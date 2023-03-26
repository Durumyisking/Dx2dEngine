#include "SceneMission.h"
#include "Object.h"
#include "Input.h"
#include "Background.h"
#include "PaintShader.h"

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
	



		CScene::Initialize();
	}
	void CSceneMission::update()
	{

		if (CInput::GetKeyTap(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
		}
		paintShader->OnExcute();
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
		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"PointLight");
			PointLight->SetPos({ 0.f, 0.f, 1.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(10.f);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });

		}

		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
		}

		//{
		//	// 배경 black
		//	mbgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
		//	CSpriteRenderer* SpriteRenderer = mbgBlack->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"Black", Material);
		//	SpriteRenderer->SetMaterial(Material);
		//	mbgBlack->SetPos(Vector3(0.f, -1.f, 5.f));
		//	mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

		//}

		//{
		//	// Left
		//	mJobLeft = object::Instantiate<CGameObj>(eLayerType::BackGround, L"Job_left");
		//	CSpriteRenderer* SpriteRenderer = mJobLeft->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"job_left", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"job_leftMat", Material);
		//	SpriteRenderer->SetMaterial(Material);
		//	mJobLeft->SetPos(Vector3(-2.6f, 0.f, 3.f));
		//	mJobLeft->SetScale(Vector3(0.75f, 0.75f, 1.f));

		//}


		//{
		//	// Right
		//	mJobRight= object::Instantiate<CGameObj>(eLayerType::BackGround, L"Job_right");
		//	CSpriteRenderer* SpriteRenderer = mJobRight->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"job_right", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"job_rightMat", Material);
		//	SpriteRenderer->SetMaterial(Material);
		//	mJobRight->SetPos(Vector3(3.2f, -0.31f, 3.f));
		//	mJobRight->SetScale(Vector3(5.5f, 5.5f, 1.f));

		//}

		{
			paintShader = CResources::Find<CPaintShader>(L"PaintShader");
			//L"SmileTexture"
			std::shared_ptr<CTexture> paintTex = CResources::Find<CTexture>(L"PaintTexture");
			paintShader->SetTarget(paintTex);
			paintShader->OnExcute();


			mJobCorner = object::Instantiate<CGameObj>(eLayerType::Player, L"22");
			CSpriteRenderer* SpriteRenderer = mJobCorner->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> mateiral = CResources::Find<CMaterial>(L"PaintMaterial");
			SpriteRenderer->SetMaterial(mateiral);

			mJobCorner->SetPos(Vector3(0.f, 0.f, 3.f));
			mJobCorner->SetScale(Vector3(8.f, 8.f, 1.f));

		}


		{
			//// Corner
			//mJobCorner= object::Instantiate<CGameObj>(eLayerType::BackGround, L"Job_corner");
			//CSpriteRenderer* SpriteRenderer = mJobCorner->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			//std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"job_corner", L"SpriteShader");
			//CResources::Insert<CMaterial>(L"job_cornerMat", Material);
			//SpriteRenderer->SetMaterial(Material);
			//mJobCorner->SetPos(Vector3(2.9f, -0.75f, 3.f));
			//mJobCorner->SetScale(Vector3(6.f, 6.f, 1.f));

		}


		CScene::Enter();
	}
	void CSceneMission::Exit()
	{
		CScene::Exit();
	}
}
