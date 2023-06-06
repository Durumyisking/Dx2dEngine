#pragma once
#include "Stage.h"

namespace dru
{
    class CStage2 :
        public CStage
    {
    public:
        CStage2();
        virtual ~CStage2();

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

        void CreateOutWall();
        void CreateFirstFloor();
        void CreateSecondFloor();


    private:
        CMonster* mGrunt1;
        CMonster* mCop1;
        CMonster* mPomp1;

        Vector3 mGrunt1DefaultPos;
        Vector3 mCop1DefaultPos;

    };

}