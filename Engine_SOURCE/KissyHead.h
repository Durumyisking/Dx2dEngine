#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CKissyHead :
		public CLiveGameObj
	{
	public:
		CKissyHead();
		virtual ~CKissyHead();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();


	};
}