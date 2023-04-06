#pragma once
#include "Script.h"

namespace dru
{

    class CBodyShadeScript :
        public CScript
    {
    public:
        CBodyShadeScript();
        virtual ~CBodyShadeScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        void SetMonster(CGameObj* _Owner) { mMonster = _Owner; }

    private:
        void animComplete();

    private:
        CGameObj* mMonster;
        CAnimator* mAnimator;

    };


}