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

        void CreateOutWall();
        void CreateFirstFloor();
        void CreateSecondFloor();
        void CreateThirdFloor();
        void CreateFourthFloor();


    private:
        CMonster* mPomp1;
        CMonster* mPomp2;
        CMonster* mGrunt1;
        CMonster* mGrunt2;
        CMonster* mCop1;
        CMonster* mCop2;


        CDoor* mDoor1;
        CDoor* mDoor2;
        CDoor* mDoor3;

        CFloor*  mLaserFloor;
        CTurret* mLaserTurret1;
        CTurret* mLaserTurret2;
        CTurret* mLaserTurret3;

        Vector3 mPomp1DefaultPos;
        Vector3 mPomp2DefaultPos;
        Vector3 mGrunt1DefaultPos;
        Vector3 mGrunt2DefaultPos;
        Vector3 mCop1DefaultPos;
        Vector3 mCop2DefaultPos;

	};

}
