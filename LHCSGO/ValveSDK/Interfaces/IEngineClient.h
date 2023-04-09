#pragma once

#include "../Geometry/Vector/Vec3.h"
#include "INetChannelInfo.h"
#include "ValveSDK/Geometry/Vector/Vec4.h"

struct model_t;
struct client_textmessage_t;
struct audiostate_t;
struct frustum_t;

class IMaterial;
class ISpatialQuery;
class IMaterialSystem;
class IAchievementMgr;
class ISPSharedMemory;

class SurfInfo;
class Sentence;
class AudioSource;
class PhysCollide;
class GamestatsData;
class KeyValues;
class SteamAPIContext;

struct Matrix4x4 {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;

		};
		float m[4][4];
	};
};

struct Matrix3x4
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;

		};
		float m[3][4];
	};

	const float* operator[](const int i) const { return m[i]; }
};

struct BrushSideInfo_t
{
    Vec4 plane;               // The plane of the brush side
    unsigned short bevel;    // Bevel plane?
    unsigned short thin;     // Thin?
};

class CPhysCollide;

struct vcollide_t
{
    unsigned short solidCount : 15;
    unsigned short isPacked : 1;
    unsigned short descSize;
    // VPhysicsSolids
    CPhysCollide   **solids;
    char           *pKeyValues;
    void           *pUserData;
};

struct cmodel_t
{
    Vec3           mins, maxs;
    Vec3           origin;        // for sounds or lights
    int            headnode;
    vcollide_t     vcollisionData;
};

