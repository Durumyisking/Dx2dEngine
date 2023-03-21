#pragma once
#include "Script.h"

namespace dru
{
    enum class ePlayerState
    {
        Idle,
        IdleToRun,
        Run,
        RunToIdle,
        Jump,
        Attack,
        Crouch,
        Roll,
        WallSlideUp,
        WallSlideDown,
        WallKick,
        Fall,

        End,
    };

    class CPlayerScript :
        public CScript
    {
    public:
        CPlayerScript();
        virtual ~CPlayerScript();

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

        void Roll();


    private:
        void idletorunFrame();
        void idletorunEnd();
        void runtoidleEnd();
        void attacktoidleEnd();
        void precrouch();
        void postcrouch();
        void rollEnd();
        void rollComplete();
        void wallkickComplete();


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;

        float mAirTime;
        float mAttackTime;
        float mRollTime;
        float mWallSlideUpTime;
        float mWallKickTime;

        float mAttackCooldown;
        Vector3 mAttackDir;

        bool mbFirstAttack;
        bool mbOnWall;
        int mbWallIsLeft; // -1 left 0 none 1 right

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        

    };
}

