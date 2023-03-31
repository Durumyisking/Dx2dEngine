#pragma once
#include "Platforms.h"
namespace dru
{
    class COutWallSide :
        public CPlatforms
    {
	public:
		COutWallSide();
		virtual ~COutWallSide();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
	};

}