#include "SceneMgr.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneTemp.h"
#include "SceneEnding.h"
#include "SceneLoading.h"

namespace dru
{
	CScene* CSceneMgr::mScenes[(static_cast<UINT>(CSceneMgr::eSceneType::End))] = {};
	CScene* CSceneMgr::mActiveScene = nullptr;

	void CSceneMgr::Initialize()
	{
		mScenes[static_cast<UINT>(eSceneType::Title)] = new CSceneTitle;
		mScenes[static_cast<UINT>(eSceneType::Title)]->SetType(eSceneType::Title);
		mScenes[static_cast<UINT>(eSceneType::Main)] = new CSceneMain;
		mScenes[static_cast<UINT>(eSceneType::Main)]->SetType(eSceneType::Main);
		mScenes[static_cast<UINT>(eSceneType::Ending)] = new CSceneEnding;
		mScenes[static_cast<UINT>(eSceneType::Ending)]->SetType(eSceneType::Ending);
		mScenes[static_cast<UINT>(eSceneType::Temp)] = new CSceneTemp;
		mScenes[static_cast<UINT>(eSceneType::Temp)]->SetType(eSceneType::Temp);
		mScenes[static_cast<UINT>(eSceneType::Loading)] = new CSceneLoading;
		mScenes[static_cast<UINT>(eSceneType::Loading)]->SetType(eSceneType::Loading);

		for (UINT i = 0; i < static_cast<UINT>(eSceneType::End); i++)
		{
			mScenes[i]->Initialize();
		}

		mActiveScene = mScenes[static_cast<UINT>(eSceneType::Loading)];
		mActiveScene->Enter();


	}

	void CSceneMgr::update()
	{
		mActiveScene->update();
	}

	void CSceneMgr::fixedUpdate()
	{
		mActiveScene->fixedUpdate();
	}

	void CSceneMgr::render()
	{
		mActiveScene->render();
	}

	void CSceneMgr::fontRender()
	{
		mActiveScene->fontRender();
	}

	void CSceneMgr::destory()
	{
		mActiveScene->destroy();
	}

	void CSceneMgr::release()
	{
		for (CScene* scene : mScenes)
		{
			if (nullptr != scene)
				delete scene;
		}
	}

	void CSceneMgr::LoadScene(eSceneType _Type)
	{
		if (mActiveScene)
			mActiveScene->Exit();

		std::vector<CGameObj*> gameObjs = mActiveScene->GetDontDestroyObjects();

		mActiveScene = mScenes[static_cast<UINT>(_Type)];

		for (CGameObj* obj : gameObjs)
		{
			mActiveScene->AddGameObject(obj, obj->GetLayerType());
		}

		if (mActiveScene)
			mActiveScene->Enter();
	}

	void CSceneMgr::DontDestroyOnLoad(CGameObj* _GameObj)
	{
		if (nullptr == _GameObj)
			return;

		_GameObj->DontDestroy();
	}

}