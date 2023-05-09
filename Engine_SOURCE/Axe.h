#pragma once
#include "LiveGameObj.h"

namespace dru
{
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

	};
}