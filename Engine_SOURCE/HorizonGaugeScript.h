#pragma once
#include "Script.h"

namespace dru
{
    class CHorizonGaugeScript :
        public CScript
    {
    public:
        CHorizonGaugeScript();
        virtual ~CHorizonGaugeScript();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();

        void SetColor(math::Vector4 _RGBA) { mColor = _RGBA; }
        void SetTimer(float _Timer) { mTimer = _Timer; }

        void Play();

    private:
        CTransform* mTransform;
        Vector4 mColor;
        Vector3 mDefaultPosition;
        Vector3 mDefaultScale;

        float mTimer;
        float mElapsedTime;

        bool mbPlaySwitch;

    };
}


