#pragma once
#include "GameObj.h"

namespace dru
{
	class CKissyHead :
		public CGameObj
	{
	public:
		CKissyHead();
		virtual ~CKissyHead();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


	};
}