#pragma once
#include "BossScript.h"

namespace dru
{
    enum class ePattern1
    {
        Jump,
        Throw,
        ThrowEnd,
        Land,

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
        Throw,
        ThrowEnd,
        Recieve,
        Land,

        End,
    };

    class CKissyface;
    class CKissyfaceScript :
        public CBossScript
    {
    public:
        CKissyfaceScript();
        virtual ~CKissyfaceScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void Reset();

        virtual void Pattern1();
        bool GetStatePattern1(ePattern1 _Type) { return mStatePattern1[static_cast<UINT>(_Type)]; }
        void SetStatePattern1On(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern1Off(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern2();
        bool GetStatePattern2(ePattern2 _Type) { return mStatePattern2[static_cast<UINT>(_Type)]; }
        void SetStatePattern2On(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern2Off(ePattern2 _Type) { mStatePattern2[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern3();
        virtual void Pattern4();
        virtual void Pattern5();

        virtual void PatternEnd(UINT _PatternNumber);

        void SetAxeDir();
        void AxeOn();
        void AxeOff();

        void Block();

        // animation Callback


        // pattern 1   
        void jumpStartComplete();
        void airThrowAxeComplete();
        void airThrowAxeEndEnd();

        // pattern 2   
        void throwAxeFrame5();


        void PlayBulletReflect(Vector3 _Pos);

    private:
        void InitializeBulletReflectComponent();

        void PlayBulletReflect();

        void BulletReflectPositioning();


    private:
        CKissyface* mKissyface;
        std::bitset<static_cast<UINT>(ePattern1::End)> mStatePattern1;

        std::bitset<static_cast<UINT>(ePattern2::End)> mStatePattern2;
        float mPattern2_RecieveWaitingTime;

        std::bitset<static_cast<UINT>(ePattern3::End)> mStatePattern3;

        CGameObj* mBulletReflect;

        bool mbNoAxe;

    public:
        CGameObj* GetOrCreateBulletReflectObject();


    };
}
