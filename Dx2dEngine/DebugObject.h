#pragma once
#include "GameObj.h"

namespace dru
{
	class CDebugObject :
		public CGameObj
	{
	public:
		CDebugObject();
		virtual ~CDebugObject();

		virtual void fixedUpdate();

	};

}
