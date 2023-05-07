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

        virtual void Pattern1();
        bool GetStatePattern1(ePattern1 _Type) { return mStatePattern1[static_cast<UINT>(_Type)]; }
        void SetStatePattern1On(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = true; }
        void SetStatePattern1Off(ePattern1 _Type) { mStatePattern1[static_cast<UINT>(_Type)] = false; }

        virtual void Pattern2();
        virtual void Pattern3();
        virtual void Pattern4();
        virtual void Pattern5();

        virtual void PatternEnd(UINT _PatternNumber);


        // animation Callback

        // pattern 1   
        void waitingEndComplete();
        void jumpStartComplete();
        void airThrowAxeComplete();
        void landComplete();

    private:
        CKissyface* mKissyface;
        std::bitset<static_cast<UINT>(ePattern1::End)> mStatePattern1;
        float mPattern1_AirTime;

    };
}
