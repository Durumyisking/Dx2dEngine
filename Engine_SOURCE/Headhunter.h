#pragma once
#include "Boss.h"

namespace dru
{
	class CHeadhunter :
		public CBoss
	{
	public:
		CHeadhunter();
		virtual ~CHeadhunter();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();


	private:
		CAnimator* mAnimator;
	};
}
