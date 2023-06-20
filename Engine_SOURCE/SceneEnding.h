#pragma once
#include "Scene.h"

namespace dru
{
    class CSceneEnding :
        public CScene
    {
	public:
		CSceneEnding();
		virtual ~CSceneEnding();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void destroy();

		virtual void Enter();
		virtual void Exit();



    };
}
