#pragma once
#include "Script.h"

namespace dru
{
    class CPlayerScript :
        public CScript
    {
    public:
        CPlayerScript();
        virtual ~CPlayerScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedupdate() override;
        virtual void render() override;

    };
}

