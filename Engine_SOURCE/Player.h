#pragma once
#include "GameObj.h"

namespace dru
{
	class CPlayer :
		public CGameObj
	{

	public:
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();



	};
}