#include "SceneLoading.h"
#include "AsyncLoad.h"
#include "Object.h"
#include "ObjectPool.h"

namespace dru
{
	CSceneLoading::CSceneLoading()
		: mCamera(nullptr)
		, mSmoke(nullptr)
		, mbResourceLoadEnd1(false)
		, mbResourceLoadEnd2(false)
		, mbResourceLoadEnd3(false)
		, mbObjectPoolLoadEnd(false)
		, mbLoadStart(false)

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
		if (mbResourceLoadEnd1 && mbResourceLoadEnd2 && mbObjectPoolLoadEnd)
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Title);
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
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->SmoothOn();
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
			cameraComp->SetProjectionType(eProjectionType::Orthographic);
			mCamera->SetPos(Vector3(0.f, 0.f, 0.f));
		}


		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}

		{
			CBackground* mBg = object::Instantiate<CBackground>(eLayerType::BackGround, L"bg");
			CSpriteRenderer* Renderer = mBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"loadingMat");
			Renderer->SetMaterial(Material);
			mBg->SetPos(Vector3(0.f, 0.f, 5.f));
			mBg->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		{
			CBackground* mFont = object::Instantiate<CBackground>(eLayerType::BackGround, L"bgfont");
			CSpriteRenderer* Renderer = mFont->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"loadingfontMat");

			CAnimator* mAnimator = mFont->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"loadingFont", Material->GetTexture(), { 0.f, 0.f }, { 305.f, 92.f }, Vector2::Zero, 4, { 305.f, 92.f }, 1.f);

			Renderer->SetMaterial(Material);
			mFont->SetPos(Vector3(6.25f, -3.75f, 5.f));
			mFont->SetScale(Vector3(0.125f, 0.5f, 1.f));

			mAnimator->Play(L"loadingFont");
		}

		std::thread thread1(CAsyncLoad::Initialize, &mbResourceLoadEnd1);
		thread1.join();

		std::thread thread2(CAsyncLoad::LoadAfterImageMaterial1, &mbResourceLoadEnd2);
		std::thread thread3(CAsyncLoad::LoadAfterImageMaterial2, &mbResourceLoadEnd3);
		std::thread thread4(CObjectPool::Initialize, &mbObjectPoolLoadEnd);

		// 스레드 함수가 완료될 때까지 대기하지 않고 탈출
		thread2.detach();
		thread3.detach();
		thread4.detach();


		CScene::Enter();
	}

	void CSceneLoading::Exit()
	{
		CScene::Exit();
	}

}
