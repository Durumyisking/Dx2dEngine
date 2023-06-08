#pragma once
#include "Stage.h"

namespace dru
{
    class CBossStage2 :
        public CStage
    {
    public:
        CBossStage2();
        virtual ~CBossStage2();

        virtual void InitStage();
        virtual void LoadinReady();
        virtual void Update();
        virtual void Exit();


        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();

        virtual void Reset();
        virtual void AddStartingLiveObjects();

        void CreateOutWall();
        void CreateFirstFloor();

    private:
        CBoss* mHeadhunter;
        Vector3 mHeadhunterDefaultPos;
    };

}

