#pragma once
#include "GameObj.h"

namespace dru
{
    class CMonster :
        public CGameObj
    {
	public:
		CMonster();
		virtual ~CMonster();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
    };
}

