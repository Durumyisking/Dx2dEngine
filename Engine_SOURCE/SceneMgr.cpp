#include "SceneMgr.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneMain.h"

namespace dru
{
	CScene* CSceneMgr::mScenes[(static_cast<UINT>(CSceneMgr::eSceneType::End))] = {};
	CScene* CSceneMgr::mPlayScene = nullptr;

	void CSceneMgr::Initialize()
	{

		mScenes[static_cast<UINT>(eSceneType::Title)] = new CSceneTitle;
		mScenes[static_cast<UINT>(eSceneType::Title)]->SetType(eSceneType::Title);
		mScenes[static_cast<UINT>(eSceneType::Main)] = new CSceneMain;
		mScenes[static_cast<UINT>(eSceneType::Main)]->SetType(eSceneType::Main);

		mPlayScene = mScenes[static_cast<UINT>(eSceneType::Title)];
		mPlayScene->Initialize();
		
	}

	void CSceneMgr::update()
	{
		mPlayScene->update();
	}

	void CSceneMgr::fixedupdate()
	{
		mPlayScene->fixedupdate();
	}

	void CSceneMgr::render()
	{
		mPlayScene->render();
	}

	void CSceneMgr::release()
	{
		for (CScene* scene : mScenes)
		{
			if (nullptr != scene)
				delete scene;
		}
	}

}