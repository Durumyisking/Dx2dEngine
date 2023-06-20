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

		void PauseMenuOperate();

		CStage* GetCurrentStage() { return mStages[mCurrentStage]; }
		
		UINT GetCurrentStageNumber() { return mCurrentStage; }
		void SetStage(UINT _stage) { mCurrentStage = _stage; }


		void SetPlayer(CPlayer* _player) { mPlayer = _player; }
		CPlayer* Getplayer() const { return mPlayer; }


	private:
		CGameObj* mCamera;
		CGameObj* mUICamera;

		CGameObj* mUICursor;

		CGameObj* mPauseMenuBg;
		CGameObj* mPauseMenuSelector;
		UINT mPauseMenuNumber;
		UINT mPauseMenuDepth;
		UINT mPauseMenuPlayerAfterimageColor;

		CGameObj* mMaskTarget;
		
		CBackground* mScreenMask;


		CPlayer* mPlayer;

		std::vector<CStage*> mStages;
		UINT mCurrentStage;

	};

}

