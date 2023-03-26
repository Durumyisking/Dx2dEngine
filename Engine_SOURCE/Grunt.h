#pragma once
#include "Monster.h"

namespace dru
{
	class CGrunt :
		public CMonster
	{
	public:
		CGrunt();
		virtual ~CGrunt();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
	};
}