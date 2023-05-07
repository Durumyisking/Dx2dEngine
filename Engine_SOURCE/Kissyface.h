#pragma once
#include "Boss.h"

namespace dru
{
	class CKissyface :
		public CBoss
	{
	public:
		CKissyface();
		virtual ~CKissyface();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


	private:
		CAnimator* mAnimator;
	};

}