#pragma once
#include "Boss.h"

namespace dru
{
	class CAxe;
	class CAxeScript;
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
		virtual void rewindRender();

		void CraeteAxe();

	private:
		CAnimator* mAnimator;
		CAxe* mAxe;

	public:
		CAxeScript* GetAxeScript() const { return mAxe->GetScript<CAxeScript>(); }
		CAxe* GetAxe() const { return mAxe; }
		CLiveGameObj* GetAxe() { return mAxe; }
	};

}