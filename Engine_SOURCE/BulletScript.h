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

        void Disable();

    private:
        void BulletReflectComplete();

        void PlayBulletReflect();

        void BulletReflectPositioning();

    private:
        CBullet* mBullet;
        CGameObj* mBulletReflect;
        float mElapsedTime;
        Vector3 mDefaultBulletScale;
        Vector3 mDir;

        bool mbScalingDone;
        bool mbCreated;

    public:
        CGameObj* GetOrCreateBulletReflectObject();
	};
}

