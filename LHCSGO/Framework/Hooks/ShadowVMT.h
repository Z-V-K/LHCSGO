#pragma once

class ShadowVMT
{
public:
	ShadowVMT();
	ShadowVMT(void* base);
	~ShadowVMT();

	bool Setup(void* class_base = nullptr);

	template<typename T>
	void HookIndex(int index, T fun)
	{
		assert(index >= 0 && index <= (int)vftbl_len);
		new_vftbl[index + 1] = reinterpret_cast<std::uintptr_t>(fun);
	}
	void UnhookIndex(int index)
	{
		new_vftbl[index] = old_vftbl[index];
	}
	void UnhookAll()
	{
		try {
			if (old_vftbl != nullptr) {
				DWORD old;
				VirtualProtect(class_base, sizeof(uintptr_t), PAGE_READWRITE, &old);
				*(std::uintptr_t**)class_base = old_vftbl;
				old_vftbl = nullptr;
				VirtualProtect(class_base, sizeof(uintptr_t), old, &old);
			}
		}
		catch (...) {
		}
	}

	template<typename T>
	T GetOg(int index)
	{
		return (T)old_vftbl[index];
	}

private:
	inline std::size_t CalcVtableLength(std::uintptr_t* vftbl_start);

	void*           class_base;
	std::size_t     vftbl_len;
	std::uintptr_t* new_vftbl;
	std::uintptr_t* old_vftbl;
};