#pragma once
#include "Script.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Player.h"

#define VELOCITY_RUN dru::math::Vector3(5.f, 7.f, 0.f)
#define VELOCITY_WALK dru::math::Vector3(1.f, 7.f, 0.f)


namespace dru
{
    enum class eBossState
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


    class CBossScript :
        public CScript
    {
    public:
        CBossScript();
        virtual ~CBossScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void attack();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        void FlipCheck();
        void Reset();

        void SetSingleState(eBossState _Type);

    protected:
        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        CPlayer* mPlayer;

        Vector3 mPos;
        Vector3 mMoveDir;

        bool mbDead;


        std::wstring mBossName;
        std::bitset<static_cast<UINT>(eBossState::End)> mState;

    
    public:
        void SetPlayer(CPlayer* _Player) { mPlayer = _Player; }


    };
}