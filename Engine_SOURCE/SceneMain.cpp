#include "SceneMain.h"
#include "TimeMgr.h"
#include "Background.h"
#include "GridScript.h"
#include "FadeScript.h"
#include "PlayerScript.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"

namespace dru
{
	CSceneMain::CSceneMain()
	{
	}
	CSceneMain::~CSceneMain()
	{
	}
	void CSceneMain::Initialize()
	{
		{
			// main Ä«¸Þ¶ó
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);

			renderer::Cameras[static_cast<UINT>(mType)].push_back(cameraComp);
		}

		CScene::Initialize();
	}

	void CSceneMain::update()
	{
		if (CInput::GetKeyDown(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Title);
		}
		CScene::update();
	}

	void CSceneMain::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneMain::render()
	{
		CScene::render();
	}

	void CSceneMain::Enter()
	{
		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		CScene::Exit();
	}

}