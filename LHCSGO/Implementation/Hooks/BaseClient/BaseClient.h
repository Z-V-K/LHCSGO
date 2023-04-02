#pragma once

enum struct ClientFrameStage : int {
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};

namespace BaseClient
{
    void __fastcall hk_FrameStageNotify(void* thisPtr, void* edx, ClientFrameStage stage);
};
