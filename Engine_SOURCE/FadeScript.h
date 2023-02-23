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
        virtual void fixedupdate() override;
        virtual void render() override;

        void SetType(int _Type) { mFadeType = _Type; }

    private:
        int mFadeType; // 0 : out 1 : in

    };
}