struct csurface_t
{
    const char     *name;
    short          surfaceProps;
    unsigned short flags;         // BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

typedef void(*pfnDemoCustomDataCallback)(uint8_t *pData, size_t iSize);

typedef struct player_info_s
{
	int64_t unknown;					//0x0000 
	union
	{
		int64_t steam_id_64;			//0x0008 - SteamID64
		
		struct
		{
			int32_t xuid_low;
			int32_t xuid_high;
		};
	};
	char            name[128];			//0x0010 - Player Name
	int             user_id;            //0x0090 - Unique Server Identifier
	char            steam_id[20];		//0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];   //0x00A8
	unsigned long   isteam_id;			//0x00B8 - SteamID 
	char            friends_name[128];
	bool            is_fake_player;
	bool            is_hltv;
	unsigned int    custom_files[4];
	unsigned char   files_downloaded;
} player_info_t;

class IEngineClient
{
public:
    virtual int                   GetIntersectingSurfaces(const model_t *model, const Vec3 &vCenter, const float radius, const bool bOnlyVisibleSurfaces, SurfInfo *pInfos, const int nMaxInfos) = 0;
	virtual Vec3				  GetLightForPoint(const Vec3 &pos, bool bClamp) = 0;
	virtual IMaterial*            TraceLineMaterialAndLighting(const Vec3 &start, const Vec3 &end, Vec3 &diffuseLightColor, Vec3& baseColor) = 0;
	virtual const char*           ParseFile(const char *data, char *token, int maxlen) = 0;
	virtual bool                  CopyFile(const char *source, const char *destination) = 0;
	virtual void                  GetScreenSize(int& width, int& height) = 0;
	virtual void                  ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
	virtual void                  ClientCmd(const char *szCmdString) = 0;
	virtual bool                  GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int                   GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t* TextMessageGet(const char *pName) = 0; // 10
	virtual bool                  Con_IsVisible() = 0;
	virtual int                   GetLocalPlayer() = 0;
	virtual const model_t*        LoadModel(const char *pName, bool bProp = false) = 0;
	virtual float                 GetLastTimeStamp() = 0;
	virtual Sentence*             GetSentence(AudioSource *pAudioSource) = 0; // 15
	virtual float                 GetSentenceLength(AudioSource *pAudioSource) = 0;
	virtual bool                  IsStreaming(AudioSource *pAudioSource) const = 0;
	virtual void                  GetViewAngles(Vec3& va) = 0;
	virtual void                  SetViewAngles(Vec3& va) = 0;
	virtual int                   GetMaxClients() = 0; // 20
	virtual const char*           Key_LookupBinding(const char *pBinding) = 0;
	virtual const char*           Key_BindingForKey(int &code) = 0;
	virtual void                  Key_SetBinding(int, char const*) = 0;
	virtual void                  StartKeyTrapMode() = 0;
	virtual bool                  CheckDoneKeyTrapping(int &code) = 0;
	virtual bool                  IsInGame() = 0;
	virtual bool                  IsConnected() = 0;
	virtual bool                  IsDrawingLoadingImage() = 0;
	virtual void                  HideLoadingPlaque() = 0;
	virtual void                  Con_NPrintf(int pos, const char *fmt, ...) = 0; // 30
	virtual void                  Con_NXPrintf(const struct con_nprint_s *info, const char *fmt, ...) = 0;
	virtual int                   IsBoxVisible(const Vec3& mins, const Vec3& maxs) = 0;
	virtual int                   IsBoxInViewCluster(const Vec3& mins, const Vec3& maxs) = 0;
	virtual bool                  CullBox(const Vec3& mins, const Vec3& maxs) = 0;
	virtual void                  Sound_ExtraUpdate() = 0;
	virtual const char*           GetGameDirectory() = 0;
	virtual const Matrix4x4&      WorldToScreenMatrix() = 0;
	virtual const Matrix4x4&      WorldToViewMatrix() = 0;
	virtual int                   GameLumpVersion(int lumpId) const = 0;
	virtual int                   GameLumpSize(int lumpId) const = 0; // 40
	virtual bool                  LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int                   LevelLeafCount() const = 0;
	virtual ISpatialQuery*        GetBSPTreeQuery() = 0;
	virtual void                  LinearToGamma(float* linear, float* gamma) = 0;
	virtual float                 LightStyleValue(int style) = 0; // 45
	virtual void                  ComputeDynamicLighting(const Vec3& pt, const Vec3* pNormal, Vec3& color) = 0;
	virtual void                  GetAmbientLightColor(Vec3& color) = 0;
	virtual int                   GetDXSupportLevel() = 0;
	virtual bool                  SupportsHDR() = 0;
	virtual void                  Mat_Stub(IMaterialSystem *pMatSys) = 0; // 50
	virtual void                  GetChapterName(char *pchBuff, int iMaxLength) = 0;
	virtual char const*           GetLevelName() = 0;
	virtual char const*           GetLevelNameShort() = 0;
	virtual char const*           GetMapGroupName() = 0;
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI() = 0;
	virtual void                  SetVoiceCasterID(unsigned int someint) = 0; // 56
	virtual void                  EngineStats_BeginFrame() = 0;
	virtual void                  EngineStats_EndFrame() = 0;
	virtual void                  FireEvents() = 0;
	virtual int                   GetLeavesArea(unsigned short *pLeaves, int nLeaves) = 0;
	virtual bool                  DoesBoxTouchAreaFrustum(const Vec3 &mins, const Vec3 &maxs, int iArea) = 0; // 60
	virtual int                   GetFrustumList(frustum_t **pList, int listMax) = 0;
	virtual bool                  ShouldUseAreaFrustum(int i) = 0;
	virtual void                  SetAudioState(const audiostate_t& state) = 0;
	virtual int                   SentenceGroupPick(int groupIndex, char *name, int nameBufLen) = 0;
	virtual int                   SentenceGroupPickSequential(int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int                   SentenceIndexFromName(const char *pSentenceName) = 0;
	virtual const char*           SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int                   SentenceGroupIndexFromName(const char *pGroupName) = 0;
	virtual const char*           SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float                 SentenceLength(int sentenceIndex) = 0;
	virtual void                  ComputeLighting(const Vec3& pt, const Vec3* pNormal, bool bClamp, Vec3& color, Vec3 *pBoxColors = NULL) = 0;
	virtual void                  ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool                  IsOccluded(const Vec3 &vecAbsMins, const Vec3 &vecAbsMaxs) = 0; // 74
	virtual int                   GetOcclusionViewId() = 0;
	virtual void*                 SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void                  SaveFreeMemory(void *pSaveMem) = 0;
	virtual INetChannelInfo*      GetNetChannelInfo() = 0;
	virtual void                  DebugDrawPhysCollide(const PhysCollide *pCollide, IMaterial *pMaterial, const Matrix3x4& transform, const uint8_t* color) = 0; //79
	virtual void                  CheckPoint(const char *pName) = 0; // 80
	virtual void                  DrawPortals() = 0;
	virtual bool                  IsPlayingDemo() = 0;
	virtual bool                  IsRecordingDemo() = 0;
	virtual bool                  IsPlayingTimeDemo() = 0;
	virtual int                   GetDemoRecordingTick() = 0;
	virtual int                   GetDemoPlaybackTick() = 0;
	virtual int                   GetDemoPlaybackStartTick() = 0;
	virtual float                 GetDemoPlaybackTimeScale() = 0;
	virtual int                   GetDemoPlaybackTotalTicks() = 0;
	virtual bool                  IsPaused() = 0; // 90
	virtual float                 GetTimescale() const = 0;
	virtual bool                  IsTakingScreenshot() = 0;
	virtual bool                  IsHLTV() = 0;
	virtual bool                  IsLevelMainMenuBackground() = 0;
	virtual void                  GetMainMenuBackgroundName(char *dest, int destlen) = 0;
	virtual void                  SetOcclusionParameters(const int /*OcclusionParams_t*/ &params) = 0; // 96
	virtual void                  GetUILanguage(char *dest, int destlen) = 0;
	virtual int                   IsSkyboxVisibleFromPoint(const Vec3 &vecPoint) = 0;
	virtual const char*           GetMapEntitiesString() = 0;
	virtual bool                  IsInEditMode() = 0; // 100
	virtual float                 GetScreenAspectRatio(int viewportWidth, int viewportHeight) = 0;
	virtual bool                  REMOVED_SteamRefreshLogin(const char *password, bool isSecure) = 0;
	virtual bool                  REMOVED_SteamProcessCall(bool & finished) = 0;
	virtual unsigned int          GetEngineBuildNumber() = 0; // engines build
	virtual const char *          GetProductVersionString() = 0; // mods version number (steam.inf)
	virtual void                  GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool                  IsHammerRunning() const = 0;
	virtual void                  ExecuteClientCmd(const char *szCmdString) = 0; //108
	virtual bool                  MapHasHDRLighting() = 0;
	virtual bool                  MapHasLightMapAlphaData() = 0;
	virtual int                   GetAppID() = 0;
	virtual Vec3                  GetLightForPointFast(const Vec3 &pos, bool bClamp) = 0;
	virtual void                  ClientCmd_Unrestricted(char  const*, bool fromConsoleOrKeybind = false) = 0;
	virtual void                  ClientCmd_Unrestricted(const char *szCmdString) = 0; // 114
	virtual void                  SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void                  SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void                  SetOverlayBindProxy(int iOverlayID, void *pBindProxy) = 0;
	virtual bool                  CopyFrameBufferToMaterial(const char *pMaterialName) = 0;
	virtual void                  ReadConfiguration(const int iController, const bool readDefault) = 0;
	virtual void                  SetAchievementMgr(IAchievementMgr *pAchievementMgr) = 0;
	virtual IAchievementMgr*      GetAchievementMgr() = 0;
	virtual bool                  MapLoadFailed() = 0;
	virtual void                  SetMapLoadFailed(bool bState) = 0;
	virtual bool                  IsLowViolence() = 0;
	virtual const char*           GetMostRecentSaveGame() = 0;
	virtual void                  SetMostRecentSaveGame(const char *lpszFilename) = 0;
	virtual void                  StartXboxExitingProcess() = 0;
	virtual bool                  IsSaveInProgress() = 0;
	virtual bool                  IsAutoSaveDangerousInProgress() = 0;
	virtual unsigned int          OnStorageDeviceAttached(int iController) = 0;
	virtual void                  OnStorageDeviceDetached(int iController) = 0;
	virtual const char*           GetSaveDirName() = 0;
	virtual void                  WriteScreenshot(const char *pFilename) = 0;
	virtual void                  ResetDemoInterpolation() = 0;
	virtual int                   GetActiveSplitScreenPlayerSlot() = 0;
	virtual int                   SetActiveSplitScreenPlayerSlot(int slot) = 0;
	virtual bool                  SetLocalPlayerIsResolvable(char const *pchContext, int nLine, bool bResolvable) = 0;
	virtual bool                  IsLocalPlayerResolvable() = 0;
	virtual int                   GetSplitScreenPlayer(int nSlot) = 0;
	virtual bool                  IsSplitScreenActive() = 0;
	virtual bool                  IsValidSplitScreenSlot(int nSlot) = 0;
	virtual int                   FirstValidSplitScreenSlot() = 0; // -1 == invalid
	virtual int                   NextValidSplitScreenSlot(int nPreviousSlot) = 0; // -1 == invalid
	virtual ISPSharedMemory*      GetSinglePlayerSharedMemorySpace(const char *szName, int ent_num = (1 << 11)) = 0;
	virtual void                  ComputeLightingCube(const Vec3& pt, bool bClamp, Vec3 *pBoxColors) = 0;
	virtual void                  RegisterDemoCustomDataCallback(const char* szCallbackSaveID, pfnDemoCustomDataCallback pCallback) = 0;
	virtual void                  RecordDemoCustomData(pfnDemoCustomDataCallback pCallback, const void *pData, size_t iDataLength) = 0;
	virtual void                  SetPitchScale(float flPitchScale) = 0;
	virtual float                 GetPitchScale() = 0;
	virtual bool                  LoadFilmmaker() = 0;
	virtual void                  UnloadFilmmaker() = 0;
	virtual void                  SetLeafFlag(int nLeafIndex, int nFlagBits) = 0;
	virtual void                  RecalculateBSPLeafFlags() = 0;
	virtual bool                  DSPGetCurrentDASRoomNew() = 0;
	virtual bool                  DSPGetCurrentDASRoomChanged() = 0;
	virtual bool                  DSPGetCurrentDASRoomSkyAbove() = 0;
	virtual float                 DSPGetCurrentDASRoomSkyPercent() = 0;
	virtual void                  SetMixGroupOfCurrentMixer(const char *szgroupname, const char *szparam, float val, int setMixerType) = 0;
	virtual int                   GetMixLayerIndex(const char *szmixlayername) = 0;
	virtual void                  SetMixLayerLevel(int index, float level) = 0;
	virtual int                   GetMixGroupIndex(char  const* groupname) = 0;
	virtual void                  SetMixLayerTriggerFactor(int i1, int i2, float fl) = 0;
	virtual void                  SetMixLayerTriggerFactor(char  const* char1, char  const* char2, float fl) = 0;
	virtual bool                  IsCreatingReslist() = 0;
	virtual bool                  IsCreatingXboxReslist() = 0;
	virtual void                  SetTimescale(float flTimescale) = 0;
	virtual void                  SetGamestatsData(GamestatsData *pGamestatsData) = 0;
	virtual GamestatsData*        GetGamestatsData() = 0;
	virtual void                  GetMouseDelta(int &dx, int &dy, bool b) = 0; // unknown
	virtual const char*           Key_LookupBindingEx(const char *pBinding, int iUserId = -1, int iStartCount = 0, int iAllowJoystick = -1) = 0;
	virtual int                   Key_CodeForBinding(char  const*, int, int, int) = 0;
	virtual void                  UpdateDAndELights() = 0;
	virtual int                   GetBugSubmissionCount() const = 0;
	virtual void                  ClearBugSubmissionCount() = 0;
	virtual bool                  DoesLevelContainWater() const = 0;
	virtual float                 GetServerSimulationFrameTime() const = 0;
	virtual void                  SolidMoved(class IClientEntity *pSolidEnt, class ICollideable *pSolidCollide, const Vec3* pPrevAbsOrigin, bool accurateBboxTriggerChecks) = 0;
	virtual void                  TriggerMoved(class IClientEntity *pTriggerEnt, bool accurateBboxTriggerChecks) = 0;
	virtual void                  ComputeLeavesConnected(const Vec3 &vecOrigin, int nCount, const int *pLeafIndices, bool *pIsConnected) = 0;
	virtual bool                  IsInCommentaryMode() = 0;
	virtual void                  SetBlurFade(float amount) = 0;
	virtual bool                  IsTransitioningToLoad() = 0;

};
