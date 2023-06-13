#pragma once
#include "Script.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Player.h"

#define VELOCITY_RUN dru::math::Vector3(5.f, 7.f, 0.f)
#define VELOCITY_WALK dru::math::Vector3(1.f, 7.f, 0.f)

#define SCREEN_CENTER dru::math::Vector3(0.f, 0.f, 0.f)
#define SCREEN_CENTERTOP dru::math::Vector3(0.f, 2.5f, 0.f)
#define SCREEN_LEFTTOP dru::math::Vector3(-7.f, 2.5f, 0.f)
#define SCREEN_RIGHTTOP dru::math::Vector3(7.f, 2.5f, 0.f)

#define SCREEN_CENTERFLOOR dru::math::Vector3(0.f, -1.99f, 0.f)


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
        Pattern6,
        Fall,
        Hurt,
        Block,
        Dodge,
        Hide,
        Dead,
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
        virtual void Pattern6() = 0;

        void CheckPlayerLeft();

        void ChoosePattern();

        virtual void PatternEnd(UINT _PatternNumber);

        void IdleOperate();
        void PatternOperate();

        bool Patterning();

        bool FlipTest();
        void FlipCheck();

        void SetSingleState(eBossState _Type);
        bool GetState(eBossState _Type) const { return mState[static_cast<UINT>(_Type)]; }

        float GetDistanceOfPlayer();
//        eStageState GetStageState() { return dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState(); }

        void SetHitDir();


    protected:
        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        CPlayer* mPlayer;

        Vector3 mPos;
        Vector3 mMoveDir;

        UINT mPatternCount;

        float mAttackCooldown;

        bool mbDead;
        bool mbIsPlayerLeft;

        bool mbFlipWhilePattern;

        std::wstring mBossName;
        std::bitset<static_cast<UINT>(eBossState::End)> mState;

    
    public:
        void SetPlayer(CPlayer* _Player) { mPlayer = _Player; }


    };
}