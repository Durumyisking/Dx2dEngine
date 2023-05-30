#pragma once
#include "LiveGameObj.h"

namespace dru
{
    class CSmallBlood :
        public CLiveGameObj
    {
	public:
		CSmallBlood();
		virtual ~CSmallBlood();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();

    };
}