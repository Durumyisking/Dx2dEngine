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
        WallSlide,
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
        void jumpdelay();

        CAnimator* animator;
        CRigidBody* rigidbody;

        float mAirTime;
        float mAttackTime;
        float mRollTime;

        float mAttackCooldown;
        Vector3 mAttackDir;
        bool mbFirstAttack;

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        

    };
}

