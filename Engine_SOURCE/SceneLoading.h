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
		CBackground* mBg;
		CGameObj* mSmoke;

		std::promise<bool> promise_ResourceLoad;
		std::promise<bool> promise_ObjectPoolLoad;

		std::future<bool> future_ResourceLoad;
		std::future<bool> future_ObjectPoolLoad;


		bool mbResourceLoadEnd;
		bool mbObjectPoolLoadEnd;

		bool mbLoadStart;

	};
}