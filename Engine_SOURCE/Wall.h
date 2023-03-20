#pragma once
#include "Platforms.h"

namespace dru
{
    class CWall :
        public CPlatforms
    {
	public:
		CWall();
		virtual ~CWall();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();



    };

}