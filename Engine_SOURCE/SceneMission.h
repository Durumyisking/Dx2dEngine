#pragma once
#include "Scene.h"

namespace dru
{

    class CSceneMission :
        public CScene
    {
	public:
		CSceneMission();
		virtual ~CSceneMission();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();

	private:
		CGameObj* mCamera;

		CBackground* mbgBlack;

		CGameObj* mJobLeft;
		CGameObj* mJobRight;
		CGameObj* mJobCorner;


    };


}