#pragma once
#include "GameObj.h"

namespace dru
{
    class CBackgroundColor :
        public CGameObj
    {
		friend class CBackgroundColorScript;

	public:
		CBackgroundColor();
		virtual ~CBackgroundColor();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

    };

}