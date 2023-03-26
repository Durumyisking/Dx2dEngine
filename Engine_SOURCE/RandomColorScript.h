#pragma once
#include "Script.h"

namespace dru
{
    class CRandomColorScript :
        public CScript
    {
    public:
        CRandomColorScript();
        virtual ~CRandomColorScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;
    };


}