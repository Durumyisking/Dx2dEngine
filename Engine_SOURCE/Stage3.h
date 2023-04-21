#pragma once
#include "Stage.h"

namespace dru
{

	class CStage3 :
		public CStage
	{
    public:
        CStage3();
        virtual ~CStage3();

        virtual void InitStage();
        virtual void LoadinReady();
        virtual void Update();
        virtual void Exit();

        virtual void Reset();
        virtual void AddStartingLiveObjects();

        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();
	};

}
