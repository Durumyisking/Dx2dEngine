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

		void SetTarget(CLiveGameObj* _Target) { mTarget = _Target; }
		CLiveGameObj* GetTarget() const { return mTarget; }
	private:
		CLiveGameObj* mTarget;
		bool mbReflected;

	};
}
