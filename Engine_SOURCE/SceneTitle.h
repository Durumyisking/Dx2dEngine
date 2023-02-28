#pragma once
#include "Scene.h"

namespace dru
{

	class CBackground;

    class CSceneTitle :
        public CScene
    {
	public:
		CSceneTitle();
		virtual ~CSceneTitle();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();


	private:
		CGameObj*	mCamera;
		CGameObj*	mCamTarget;

		CBackground* mbgBlack;
		CBackground* mbgSteel;
		CBackground* mbgChain;
		CBackground* mbgGrass;
		CBackground* mbgTitle;


	};

}

