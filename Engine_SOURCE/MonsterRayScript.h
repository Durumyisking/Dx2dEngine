#pragma once
#include "Script.h"

namespace dru
{
	class CMonsterScript;
	class CMonsterRayScript :
        public CScript
    {
	public:
		CMonsterRayScript();
		virtual ~CMonsterRayScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

		void SetMonster(CMonster* _monster);

		void SetMonsterAttack();
		void SetMonsterIdle();
		void SetMonsterRun();

		bool IsPlayerDead();

		void ExceptWallOn() { mbExceptWall = true; }

	private:
		CMonster* mRayOwner;
		CMonsterScript* mMonsterScript;

		CAnimator* mAnimator;
		CRigidBody* mRigidBody;

		bool mbThroughWall;
		bool mbExceptWall;
    };

}
