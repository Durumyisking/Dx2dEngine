#include "SceneMission.h"
#include "Object.h"

namespace dru
{
	CSceneMission::CSceneMission()
		: mCamera(nullptr)
	{
	}
	CSceneMission::~CSceneMission()
	{
	}
	void CSceneMission::Initialize()
	{
		{
			// main Ä«¸Þ¶ó
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
		}


		CScene::Initialize();
	}
	void CSceneMission::update()
	{

		CScene::update();
	}
	void CSceneMission::fixedUpdate()
	{
		CScene::fixedUpdate();
	}
	void CSceneMission::render()
	{
		CScene::render();
	}
	void CSceneMission::Enter()
	{
		CScene::Enter();
	}
	void CSceneMission::Exit()
	{
		CScene::Exit();
	}
}
