#include "SceneMgr.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneMain.h"

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

		mActiveScene = mScenes[static_cast<UINT>(eSceneType::Title)];
		mActiveScene->Initialize();
		
	}

	void CSceneMgr::update()
	{
		mActiveScene->update();
	}

	void CSceneMgr::fixedupdate()
	{
		mActiveScene->fixedupdate();
	}

	void CSceneMgr::render()
	{
		mActiveScene->render();
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
		if(mActiveScene)
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