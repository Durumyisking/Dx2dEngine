#pragma once
#include "Platforms.h"


namespace dru
{
    class COutWall :
        public CPlatforms
    {
	public:
		COutWall();
		virtual ~COutWall();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();



    };

}
