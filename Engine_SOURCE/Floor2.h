#pragma once
#include "Platforms.h"

namespace dru
{
	class CFloor2 :
		public CPlatforms
	{
	public:
		CFloor2();
		virtual ~CFloor2();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


	};

}