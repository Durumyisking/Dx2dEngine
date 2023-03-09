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
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();


	private:
		CGameObj*	mCamera;
		CGameObj*	mUICamera;

		CGameObj*	mCamTarget;
		CGameObj*	mCamTarget2;
		CGameObj*	mUITarget;

		CBackgroundColor* mUIBg;
		CBackgroundColor* mUIStart;


		CBackground* mbgBlack;
		CBackground* mbgSteel;
		CBackground* mbgChain;
		CBackground* mbgGrass;
		CBackground* mbgKatana;
		CBackground* mbgZer;
		CBackground* mbgO;

		bool mCamMoveDone;
		bool mCamMoveStart;
		bool mUIMoveDone;

		int mMenu;

	};

}

