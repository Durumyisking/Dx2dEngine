#pragma once
#include "Stage.h"

namespace dru
{
    class CStageTutorial :
        public CStage
    {
    public:
        CStageTutorial();
        virtual ~CStageTutorial();

        virtual void InitStage();
        virtual void LoadAfterReady();
        virtual void Update();

    };

    CGameObj* mUICursor;

    CGameObj* mMaskTarget;

    CPlayer* mPlayer;

    CBackground* mStageBackground;
    CBackground* mScreenMask;

    bool mbMaskMove;
    
}