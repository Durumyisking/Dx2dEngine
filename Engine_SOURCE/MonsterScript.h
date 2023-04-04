#pragma once
#include "Script.h"
#include "RigidBody.h"

namespace dru
{
    enum class eMonsterState
    {
        Idle, //0
        Run,// 2
        TutorAttack,// 5 
        Fall,// 11
        DieAirUp,
        DieAirDown,
        DieGround,

        End,
    };

    class CMonsterScript :
        public CScript
    {
    public:
        CMonsterScript();
        virtual ~CMonsterScript();

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

        void DeleteOn() { mbDeleteOn = true; }
        void DeleteOff() { mbDeleteOn = false; }

        void HitAddForce();

    private:
        void deadgroundComplete();

        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        Vector3 mPos;
        Vector3 mMoveDir;
        Vector3 mHitDir;

        bool mbOnWall;
        bool mbDead;
        bool mbDeleteOn;

        float mHitTimer;

        std::wstring mMonsterName;

        std::bitset<static_cast<UINT>(eMonsterState::End)> mState;

    };

}

