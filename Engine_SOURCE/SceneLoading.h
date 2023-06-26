#pragma once
#include "Scene.h"

namespace dru
{

	class CSceneLoading :
		public CScene
	{
	public:
		CSceneLoading();
		virtual ~CSceneLoading();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void Enter();
		virtual void Exit();


	private:
		CGameObj* mCamera;
		CGameObj* mSmoke;

		bool mbResourceLoadEnd;
		bool mbObjectPoolLoadEnd;

		bool mbLoadStart;

	};
}