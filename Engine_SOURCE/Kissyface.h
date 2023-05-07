#pragma once
#include "Boss.h"

namespace dru
{
	class CAxe;
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

		void CraeteAxe();

	private:
		CAnimator* mAnimator;
		CAxe* mAxe;

	};

}