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
        Pattern1,
        Pattern2,
        Pattern3,
        Pattern4,
        Pattern5,
        Fall,
        DieGround,
        Block,
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

        virtual void Reset();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void Pattern1() = 0;
        virtual void Pattern2() = 0;
        virtual void Pattern3() = 0;
        virtual void Pattern4() = 0;
        virtual void Pattern5() = 0;

        void ChoosePattern();

        virtual void PatternEnd(UINT _PatternNumber);

        void IdleOperate();
        void PatternOperate();

        void FlipCheck();

        void SetSingleState(eBossState _Type);
        bool GetState(eBossState _Type) const { return mState[static_cast<UINT>(_Type)]; }

//        eStageState GetStageState() { return dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState(); }

    protected:
        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        CPlayer* mPlayer;

        Vector3 mPos;
        Vector3 mMoveDir;

        float mAttackCooldown;

        bool mbDead;

        std::wstring mBossName;
        std::bitset<static_cast<UINT>(eBossState::End)> mState;

    
    public:
        void SetPlayer(CPlayer* _Player) { mPlayer = _Player; }


    };
}