#include "SceneEnding.h"
#include "Object.h"

namespace dru
{
	CSceneEnding::CSceneEnding()
		: mBg(nullptr)
		, mCamera(nullptr)
		, mSmoke(nullptr) 
	{
	}

	CSceneEnding::~CSceneEnding()
	{
	}

	void CSceneEnding::Initialize()
	{
		CScene::Initialize();
	}

	void CSceneEnding::update()
	{
		CScene::update();
	}

	void CSceneEnding::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneEnding::render()
	{
		CScene::render();
	}

	void CSceneEnding::Enter()
	{

		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(eProjectionType::Perspective);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
		}

		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}

		{
			// 배경 black
			mBg = object::Instantiate<CBackground>(eLayerType::BackGround, L"bg");
			CSpriteRenderer* Renderer = mBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"endingBgMat");
			Renderer->SetMaterial(Material);
			mBg->SetPos(Vector3(0.f, 0.f, 5.f));
			//mBg->SetScale(Vector3(10.f, 10.f, 1.f));

		}

		CScene::Enter();
	}

	void CSceneEnding::Exit()
	{
		CScene::Exit();
	}


}