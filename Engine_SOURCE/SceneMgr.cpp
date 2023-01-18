#include "SceneMgr.h"

#include "Scene.h"

#include "SceneTitle.h"
#include "SceneMain.h"


namespace dru
{
	CScene* mScenes[(static_cast<UINT>(CSceneMgr::eSceneType::End))] = {};
	CScene*  mPlayScene = nullptr;

	CSceneMgr::CSceneMgr()
	{
	}
	CSceneMgr::~CSceneMgr()
	{
	}

	void CSceneMgr::init()
	{
		mScenes[static_cast<UINT>(eSceneType::Title)] = new CSceneTitle;
		mScenes[static_cast<UINT>(eSceneType::Title)]->SetType(eSceneType::Title);
		mScenes[static_cast<UINT>(eSceneType::Main)] = new CSceneMain;
		mScenes[static_cast<UINT>(eSceneType::Main)]->SetType(eSceneType::Main);

		mPlayScene = mScenes[static_cast<UINT>(eSceneType::Title)];
	}

	void CSceneMgr::update()
	{
		mPlayScene->update();

	}

	void CSceneMgr::fixedupdate()
	{
	}

	void CSceneMgr::render()
	{
	}

}