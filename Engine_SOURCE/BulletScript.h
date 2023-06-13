#pragma once
#include "Script.h"

namespace dru
{
	class CBulletScript :
		public CScript
	{
    public:
        CBulletScript();
        virtual ~CBulletScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;


        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);

    public:
        void BulletScaling();
        void BulletMove();
        void BulletReflect();

        void InitializeBulletReflectComponent();
        void InitializeGunFireComponent();

        void Disable();

        void RotateBullet(Vector3 _Dir, Vector3 _Pos, float _Angle);
        void RotateBulletCollider(float _Angle);

        void SetGunfired(bool _flag) { mbGunfired = _flag; }

    private:
        void BulletReflectComplete();
        void PlayBulletReflect();
        void BulletReflectPositioning();

        void GunFireComplete();
        void PlayGunFire();

    private:
        CBullet* mBullet;
        CAudioSource* mAudioSource;
        CGameObj* mBulletReflect;
        CGameObj* mGunFire;
        float mElapsedTime;
        Vector3 mDefaultBulletScale;
        Vector3 mDir;

        bool mbDisabled;
        bool mbScalingDone;
        bool mbGunfired;

    public:
        CGameObj* GetOrCreateBulletReflectObject();
        CGameObj* GetOrCreateGunFireObject();
    };
}

