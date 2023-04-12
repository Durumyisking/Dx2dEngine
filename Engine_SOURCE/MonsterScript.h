#pragma once
#include "Script.h"
#include "RigidBody.h"
#include "Animator.h"
#include "GameObj.h"


namespace dru
{
    enum class eMonsterState
    {
        Idle,
        Run,
        Attack,
        Fall,
        DieAirUp,
        DieAirDown,
        DieGround,

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


        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);

        void DeleteOn() { mbDeleteOn = true; }
        void DeleteOff() { mbDeleteOn = false; }

        void HitAddForce();

        void CreateBodySlash();

        bool  IsMonsterDead() const { return mbDead; };

        void SetTarget(CGameObj* _Target) { mTarget = _Target; }
        CGameObj* GetTarget() const { return mTarget; }

        float GetPlayerDistance();

    private:
        void run();

        void hitSlash();
        void wallBound(CCollider2D* _oppo);
        void dead();

        void deadgroundComplete();
        void attackComplete();


    protected:

        void makeSlash(Vector2 _vLT, Vector2 _FrameSize, UINT _AnimSize, Vector2 _Ratio);


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        CGameObj* mTarget;
        Vector3 mPos;
        Vector3 mMoveDir;
        Vector3 mHitDir;

        bool mbOnWall;
        bool mbDead;
        bool mbDeleteOn;

        float mHitTimer;

        float mAttackTimer;

        std::wstring mMonsterName;

        std::bitset<static_cast<UINT>(eMonsterState::End)> mState;

    };

}

