#pragma once
#include "LiveGameObj.h"

namespace dru
{
    class CBloodDecal :
        public CLiveGameObj
    {
	public:
		CBloodDecal();
		virtual ~CBloodDecal();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();

	};

}