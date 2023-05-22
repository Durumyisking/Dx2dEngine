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
        Dead, // 12

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


        void PlayerDead();

        void RewindStart();
        void Reset();

        void SetParticle(CGameObj* _Particle) { mParticle = _Particle; }
        void CreateLaserParticleSystem();

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

        void deadComplete();

        void BulletTimeSwitchOn();
        void BulletTimeSwitchOff();

        // player action
        void idleToRun();
        void run();
        void crouch();
        void fall();
        void fallStart();
        void rollTrigger();
        void rollStart();
        void roll();
        void jump();
        void wallSlide();
        void wallKickTrigger();
        void wallKick();
        void attack();
        void bulletTime();
        void dead();

        void initializeJumpdustComponent();
        void jumpdustSlideCheck();
        void jumpdustRotate(float _Radian);

        void initializeLanddustComponent();

        void bulletTimeStunOperate();

        void createRolldust(UINT _Count);

        void makeSlash();

        void wallLRCheck();

        void collEnter_Floor();
        void collEnter_Floor2(CCollider2D* _oppo);
        void collEnter_Wall(CCollider2D* _oppo);
        void collEnter_MonsterSlash(CCollider2D* _oppo);
        void collEnter_BulletSlash(CCollider2D* _oppo);

        void coll_Wall();


        void hit(Vector3& _enemyPos, int _Type);
        void laserHit();

        bool towardToWallCheck_KeyTap();
        bool towardToWallCheck_KeyDown();
        bool NotowardToWallCheck_KeyTap();
        bool NotowardToWallCheck_KeyDown();

        void SetAfterImageCount(int _Count);


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        Vector3 mPos;

        CGameObj* mJumpdust;
        CGameObj* mLanddust;

        CGameObj* mParticle;

        float mAirTime;
        float mAttackTime;
        float mRollTime;
        float mWallSlideUpTime;
        float mWallKickTime;
        float mLRKeyupTime;
        float mSlideDustCount;

        float mAttackCooldown;
        Vector3 mAttackDir;

        float mBulletTimeGauge;
        float mBulletTimeCooldown;
        bool mbBulletTimeStun;

        float mHitTimer;
        Vector3 mHitDir;

        bool mbFirstAttack;
        bool mbOnWall;
        int mbWallIsLeft; // -1 left 0 none 1 right

        bool mbLRKeyupTimerOn;
        bool mbInputBlock;

        bool mbOnFloor2;

        std::bitset<static_cast<UINT>(ePlayerState::End)> mState;        

        float mLaserHitElapsedTimeX;
        float mLaserHitElapsedTimeY;

    public:
        bool IsOnWall() const { return mbOnWall; }
        float GetBulletTimeGauge() const { return mBulletTimeGauge; }

        void InputBlocking() { mbInputBlock = true; }
        void UnInputBlocking() { mbInputBlock = false; }

        void BulletTimeStun() { mbBulletTimeStun = true; }

        bool GetPlayerState(ePlayerState _state) const { return mState[(UINT)_state]; }
        void SetPlayerState(ePlayerState _state, bool _value) { mState[(UINT)_state] = _value; }
        void SetPlayerSingleState(ePlayerState _state);


	private:
        void PlayLanddust();
        void PlayJumpdust();

        CGameObj* GetOrCreateJumpdustObject();
		CGameObj* GetOrCreateLanddustObject();
     
    };
}

