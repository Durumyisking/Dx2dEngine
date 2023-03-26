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

    private:

		CGameObj* mUICursor;

		CGameObj* mMaskTarget;

		CPlayer* mPlayer;

		CBackground* mStageBackground;
		CBackground* mScreenMask;

		bool mbMaskMove;
		bool mbLoad;
		bool mbStart;

    };
}