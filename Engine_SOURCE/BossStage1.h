#pragma once
#include "Stage.h"
namespace dru
{
    class CBossStage1 :
        public CStage
    {
    public:
        CBossStage1();
        virtual ~CBossStage1();

        virtual void InitStage();
        virtual void LoadinReady();
        virtual void Update();
        virtual void Exit();


        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();
        void         ClearOperate();

        virtual void Reset();
        virtual void AddStartingLiveObjects();
    };
}


