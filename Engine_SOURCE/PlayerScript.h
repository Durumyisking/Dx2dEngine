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
        TutorAttack,// 5 
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

        bool IsOnWall() const { return mbOnWall; }

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


        void rollFrame1();
        void rollFrame2();
        void rollFrame3();
        void rollFrame4();
        void rollFrame5();
        void rollFrame6();
        void rollFrame7();

        void JumpdustComplete();
        void LanddustComplete();
        void RolldustComplete();


        // player action
        void idleToRun();
        void run();
        void crouch();
        void fall();
        void rollTrigger();
        void roll();
        void jump();
        void wallSlide();
        void wallKickTrigger();
        void wallKick();
        void attack();

        void initializeJumpdustComponent();
        void jumpdustSlideCheck();
        void jumpdustRotate(float _Radian);

        void initializeLanddustComponent();


        void createRolldust(UINT _Count);


        void wallLRCheck();


        bool towardToWallCheck_KeyTap();
        bool towardToWallCheck_KeyDown();
        bool NotowardToWallCheck_KeyTap();
        bool NotowardToWallCheck_KeyDown();


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        Vector3 mPos;

        CGameObj* mJumpdust;
        CGameObj* mLanddust;

        float mAirTime;
        float mAttackTime;
        float mRollTime;
        float mWallSlideUpTime;
        float mWallKickTime;
        float mLRKeyupTime;
        float mSlideDustCount;

        float mAttackCooldown;
        Vector3 mAttackDir;

        bool mbFirstAttack;
        bool mbOnWall;
        int mbWallIsLeft; // -1 left 0 none 1 right

        bool mbLRKeyupTimerOn;

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        


	private:
        void PlayLanddust();
        void PlayJumpdust();

        CGameObj* GetOrCreateJumpdustObject();
		CGameObj* GetOrCreateLanddustObject();
    };
}

