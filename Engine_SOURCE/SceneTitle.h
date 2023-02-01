#pragma once
#include "Scene.h"

namespace dru
{

    class CSceneTitle :
        public CScene
    {
	public:
		CSceneTitle();
		virtual ~CSceneTitle();

		virtual void Initialize();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();



    };

}

