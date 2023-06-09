#pragma once

#include "ValveSDK/Misc/Recv.h"

class IClientNetworkable;

enum ClassId {
	ClassId_CTestTraceline = 224,
	ClassId_CTEWorldDecal = 225,
	ClassId_CTESpriteSpray = 222,
	ClassId_CTESprite = 221,
	ClassId_CTESparks = 220,
	ClassId_CTESmoke = 219,
	ClassId_CTEShowLine = 217,
	ClassId_CTEProjectedDecal = 214,
	ClassId_CFEPlayerDecal = 71,
	ClassId_CTEPlayerDecal = 213,
	ClassId_CTEPhysicsProp = 210,
	ClassId_CTEParticleSystem = 209,
	ClassId_CTEMuzzleFlash = 208,
	ClassId_CTELargeFunnel = 206,
	ClassId_CTEKillPlayerAttachments = 205,
	ClassId_CTEImpact = 204,
	ClassId_CTEGlowSprite = 203,
	ClassId_CTEShatterSurface = 216,
	ClassId_CTEFootprintDecal = 200,
	ClassId_CTEFizz = 199,
	ClassId_CTEExplosion = 197,
	ClassId_CTEEnergySplash = 196,
	ClassId_CTEEffectDispatch = 195,
	ClassId_CTEDynamicLight = 194,
	ClassId_CTEDecal = 192,
	ClassId_CTEClientProjectile = 191,
	ClassId_CTEBubbleTrail = 190,
	ClassId_CTEBubbles = 189,
	ClassId_CTEBSPDecal = 188,
	ClassId_CTEBreakModel = 187,
	ClassId_CTEBloodStream = 186,
	ClassId_CTEBloodSprite = 185,
	ClassId_CTEBeamSpline = 184,
	ClassId_CTEBeamRingPoint = 183,
	ClassId_CTEBeamRing = 182,
	ClassId_CTEBeamPoints = 181,
	ClassId_CTEBeamLaser = 180,
	ClassId_CTEBeamFollow = 179,
	ClassId_CTEBeamEnts = 178,
	ClassId_CTEBeamEntPoint = 177,
	ClassId_CTEBaseBeam = 176,
	ClassId_CTEArmorRicochet = 175,
	ClassId_CTEMetalSparks = 207,
	ClassId_CSteamJet = 168,
	ClassId_CSmokeStack = 158,
	ClassId_DustTrail = 277,
	ClassId_CFireTrail = 74,
	ClassId_SporeTrail = 283,
	ClassId_SporeExplosion = 282,
	ClassId_RocketTrail = 280,
	ClassId_SmokeTrail = 281,
	ClassId_CPropVehicleDriveable = 145,
	ClassId_ParticleSmokeGrenade = 279,
	ClassId_CParticleFire = 117,
	ClassId_MovieExplosion = 278,
	ClassId_CTEGaussExplosion = 202,
	ClassId_CEnvQuadraticBeam = 66,
	ClassId_CEmbers = 55,
	ClassId_CEnvWind = 70,
	ClassId_CPrecipitation = 138,
	ClassId_CPrecipitationBlocker = 139,
	ClassId_CBaseTempEntity = 18,
	ClassId_NextBotCombatCharacter = 0,
	ClassId_CEconWearable = 54,
	ClassId_CBaseAttributableItem = 4,
	ClassId_CEconEntity = 53,
	ClassId_CWeaponZoneRepulsor = 274,
	ClassId_CWeaponXM1014 = 273,
	ClassId_CWeaponTaser = 268,
	ClassId_CTablet = 172,
	ClassId_CSnowball = 159,
	ClassId_CSmokeGrenade = 156,
	ClassId_CWeaponShield = 266,
	ClassId_CWeaponSG552 = 264,
	ClassId_CSensorGrenade = 152,
	ClassId_CWeaponSawedoff = 260,
	ClassId_CWeaponNOVA = 256,
	ClassId_CIncendiaryGrenade = 99,
	ClassId_CMolotovGrenade = 113,
	ClassId_CMelee = 112,
	ClassId_CWeaponM3 = 248,
	ClassId_CKnifeGG = 108,
	ClassId_CKnife = 107,
	ClassId_CHEGrenade = 96,
	ClassId_CFlashbang = 77,
	ClassId_CFists = 76,
	ClassId_CWeaponElite = 239,
	ClassId_CDecoyGrenade = 47,
	ClassId_CDEagle = 46,
	ClassId_CWeaponUSP = 272,
	ClassId_CWeaponM249 = 247,
	ClassId_CWeaponUMP45 = 271,
	ClassId_CWeaponTMP = 270,
	ClassId_CWeaponTec9 = 269,
	ClassId_CWeaponSSG08 = 267,
	ClassId_CWeaponSG556 = 265,
	ClassId_CWeaponSG550 = 263,
	ClassId_CWeaponScout = 262,
	ClassId_CWeaponSCAR20 = 261,
	ClassId_CSCAR17 = 150,
	ClassId_CWeaponP90 = 259,
	ClassId_CWeaponP250 = 258,
	ClassId_CWeaponP228 = 257,
	ClassId_CWeaponNegev = 255,
	ClassId_CWeaponMP9 = 254,
	ClassId_CWeaponMP7 = 253,
	ClassId_CWeaponMP5Navy = 252,
	ClassId_CWeaponMag7 = 251,
	ClassId_CWeaponMAC10 = 250,
	ClassId_CWeaponM4A1 = 249,
	ClassId_CWeaponHKP2000 = 246,
	ClassId_CWeaponGlock = 245,
	ClassId_CWeaponGalilAR = 244,
	ClassId_CWeaponGalil = 243,
	ClassId_CWeaponG3SG1 = 242,
	ClassId_CWeaponFiveSeven = 241,
	ClassId_CWeaponFamas = 240,
	ClassId_CWeaponBizon = 235,
	ClassId_CWeaponAWP = 233,
	ClassId_CWeaponAug = 232,
	ClassId_CAK47 = 1,
	ClassId_CWeaponCSBaseGun = 237,
	ClassId_CWeaponCSBase = 236,
	ClassId_CC4 = 34,
	ClassId_CBumpMine = 32,
	ClassId_CBumpMineProjectile = 33,
	ClassId_CBreachCharge = 28,
	ClassId_CBreachChargeProjectile = 29,
	ClassId_CWeaponBaseItem = 234,
	ClassId_CBaseCSGrenade = 8,
	ClassId_CSnowballProjectile = 161,
	ClassId_CSnowballPile = 160,
	ClassId_CSmokeGrenadeProjectile = 157,
	ClassId_CSensorGrenadeProjectile = 153,
	ClassId_CMolotovProjectile = 114,
	ClassId_CItem_Healthshot = 104,
	ClassId_CItemDogtags = 106,
	ClassId_CDecoyProjectile = 48,
	ClassId_CPhysPropRadarJammer = 127,
	ClassId_CPhysPropWeaponUpgrade = 128,
	ClassId_CPhysPropAmmoBox = 125,
	ClassId_CPhysPropLootCrate = 126,
	ClassId_CItemCash = 105,
	ClassId_CEnvGasCanister = 63,
	ClassId_CDronegun = 50,
	ClassId_CParadropChopper = 116,
	ClassId_CSurvivalSpawnChopper = 171,
	ClassId_CBRC4Target = 27,
	ClassId_CInfoMapRegion = 102,
	ClassId_CFireCrackerBlast = 72,
	ClassId_CInferno = 100,
	ClassId_CChicken = 36,
	ClassId_CDrone = 49,
	ClassId_CFootstepControl = 79,
	ClassId_CCSGameRulesProxy = 39,
	ClassId_CWeaponCubemap = 0,
	ClassId_CWeaponCycler = 238,
	ClassId_CTEPlantBomb = 211,
	ClassId_CTEFireBullets = 198,
	ClassId_CTERadioIcon = 215,
	ClassId_CPlantedC4 = 129,
	ClassId_CCSTeam = 43,
	ClassId_CCSPlayerResource = 41,
	ClassId_CCSPlayer = 40,
	ClassId_CPlayerPing = 131,
	ClassId_CCSRagdoll = 42,
	ClassId_CTEPlayerAnimEvent = 212,
	ClassId_CHostage = 97,
	ClassId_CHostageCarriableProp = 98,
	ClassId_CBaseCSGrenadeProjectile = 9,
	ClassId_CHandleTest = 95,
	ClassId_CTeamplayRoundBasedRulesProxy = 174,
	ClassId_CSpriteTrail = 166,
	ClassId_CSpriteOriented = 165,
	ClassId_CSprite = 164,
	ClassId_CRagdollPropAttached = 148,
	ClassId_CRagdollProp = 147,
	ClassId_CPropCounter = 142,
	ClassId_CPredictedViewModel = 140,
	ClassId_CPoseController = 136,
	ClassId_CGrassBurn = 94,
	ClassId_CGameRulesProxy = 93,
	ClassId_CInfoLadderDismount = 101,
	ClassId_CFuncLadder = 85,
	ClassId_CTEFoundryHelpers = 201,
	ClassId_CEnvDetailController = 61,
	ClassId_CDangerZone = 44,
	ClassId_CDangerZoneController = 45,
	ClassId_CWorldVguiText = 276,
	ClassId_CWorld = 275,
	ClassId_CWaterLODControl = 231,
	ClassId_CWaterBullet = 230,
	ClassId_CMapVetoPickController = 110,
	ClassId_CVoteController = 229,
	ClassId_CVGuiScreen = 228,
	ClassId_CPropJeep = 144,
	ClassId_CPropVehicleChoreoGeneric = 0,
	ClassId_CTriggerSoundOperator = 227,
	ClassId_CBaseVPhysicsTrigger = 22,
	ClassId_CTriggerPlayerMovement = 226,
	ClassId_CBaseTrigger = 20,
	ClassId_CTest_ProxyToggle_Networkable = 223,
	ClassId_CTesla = 218,
	ClassId_CBaseTeamObjectiveResource = 17,
	ClassId_CTeam = 173,
	ClassId_CSunlightShadowControl = 170,
	ClassId_CSun = 169,
	ClassId_CParticlePerformanceMonitor = 118,
	ClassId_CSpotlightEnd = 163,
	ClassId_CSpatialEntity = 162,
	ClassId_CSlideshowDisplay = 155,
	ClassId_CShadowControl = 154,
	ClassId_CSceneEntity = 151,
	ClassId_CRopeKeyframe = 149,
	ClassId_CRagdollManager = 146,
	ClassId_CPhysicsPropMultiplayer = 123,
	ClassId_CPhysBoxMultiplayer = 121,
	ClassId_CPropDoorRotating = 143,
	ClassId_CBasePropDoor = 16,
	ClassId_CDynamicProp = 52,
	ClassId_CProp_Hallucination = 141,
	ClassId_CPostProcessController = 137,
	ClassId_CPointWorldText = 135,
	ClassId_CPointCommentaryNode = 134,
	ClassId_CPointCamera = 133,
	ClassId_CPlayerResource = 132,
	ClassId_CPlasma = 130,
	ClassId_CPhysMagnet = 124,
	ClassId_CPhysicsProp = 122,
	ClassId_CStatueProp = 167,
	ClassId_CPhysBox = 120,
	ClassId_CParticleSystem = 119,
	ClassId_CMovieDisplay = 115,
	ClassId_CMaterialModifyControl = 111,
	ClassId_CLightGlow = 109,
	ClassId_CItemAssaultSuitUseable = 0,
	ClassId_CItem = 0,
	ClassId_CInfoOverlayAccessor = 103,
	ClassId_CFuncTrackTrain = 92,
	ClassId_CFuncSmokeVolume = 91,
	ClassId_CFuncRotating = 90,
	ClassId_CFuncReflectiveGlass = 89,
	ClassId_CFuncOccluder = 88,
	ClassId_CFuncMoveLinear = 87,
	ClassId_CFuncMonitor = 86,
	ClassId_CFunc_LOD = 81,
	ClassId_CTEDust = 193,
	ClassId_CFunc_Dust = 80,
	ClassId_CFuncConveyor = 84,
	ClassId_CFuncBrush = 83,
	ClassId_CBreakableSurface = 31,
	ClassId_CFuncAreaPortalWindow = 82,
	ClassId_CFish = 75,
	ClassId_CFireSmoke = 73,
	ClassId_CEnvTonemapController = 69,
	ClassId_CEnvScreenEffect = 67,
	ClassId_CEnvScreenOverlay = 68,
	ClassId_CEnvProjectedTexture = 65,
	ClassId_CEnvParticleScript = 64,
	ClassId_CFogController = 78,
	ClassId_CEnvDOFController = 62,
	ClassId_CCascadeLight = 35,
	ClassId_CEnvAmbientLight = 60,
	ClassId_CEntityParticleTrail = 59,
	ClassId_CEntityFreezing = 58,
	ClassId_CEntityFlame = 57,
	ClassId_CEntityDissolve = 56,
	ClassId_CDynamicLight = 51,
	ClassId_CColorCorrectionVolume = 38,
	ClassId_CColorCorrection = 37,
	ClassId_CBreakableProp = 30,
	ClassId_CBeamSpotlight = 25,
	ClassId_CBaseButton = 5,
	ClassId_CBaseToggle = 19,
	ClassId_CBasePlayer = 15,
	ClassId_CBaseFlex = 12,
	ClassId_CBaseEntity = 11,
	ClassId_CBaseDoor = 10,
	ClassId_CBaseCombatCharacter = 6,
	ClassId_CBaseAnimatingOverlay = 3,
	ClassId_CBoneFollower = 26,
	ClassId_CBaseAnimating = 2,
	ClassId_CAI_BaseNPC = 0,
	ClassId_CBeam = 24,
	ClassId_CBaseViewModel = 21,
	ClassId_CBaseParticleEntity = 14,
	ClassId_CBaseGrenade = 13,
	ClassId_CBaseCombatWeapon = 7,
	ClassId_CBaseWeaponWorldModel = 23
};

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
    CreateClientClassFn      m_pCreateFn;
    CreateEventFn            m_pCreateEventFn;
    char*                    m_pNetworkName;
    RecvTable*               m_pRecvTable;
    ClientClass*             m_pNext;
    ClassId                  m_ClassID;
};
