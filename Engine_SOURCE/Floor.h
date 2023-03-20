#pragma once
#include "Platforms.h"


namespace dru
{
	class CFloor :
		public CPlatforms
	{
	public:
		CFloor();
		virtual ~CFloor();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


	};


}

