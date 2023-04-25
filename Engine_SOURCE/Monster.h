#pragma once
#include "LiveGameObj.h"
#include "MonsterScript.h"
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


		void AddRay(Vector3 _Scale = Vector3::Zero);
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

