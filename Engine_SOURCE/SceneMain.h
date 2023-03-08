#pragma once
#include "Scene.h"

namespace dru
{
	class CSceneMain :
		public CScene
	{
	public:
		CSceneMain();
		virtual ~CSceneMain();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();


	private:
		CGameObj* mCamera;
		CGameObj* mUICamera;

		CGameObj* mUICursor;
		std::vector<CGameObj*> mHudBatteryParts;
		CGameObj* mHudTimerBar;
		CGameObj* mHudLeftHand;
		CGameObj* mHudRightHand;

		
		CPlayer* mPlayer;

		CBackground* mStageBackground;

		

	};

}

