#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CKissyface;
	class CAxe :
		public CLiveGameObj
	{
	public:
		CAxe();
		virtual ~CAxe();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();

	private:
		CKissyface* mKissyface;

	public:
		CKissyface* GetKissyface() const { return mKissyface; }
		void SetKissyface(CKissyface* _Kissyface) { mKissyface = _Kissyface; }
	};
}