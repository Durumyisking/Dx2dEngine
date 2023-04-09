#pragma once
#include "Script.h"


namespace dru
{
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


		CMonster* mRayOwner;
		CGameObj* mTarget;

    };

}
