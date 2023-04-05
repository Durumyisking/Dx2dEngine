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

		CStage* GetCurrentStage() { return mStages[mCurrentStage]; }


		void SetPlayer(CPlayer* _player) { mPlayer = _player; }
		CPlayer* Getplayer() const { return mPlayer; }

		void SetStage(UINT _stage) { mCurrentStage = _stage; }

	private:
		CGameObj* mCamera;
		CGameObj* mUICamera;

		CGameObj* mUICursor;

		CGameObj* mMaskTarget;
		
		CBackground* mScreenMask;


		CPlayer* mPlayer;

		std::vector<CStage*> mStages;
		UINT mCurrentStage;
	};

}

