#pragma once
#include "Monster.h"

namespace dru
{
	class CCop :
		public CMonster
	{
	public:
		CCop();
		virtual ~CCop();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();
	};

}
