#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <winternl.h>

#define DLL_PATH "C:\\Users\\Kevin\\Desktop\\Dev\\LHCSGO\\Release\\LHCSGO.dll"
#define PROCESS_NAME L"csgo.exe"

typedef HMODULE(__stdcall* pLoadLibraryA)(LPCSTR);
typedef FARPROC(__stdcall* pGetProcAddress)(HMODULE, LPCSTR);
typedef INT(__stdcall* dllmain)(HMODULE, DWORD, LPVOID); 

using f_NTQuerySystemInformation = NTSTATUS(WINAPI*)(ULONG, PVOID, ULONG, PULONG);

struct SYSTEM_THREADS {
	LARGE_INTEGER  KernelTime;
	LARGE_INTEGER  UserTime;
	LARGE_INTEGER  CreateTime;
	ULONG          WaitTime;
	PVOID          StartAddress;
	CLIENT_ID      ClientId;
	KPRIORITY      Priority;
	KPRIORITY      BasePriority;
	ULONG          ContextSwitchCount;
	LONG           State;
	LONG           WaitReason;
};

struct VM_COUNTERS {
	SIZE_T             PeakVirtualSize;
	SIZE_T             VirtualSize;
	ULONG              PageFaultCount;
	SIZE_T             PeakWorkingSetSize;
	SIZE_T             WorkingSetSize;
	SIZE_T             QuotaPeakPagedPoolUsage;
	SIZE_T             QuotaPagedPoolUsage;
	SIZE_T             QuotaPeakNonPagedPoolUsage;
	SIZE_T             QuotaNonPagedPoolUsage;
	SIZE_T             PagefileUsage;
	SIZE_T             PeakPagefileUsage;
};

struct SYSTEM_PROCESSES {
	ULONG              NextEntryDelta;
	ULONG              ThreadCount;
	ULONG              Reserved1[6];
	LARGE_INTEGER      CreateTime;
	LARGE_INTEGER      UserTime;
	LARGE_INTEGER      KernelTime;
	UNICODE_STRING     ProcessName;
	KPRIORITY          BasePriority;
	ULONG              ProcessId;
	ULONG              InheritedFromProcessId;
	ULONG              HandleCount;
	ULONG              Reserved2[2];
	VM_COUNTERS        VmCounters;
	IO_COUNTERS        IoCounters;
	SYSTEM_THREADS     Threads[1];
};

struct LoaderData
{
	PBYTE BaseAddress;

	DWORD AddressOfEntryPoint;
	DWORD BaseRelocation;
	DWORD ImportDir;
	DWORD ImageBase;

	pLoadLibraryA fnLoadLibraryA;
	pGetProcAddress fnGetProcAddress;
};

DWORD GetThreadId() {
	const auto hNTDLL{ LoadLibraryW(L"ntdll") };
	if (!hNTDLL)
		return 0;

	const auto ntQSI{ reinterpret_cast<f_NTQuerySystemInformation>(GetProcAddress(hNTDLL, "NtQuerySystemInformation")) };
	if (!ntQSI)
		return 0;


	if (SIZE_T buffersize; !NT_SUCCESS(ntQSI(SystemProcessInformation, nullptr, 0, &buffersize))) {
		auto buffer{ std::make_unique<std::byte[]>(buffersize) };
		auto spi{ reinterpret_cast<SYSTEM_PROCESSES*>(buffer.get()) };
		if (NTSTATUS status; !NT_SUCCESS(status = ntQSI(SystemProcessInformation, spi, buffersize, nullptr)))
			return 0;

		while (spi->NextEntryDelta)
		{
			spi = reinterpret_cast<SYSTEM_PROCESSES*>((LPBYTE)spi + spi->NextEntryDelta);

			if(!wcscmp(spi->ProcessName.Buffer, PROCESS_NAME))
				return reinterpret_cast<ULONG>(spi->Threads->ClientId.UniqueThread);
		}
	}

	return 0;
}

DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

