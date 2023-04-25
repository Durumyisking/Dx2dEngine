#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CBullet :
		public CLiveGameObj
	{
	public:
		CBullet();
		virtual ~CBullet();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	private:
		CLiveGameObj* mTarget;

	};
}
