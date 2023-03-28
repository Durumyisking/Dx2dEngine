#pragma once
#include "Script.h"

namespace dru
{
    class CFadeScript :
        public CScript
    {
    public:
        CFadeScript();
        virtual ~CFadeScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        void SetFadeType(int _Type) { mFadeType = _Type; }

        void SetFadeValue(float _Value) { mFadeValue = _Value; }
        void SetFadeTextureType(int _Value) { mFadeTextureType = _Value; }

        void restart(int _fadeType);


    private:
        int   mFadeType;
        int   mFadeTextureType;
        float mFadeValue;
        float mtime;

        bool  mStart;

    };
}


