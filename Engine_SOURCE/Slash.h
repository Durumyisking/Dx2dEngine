#pragma once
#include "GameObj.h"

namespace dru
{
	class CSlash :
		public CGameObj
	{

	public:
		CSlash();
		virtual ~CSlash();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	};


}

