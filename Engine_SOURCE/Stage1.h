#pragma once
#include "Stage.h"



namespace dru
{
    class CStage1 :
        public CStage
    {
    public:
        CStage1();
        virtual ~CStage1();

        virtual void InitStage();
        virtual void LoadAfterReady();
        virtual void Update();

    private:

		CGameObj* mUICursor;

		CGameObj* mMaskTarget;

		CBackground* mStageBackground;
		CBackground* mScreenMask;

		bool mbMaskMove;
		bool mbLoad;
		bool mbStart;

    };
}