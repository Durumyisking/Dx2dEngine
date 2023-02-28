#pragma once
#include "../Engine_SOURCE/GameObj.h"

namespace dru
{
	class CDebugObject :
		public CGameObj
	{
	public:
		CDebugObject();
		virtual ~CDebugObject();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
	};

}
