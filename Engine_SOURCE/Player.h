#pragma once
#include "GameObj.h"

namespace dru
{
	class CPlayer :
		public CGameObj
	{
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	};
}