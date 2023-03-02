#pragma once
#include "Script.h"

namespace dru
{
    class CBackgroundColorScript :
        public CScript
    {
    public:
        CBackgroundColorScript();
        virtual ~CBackgroundColorScript();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();

        void SetColor(math::Vector4 _RGBA) { mColor = _RGBA; }

    private:
        math::Vector4 mColor;
    };
}


