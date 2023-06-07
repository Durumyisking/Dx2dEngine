#pragma once
#include "LiveGameObj.h"

namespace dru
{
    class CDoor :
        public CLiveGameObj
    {
	public:
		CDoor();
		virtual ~CDoor();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();


    };
}
