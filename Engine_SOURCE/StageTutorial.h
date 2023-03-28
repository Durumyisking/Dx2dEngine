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

    private:
        CGameObj* mUICursor;

        CGameObj* mMaskTarget;
        CGameObj* mCamTarget;

        CBackground* mStageBackground;
        CBackground* mScreenMask;

        CBackgroundColor* mUIBg;
        CGameObj* mTutorialtxt;

        float mFadeTimer;
        bool mbFadeDone;

        bool mbZoomDone;

        bool mbMaskMove;

    };    
}