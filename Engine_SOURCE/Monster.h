#pragma once
#include "LiveGameObj.h"
#include "Animator.h"
#include "MonsterScript.h"
#include "RigidBody.h"
#include "MonsterRay.h"


namespace dru
{
    class CMonster :
        public CLiveGameObj
    {
	public:
		CMonster();
		virtual ~CMonster();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void PushFrameCpaturedData();
		virtual void RewindOperate(float _ElapsedTime);


		void AddRay();
		void SetRayPos();
		CMonsterRay* GetRay() const { return mRay; }
		bool IsMonsterDead();

		void Disable();

		void SetRayDie() 
		{
			mRay->Die(); 
			mRay = nullptr;
		}


	private:
		CMonsterRay* mRay;
    };
}

