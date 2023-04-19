#pragma once
#include "Platforms.h"

namespace dru
{
	class CStair :
		public CPlatforms
	{
	public:
		CStair();
		virtual ~CStair();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		float GetDegree() const { return mSlopeDegree; }

	private:
		float mSlopeDegree;
	};

}
