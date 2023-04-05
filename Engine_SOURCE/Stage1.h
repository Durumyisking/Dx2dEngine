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
        virtual void LoadinReady();
        virtual void Update();
        virtual void Exit();

        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();

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