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
        void CreateThirdFloor();


    private:
        CMonster* mGrunt1;
        CMonster* mGrunt2;

        CFloor* mLaserFloor;
        CTurret* mLaserTurret;

        CDoor* mDoor1;

        Vector3 mGrunt1DefaultPos;
        Vector3 mGrunt2DefaultPos;
    };
}