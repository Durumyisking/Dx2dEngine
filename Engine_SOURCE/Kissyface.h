#pragma once
#include "Monster.h"

namespace dru
{
	class CKissyface :
		public CMonster
	{
	public:
		CKissyface();
		virtual ~CKissyface();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
	};

}