#pragma once
#include "Script.h"

namespace dru
{
    class CBlinkScript :
        public CScript
    {
    public:
        CBlinkScript();
        virtual ~CBlinkScript();

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

        void SetOnTime(float _value) { mOnTime = _value; }
        void SetOffTime(float _value) { mOffTime = _value; }

        void SwitchOn() { mSwitch = true; }
        void SwitchOff() { mSwitch = false; }

    private:
        bool mSwitch;
        bool mIsBlinking;
        bool mIsRandom;
        float mTimer;
        float mOnTime;
        float mOffTime;
    };

}