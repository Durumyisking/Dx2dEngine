#pragma once
#include "GameObj.h"

namespace dru
{
    class CBackgroundColor :
        public CGameObj
    {
	public:
		CBackgroundColor();
		virtual ~CBackgroundColor();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void SetColor(Vector4 _RGBA) { mColor = _RGBA; }

		Vector4 mColor;
    };

}