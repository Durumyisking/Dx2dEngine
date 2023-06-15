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
            WallKickReady,
            WallKick,
            WallKickAttack,
            WallKickFall,
            WallKickLand,

            End,
        };
        enum class ePattern3
        {
            Takeout,
            Dash,
            DashEnd,
            PutBack,

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
            DashEnd,

            End,
        };
        enum class ePattern6
        {
            VerticalLaserAppear,
            VerticalLaserDisappear,
            SweepStartL,
            SweepL,
            SweepDisappearL,
            SweepStartR,
            SweepR,
            SweepDisappearR,
            Dash,
            DashEnd,

            End,
        };

#define DASH_TIMER 0.25f

#define MV_BACKJUMP math::Vector3(1.7021f, 12.5f, 0.f)
#define MV_WALLKICK math::Vector3(9.f, 12.f, 0.f)
#define MV_DODGE math::Vector3(8.f, 6.f, 0.f)



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

        void CreateBullet(float _Angle);

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
        void WallKickReady();
        void WallKick();
        void WallKickAttackStart();


        virtual void Pattern3();
        bool GetStatePattern3(ePattern3 _Type) { return  mStatePattern3[static_cast<UINT>(_Type)]; }
        void SetStatePattern3On(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern3Off(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern4();
        bool GetStatePattern4(ePattern5 _Type) { return  mStatePattern4[static_cast<UINT>(_Type)]; }
        void SetStatePattern4On(ePattern5 _Type) { mStatePattern4[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern4Off(ePattern5 _Type) { mStatePattern4[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern5();
        bool GetStatePattern5(ePattern5 _Type) { return  mStatePattern5[static_cast<UINT>(_Type)]; }
        void SetStatePattern5On(ePattern5 _Type) { mStatePattern5[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern5Off(ePattern5 _Type) { mStatePattern5[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern6();
        bool GetStatePattern6(ePattern6 _Type) { return  mStatePattern6[static_cast<UINT>(_Type)]; }
        void SetStatePattern6On(ePattern6 _Type) { mStatePattern6[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern6Off(ePattern6 _Type) { mStatePattern6[static_cast<UINT>(_Type)] = false; }
        void SwitchVerticalLaserLR();

        virtual void PatternEnd();

        void PlayerReset();
        void PushPlayer();

        CGameObj* GetOrCreateExplosionObject();
        void InitializeExplosionComponent();
        void PlayExplosion();
        void ExplosionPositioning();

        CGameObj* GetOrCreateBeamObject();
        void InitializeBeamComponent();
        void PlayBeam();
        void BeamPositioning();


    private:
        CHeadhunter* mHeadhunter;
        CAudioSource* mAudioSource;
        CGameObj* mExplosion;
        CGameObj* mBeam;
        CTransform* mBeamTransform;


        float mDodgeCooldown;
        float mDodgeRadius;
        float mDodgeTimer;

        float mDashElapsedTime;
        Vector3 mDashOrigin;
        Vector3 mDashDest;

        float mHideTimer;

        std::bitset<static_cast<UINT>(ePattern1::End)> mStatePattern1;
        float mPattern1_AimingTime;
        std::wstring mPattern1_ShootAnimName;

        std::bitset<static_cast<UINT>(ePattern2::End)> mStatePattern2;
        UINT mPattern2_ShootedBulletCountL;
        UINT mPattern2_ShootedBulletCountR;

        std::bitset<static_cast<UINT>(ePattern3::End)> mStatePattern3;

        std::bitset<static_cast<UINT>(ePattern4::End)> mStatePattern4;

        std::bitset<static_cast<UINT>(ePattern5::End)> mStatePattern5;

        std::bitset<static_cast<UINT>(ePattern6::End)> mStatePattern6;
        UINT mPattern6_VerticalShootCount;


        CGameObj* mAttackCollider;


    };
}


