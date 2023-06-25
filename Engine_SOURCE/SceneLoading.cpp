#include "SceneLoading.h"
#include "AsyncLoad.h"
#include "Object.h"
#include "ObjectPool.h"

namespace dru
{
	CSceneLoading::CSceneLoading()
		: mBg(nullptr)
		, mCamera(nullptr)
		, mSmoke(nullptr)
		, mbThreadMade(false)
	{
	}

	CSceneLoading::~CSceneLoading()
	{
	}

	void CSceneLoading::Initialize()
	{
		CScene::Initialize();
	}

	void CSceneLoading::update()
	{
		if (!mbThreadMade)
		{
			std::thread thread(CAsyncLoad::Initialize);
			thread.join();
			mbThreadMade = true;

			std::thread thread2(CObjectPool::Initialize);
			thread2.join();
		}

		CScene::update();
	}

	void CSceneLoading::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneLoading::render()
	{
		CScene::render();
	}

	void CSceneLoading::Enter()
	{

		{
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
			mCamera->DontDestroy();
		}

		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}

		{
			mBg = object::Instantiate<CBackground>(eLayerType::BackGround, L"bg");
			CSpriteRenderer* Renderer = mBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"loadingMat");
			Renderer->SetMaterial(Material);
			mBg->SetPos(Vector3(0.f, 0.f, 5.f));
			mBg->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		CScene::Enter();
	}

	void CSceneLoading::Exit()
	{
		CScene::Exit();
	}

}
