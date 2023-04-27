#pragma once
#include "MonsterScript.h"

namespace dru
{
    class CCopScript :
        public CMonsterScript
    {
    public:
        CCopScript();
        virtual ~CCopScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void attack();


        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void SetMonsterAttack();

        void CreateGun();
        void CreateBullet(Vector3 _StartPos);

    private:
        CGameObj* mCopGun;
        CGameObj* mGunMuzzle;
        CGameObj* mGunFire;
    };
}

