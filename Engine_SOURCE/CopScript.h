#pragma once
#include "MonsterScript.h"

namespace dru
{
    class CBullet;
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

        void GunFlip();
        void RotateGun(Vector3 _Dir);

        void InitializeGunFireComponent();
        void InitializeGunSmokeComponent();


    private:
        void GunFireComplete();
        void GunSmokeComplete();

        void PlayGunFire();
        void PlayGunSmoke();

        void GunFireSmokePositioning(CGameObj* GunFireOrSmoke);


    private:
        CGameObj* mCopGun;
        CGameObj* mGunMuzzle;
        CGameObj* mGunFire;
        CGameObj* mGunSmoke;

        float mAngle;

    public:
        CGameObj* GetOrCreateGunFireObject();
        CGameObj* GetOrCreateGunSmokeObject();

    };
}

