#pragma once
#include "ValveSDK/Classes/CUserCmd.h"

class IPrediction
{
public:
    byte    pad1 [0x4];
    int32_t last_ground;			// 0x0004
    bool    in_prediction;			// 0x0008
    bool    first_time_predicted;	// 0x0009
    bool    engine_paused;			// 0x000A
    bool    old_cl_predict_value;	// 0x000B
    int32_t previous_startframe;	// 0x000C
    int32_t commands_predicted;		// 0x0010
    byte    pad2[0x38];				// 0x0014
    float   backup_realtime;		// 0x004C
    byte    pad3[0xC];				// 0x0050
    float   backup_curtime;			// 0x005C
    byte    pad4[0xC];				// 0x0060
    float   backup_interval;		// 0x006C

    virtual void unk0() = 0;
    virtual void unk1() = 0;
    virtual void unk2() = 0;
    virtual void Update(int iStartFrame, bool bValidFrame, int nIncomingAcknowledged, int nOutgoingCommand);
    virtual void unk4() = 0;
    virtual void unk5() = 0;
    virtual void unk6() = 0;
    virtual void unk7() = 0;
    virtual void unk8() = 0;
    virtual void unk9() = 0;
    virtual void unk10() = 0;
    virtual void unk11() = 0;
    virtual void GetLocalViewAngles(Vec3& angView);
    virtual void SetLocalViewAngles(Vec3& angView);
    virtual void unk14() = 0;
    virtual void unk15() = 0;
    virtual void unk16() = 0;
    virtual void unk17() = 0;
    virtual void CheckMovingGround(BaseEntity* pEntity, double dbFrameTime);
    virtual void unk19() = 0;
    virtual void SetupMove(BaseEntity* pEntity, CUserCmd* pCmd, IMoveHelper* pHelper, MoveData* pMoveData);
    virtual void FinishMove(BaseEntity* pEntity, CUserCmd* pCmd, MoveData* pMoveData);
};
