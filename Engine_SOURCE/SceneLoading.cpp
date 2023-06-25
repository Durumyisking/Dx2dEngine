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
		, mbResourceLoadEnd(false)
		, mbObjectPoolLoadEnd(false)
		, mbLoadStart(false)
		, promise_ResourceLoad{}
		, promise_ObjectPoolLoad{}
		, future_ResourceLoad{}
		, future_ObjectPoolLoad{}

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
		mbResourceLoadEnd = future_ResourceLoad.get();
		mbObjectPoolLoadEnd = future_ObjectPoolLoad.get();

		if (mbResourceLoadEnd && mbObjectPoolLoadEnd)
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
			mBg = object::Instantiate<CBackground>(eLayerType::BackGround, L"bg");
			CSpriteRenderer* Renderer = mBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"loadingMat");
			Renderer->SetMaterial(Material);
			mBg->SetPos(Vector3(0.f, 0.f, 5.f));
			mBg->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		future_ResourceLoad = promise_ResourceLoad.get_future();
		future_ObjectPoolLoad = promise_ObjectPoolLoad.get_future();

		std::thread thread1(CAsyncLoad::Initialize, std::ref(promise_ResourceLoad));
		std::thread thread2(CObjectPool::Initialize, std::ref(promise_ObjectPoolLoad));

		// 스레드 함수가 완료될 때까지 대기하지 않고 탈출
		thread1.detach();
		thread2.detach();

		// 비동기 쓰레드 호출
		//std::future<void> thread1 = std::async(std::launch::async, CAsyncLoad::Initialize, std::ref(promise_ResourceLoad));
		//std::future<void> thread2 = std::async(std::launch::async, CObjectPool::Initialize, std::ref(promise_ObjectPoolLoad));


		CScene::Enter();
	}

	void CSceneLoading::Exit()
	{
		CScene::Exit();
	}

}
