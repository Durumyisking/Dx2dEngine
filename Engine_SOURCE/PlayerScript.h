#pragma once
#include "Script.h"

namespace dru
{
    enum class ePlayerState
    {
        Idle, //0
        IdleToRun, // 1
        Run,// 2
        RunToIdle,// 3
        Jump,// 4
        Attack,// 5 
        Crouch,// 6
        Roll,// 7
        WallSlideUp,// 8
        WallSlideDown,// 9
        WallKick,// 10
        Fall,// 11

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
        // anim function
        void idletorunFrame();
        void idletorunEnd();
        void runtoidleEnd();
        void attacktoidleEnd();
        void precrouch();
        void postcrouch();
        void rollEnd();
        void rollComplete();
        void wallkickComplete();

        // player action
        void roll();
        void wallKickTrigger();
        void wallKick();


        void wallLRCheck();



        bool towardToWallCheck_KeyTap();
        bool towardToWallCheck_KeyDown();
        bool NotowardToWallCheck_KeyTap();
        bool NotowardToWallCheck_KeyDown();


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;

        float mAirTime;
        float mAttackTime;
        float mRollTime;
        float mWallSlideUpTime;
        float mWallKickTime;
        float mLRKeyupTime;


        float mAttackCooldown;
        Vector3 mAttackDir;

        bool mbFirstAttack;
        bool mbOnWall;
        int mbWallIsLeft; // -1 left 0 none 1 right

        bool mbLRKeyupTimerOn;

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        

    };
}

