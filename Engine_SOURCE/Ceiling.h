#pragma once
#include "Platforms.h"

namespace dru
{
    class CCeiling :
        public CPlatforms
    {
	public:
		CCeiling();
		virtual ~CCeiling();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
    };

}