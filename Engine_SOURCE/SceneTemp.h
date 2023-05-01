#pragma once
#include "Scene.h"

namespace dru
{
    class CSceneTemp :
        public CScene
    {
	public:
		CSceneTemp();
		virtual ~CSceneTemp();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();


	private:
		bool mbChange;
    };
}