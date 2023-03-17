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
        Thumble,
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


    private:
        void idletorunFrame();
        void idletorun();
        void runtoidle();
        void attacktoidle();
        void jumpdelay();



        float mAirTime;
        float mAttackTime;
        float mAttackCooldown;
        Vector3 mAttackDir;
        bool mbFirstAttack;

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        

    };
}