DWORD __stdcall libraryLoader(LPVOID Memory)
{
	LoaderData* loaderData = (LoaderData*)Memory;
	
    PIMAGE_BASE_RELOCATION relocation = (PIMAGE_BASE_RELOCATION)(loaderData->BaseAddress + loaderData->BaseRelocation);
    DWORD delta = (DWORD)(loaderData->BaseAddress - loaderData->ImageBase);
    while (relocation->VirtualAddress) {
        PWORD relocationInfo = (PWORD)(relocation + 1);
        for (int i = 0, count = (relocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD); i < count; i++)
            if (relocationInfo[i] >> 12 == IMAGE_REL_BASED_HIGHLOW)
                * (PDWORD)(loaderData->BaseAddress + (relocation->VirtualAddress + (relocationInfo[i] & 0xFFF))) += delta;
    
        relocation = (PIMAGE_BASE_RELOCATION)((LPBYTE)relocation + relocation->SizeOfBlock);
    }
    
    PIMAGE_IMPORT_DESCRIPTOR importDirectory = (PIMAGE_IMPORT_DESCRIPTOR)(loaderData->BaseAddress + loaderData->ImportDir);
    
    while (importDirectory->Characteristics) {
        PIMAGE_THUNK_DATA originalFirstThunk = (PIMAGE_THUNK_DATA)(loaderData->BaseAddress + importDirectory->OriginalFirstThunk);
        PIMAGE_THUNK_DATA firstThunk = (PIMAGE_THUNK_DATA)(loaderData->BaseAddress + importDirectory->FirstThunk);
    
        HMODULE module = loaderData->fnLoadLibraryA((LPCSTR)loaderData->BaseAddress + importDirectory->Name);
    
        if (!module)
            return FALSE;
    
        while (originalFirstThunk->u1.AddressOfData) {
            DWORD Function = (DWORD)loaderData->fnGetProcAddress(module, originalFirstThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG ? (LPCSTR)(originalFirstThunk->u1.Ordinal & 0xFFFF) : ((PIMAGE_IMPORT_BY_NAME)((LPBYTE)loaderData->BaseAddress + originalFirstThunk->u1.AddressOfData))->Name);
    
            if (!Function)
                return FALSE;
    
            firstThunk->u1.Function = Function;
            originalFirstThunk++;
            firstThunk++;
        }
        importDirectory++;
    }

	if (loaderData->AddressOfEntryPoint)
	{
		DWORD result = ((DWORD(__stdcall*)(HMODULE, DWORD, LPVOID))
			(loaderData->BaseAddress + loaderData->AddressOfEntryPoint))
			((HMODULE)loaderData->BaseAddress, DLL_PROCESS_ATTACH, NULL);

		return result;
	}

	return 1;
}

DWORD __stdcall stub()
{
	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE hDll = CreateFileA(DLL_PATH, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	
	DWORD fileSize = GetFileSize(hDll, 0);
	LPVOID fileBuffer = VirtualAlloc(NULL, fileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	
	ReadFile(hDll, fileBuffer, fileSize, NULL, NULL);

	HANDLE hOgThread = OpenThread(THREAD_ALL_ACCESS, FALSE, GetThreadId());
	if(!hOgThread)
	{
		printf("Error getting thread handle\n");
		return 1;
	}
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, FindProcessId(PROCESS_NAME));
	if(!hProcess)
	{
		printf("Error OpenProcess csgo.exe\n");
		return 1;
	}

	SuspendThread(hOgThread);
	
	PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((LPBYTE)fileBuffer + ((PIMAGE_DOS_HEADER)fileBuffer)->e_lfanew);

    PBYTE executableImage = (PBYTE) VirtualAllocEx(hProcess, NULL, ntHeaders->OptionalHeader.SizeOfImage,
        MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    PIMAGE_SECTION_HEADER sectionHeaders = (PIMAGE_SECTION_HEADER)(ntHeaders + 1);
    for (INT i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++)
        WriteProcessMemory(hProcess, executableImage + sectionHeaders[i].VirtualAddress,
            (LPBYTE) fileBuffer + sectionHeaders[i].PointerToRawData, sectionHeaders[i].SizeOfRawData, NULL);

    LoaderData* loaderMemory = (LoaderData*) VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READ);

    LoaderData loaderParams;
    loaderParams.BaseAddress = executableImage;
    loaderParams.fnLoadLibraryA = LoadLibraryA;
    loaderParams.fnGetProcAddress = GetProcAddress;

    loaderParams.ImageBase = ntHeaders->OptionalHeader.ImageBase;
    loaderParams.BaseRelocation = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
    loaderParams.ImportDir = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    loaderParams.AddressOfEntryPoint = ntHeaders->OptionalHeader.AddressOfEntryPoint;
    
    WriteProcessMemory(hProcess, loaderMemory, &loaderParams, sizeof(LoaderData),
        NULL);
    WriteProcessMemory(hProcess, loaderMemory + 1, libraryLoader,
        (DWORD)stub - (DWORD)libraryLoader, NULL);
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)(loaderMemory + 1),
        loaderMemory, 0, NULL);


	ResumeThread(hOgThread);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(hProcess, loaderMemory, 0, MEM_RELEASE);

	CloseHandle(hProcess);
	CloseHandle(hOgThread);
	
	return 0;
}
