#pragma once
#include "Scene.h"
#include "Stage.h"

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

		CGameObj* mMaskTarget;
		
		CBackground* mScreenMask;

		bool mbLoad;

		CPlayer* mPlayer;

		CBackground* mStageBackground;

		std::vector<CStage*> mStages;
		UINT mCurrentStage;
	};

}

