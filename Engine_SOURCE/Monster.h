#pragma once
#include "LiveGameObj.h"
#include "MonsterScript.h"
#include "MonsterRay.h"
#include "Bullet.h"


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
		virtual void rewindRender();

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

		Vector3 GetRayScale() const { return mRayScale; }
		void MonsterPatrolOn();

	protected:
		Vector3 mRayScale;

		
	private:
		CMonsterRay* mRay;
    };
}

