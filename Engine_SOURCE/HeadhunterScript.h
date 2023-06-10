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
            Throw,
            ThrowEnd,
            Recieve,
            Land,

            End,
        };
        enum class ePattern3
        {
            LungeReady,
            Lunge,
            LungeAttack,

            End,
        };
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

        virtual void Pattern1();
        bool GetStatePattern1(ePattern1 _Type) { return mStatePattern1[static_cast<UINT>(_Type)]; }
        void SetStatePattern1On(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern1Off(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = false; }
        std::wstring GetAimRifleKey();

        virtual void Pattern2();
        bool GetStatePattern2(ePattern2 _Type) { return mStatePattern2[static_cast<UINT>(_Type)]; }
        void SetStatePattern2On(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern2Off(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern3();
        bool GetStatePattern3(ePattern3 _Type) { return  mStatePattern3[static_cast<UINT>(_Type)]; }
        void SetStatePattern3On(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern3Off(ePattern3 _Type) { mStatePattern3[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern4();
        virtual void Pattern5();

        virtual void PatternEnd(UINT _PatternNumber);

        void PlayerReset();


    private:
        CHeadhunter* mHeadhunter;
        CAudioSource* mAudioSource;

        std::bitset<static_cast<UINT>(ePattern1::End)> mStatePattern1;
        float mPattern1_AimingTime;


        std::bitset<static_cast<UINT>(ePattern2::End)> mStatePattern2;

        std::bitset<static_cast<UINT>(ePattern3::End)> mStatePattern3;

        CGameObj* mAttackCollider;


    };
}


