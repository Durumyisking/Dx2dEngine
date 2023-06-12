#pragma once
#include "BossScript.h"

namespace dru
{

    class CHeadhunter;
    class CHeadhunterScript :
        public CBossScript
    {
        enum class ePattern1
        {
            Takeout,
            Aim,
            Shoot,
            Putback,
            End,
        };
        enum class ePattern2
        {
            BackJump,
            WallKick,
            WallKickAttack,
            WallKickFall,
            WallKickLand,

            End,
        };
        enum class ePattern3
        {
            LungeReady,
            Lunge,
            LungeAttack,

            End,
        };
        enum class ePattern4
        {
            LungeReady,
            Lunge,
            LungeAttack,

            End,
        };
        enum class ePattern5
        {
            SweepStart,
            Sweep,
            Dash,
            DashLand,

            End,
        };

#define DASH_TIMER 0.25f
#define BACKJUMP_FORCE_X 89.361702f
#define BACKJUMP_TIMER 0.5f
#define WALLKICK_TIMER 0.4f


    public:
        CHeadhunterScript();
        virtual ~CHeadhunterScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void Reset();

        void AllPatternReset();
        void AfterImageReset();

        void AddAnimationCallBack();
        void AddAnimationCallBack_Lamda();

        void DodgeOperate();
        void DodgeStart();
        void SetDodgeDir();
        void Hide();
        void DashOperate();
        void Dash();
        void DashEnd();
        void Hit();

        virtual void Pattern1();
        bool GetStatePattern1(ePattern1 _Type) { return mStatePattern1[static_cast<UINT>(_Type)]; }
        void SetStatePattern1On(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern1Off(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = false; }
        std::wstring GetAimRifleKey();
        void AimingOperate();

        virtual void Pattern2();
        bool GetStatePattern2(ePattern2 _Type) { return mStatePattern2[static_cast<UINT>(_Type)]; }
        void SetStatePattern2On(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern2Off(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = false; }
        void BackJump();
        void SetBackJumpForce();
        void WallKick();
        void WallKickAttackStart();


        virtual void Pattern3();
        bool GetStatePattern3(ePattern3 _Type) { return  mStatePattern3[static_cast<UINT>(_Type)]; }
        void SetStatePattern3On(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern3Off(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern4();

        virtual void Pattern5();
        bool GetStatePattern5(ePattern5 _Type) { return  mStatePattern5[static_cast<UINT>(_Type)]; }
        void SetStatePattern5On(ePattern5 _Type) { mStatePattern5[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern5Off(ePattern5 _Type) { mStatePattern5[static_cast<UINT>(_Type)] = false; }

        virtual void PatternEnd();

        void PlayerReset();
        void PushPlayer();

        CGameObj* GetOrCreateExplosionObject();
        void InitializeExplosionComponent();
        void PlayExplosion();
        void ExplosionPositioning();



    private:
        CHeadhunter* mHeadhunter;
        CAudioSource* mAudioSource;
        CGameObj* mExplosion;

        float mDodgeCooldown;
        float mDodgeRadius;
        float mDodgeTimer;

        float mDashElapsedTime;
        Vector3 mDashOrigin;
        Vector3 mDashDest;

        float mHideTimer;

        std::bitset<static_cast<UINT>(ePattern1::End)> mStatePattern1;
        float mPattern1_AimingTime;

        std::bitset<static_cast<UINT>(ePattern2::End)> mStatePattern2;

        std::bitset<static_cast<UINT>(ePattern3::End)> mStatePattern3;

        std::bitset<static_cast<UINT>(ePattern4::End)> mStatePattern4;

        std::bitset<static_cast<UINT>(ePattern5::End)> mStatePattern5;

        CGameObj* mAttackCollider;


    };
}


