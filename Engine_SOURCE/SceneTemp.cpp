#include "SceneTemp.h"
#include "SceneMain.h"

namespace dru
{
	CSceneTemp::CSceneTemp()
		: mbChange(false)
	{
	}

	CSceneTemp::~CSceneTemp()
	{
	}

	void CSceneTemp::Initialize()
	{
		CScene::Initialize();
	}

	void CSceneTemp::update()
	{
		if (!mbChange)
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
		}
		CScene::update();
	}

	void CSceneTemp::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneTemp::render()
	{
		CScene::render();
	}

	void CSceneTemp::Enter()
	{
		CScene::Enter();
	}

	void CSceneTemp::Exit()
	{
		CScene::Exit();
	}


}