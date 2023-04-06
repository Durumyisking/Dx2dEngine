#pragma once
#include "GameObj.h"


namespace dru
{
	class CMonsterRay :
		public CGameObj
	{
	public:
		CMonsterRay();
		virtual ~CMonsterRay();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
	};

}