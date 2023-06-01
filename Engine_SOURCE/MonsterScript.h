#pragma once
#include "Script.h"
#include "RigidBody.h"
#include "Animator.h"
#include "GameObj.h"

#define VELOCITY_RUN dru::math::Vector3(5.f, 7.f, 0.f)
#define VELOCITY_WALK dru::math::Vector3(1.f, 7.f, 0.f)


namespace dru
{
    enum class eMonsterState
    {
        Idle,
        Patrol,
        Run,
        Attack,
        Fall,
        DieAirUp,
        DieAirDown,
        DieGround,
        Block,

        End,
    };

    class CMonsterScript :
        public CScript
    {
        friend class CMonsterRayScript;
    public:
        CMonsterScript();
        virtual ~CMonsterScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void attack();
        virtual void patrol();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);

        virtual void SetMonsterAttack() = 0;

        void HitAddForce();
        void CreateBodySlash();
        void CreateDirBlood();
        void CreateBodyBlood();
        void CreateDecalBlood();
        bool IsMonsterDead() const { return mbDead; };

        void FlipCheck();
        void Reset();

        void SetSingleState(eMonsterState _Type);
        bool GetSingleState(eMonsterState _Type) { return mState[(UINT)_Type]; };

        void DeleteTarget() { mTarget = nullptr; }

        void SetHitDir();

    protected:
        void runTrigger();
        void run();

        void hitSlash(int _Type);
        void collEnter_BulletSlash(CCollider2D* _oppo);
        void wallBound(CCollider2D* _oppo);
        void dead();

        void deadgroundComplete();
        void attackComplete();

        void collEnter_Floor2(CCollider2D* _oppo);

    protected:

        void makeSlash(Vector2 _vLT, Vector2 _FrameSize, UINT _AnimSize, Vector2 _Ratio);


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        CLiveGameObj* mTarget;
        Vector3 mPos;
        Vector3 mMoveDir;
        Vector3 mHitDir;

        bool mbOnWall;
        bool mbDead;
        bool mbDeleteOn;

        float mHitTimer;

        float mAttackTimer;

        float mDetectRadius;
        float mAttackRadius;

        std::wstring mMonsterName;

        std::bitset<static_cast<UINT>(eMonsterState::End)> mState;

        bool mbBodyBlood;
        float mBodyBloodTimer;

    public:
        void DeleteOn() { mbDeleteOn = true; }
        void DeleteOff() { mbDeleteOn = false; }

        void SetTarget(CLiveGameObj* _Target) { mTarget = _Target; }
        CLiveGameObj* GetTarget() const { return mTarget; }

        float GetPlayerDistance();
        Vector3 GetPlayerTowardDir(CGameObj* _Obj);

        void SetDetectRadius(float _Value) { mDetectRadius = _Value; }
        float GetDetectRadius() const { return mDetectRadius; }
        void SetAttackRadius(float _Value) { mAttackRadius = _Value; }
        float GetAttackRadius() const { return mAttackRadius; }
    };
}

