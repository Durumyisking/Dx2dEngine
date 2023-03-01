#include "SceneTitle.h"
#include "TimeMgr.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"

namespace dru
{
	CSceneTitle::CSceneTitle()
	{
	}

	CSceneTitle::~CSceneTitle()
	{

	}

	void CSceneTitle::Initialize()
	{
		mDeleteObj = true;
		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->SmoothOn();
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::Cameras[static_cast<UINT>(mType)].push_back(cameraComp);
		}
		{
			// ui 카메라
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			mUICamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::Cameras[static_cast<UINT>(mType)].push_back(cameraComp);
		}

		{
			//// gridobj
			//CGameObj* gridObj = object::Instantiate<CGameObj>(eLayerType::Grid, L"Grid");
			//CMeshRenderer* MeshRenderer = gridObj->AddComponent<CMeshRenderer>(eComponentType::MeshRenderer);
			//MeshRenderer->SetMaterial(CResources::Find<CMaterial>(L"GridMaterial"));
			//gridObj->AddComponent<CGridScript>(eComponentType::Script);

		}


		std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"Rectmesh");

		{			
			{
				// 배경 black
				mbgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
				CSpriteRenderer* SpriteRenderer = mbgBlack->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgBlack->SetPos(Vector3(0.f, -1.f, 1.f));
				mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

			}

			{
				// 배경 Steel
				mbgSteel = object::Instantiate<CBackground>(eLayerType::BackGround, L"Steel");
				CSpriteRenderer* SpriteRenderer = mbgSteel->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
	
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Steel", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Steel", Material);
 				SpriteRenderer->SetMaterial(Material);
				mbgSteel->SetPos(Vector3(0.f, -0.2f, 1.f));
				mbgSteel->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}

			{
				// 배경 TitleZer
				mbgZer = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleZer_1");
				CSpriteRenderer* SpriteRenderer = mbgZer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleZer_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleZer_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgZer->SetPos(Vector3(-0.09f, -0.45f, 0.81f));
				mbgZer->SetScale(Vector3(0.25f, 0.25f, 1.f));
			}


			{
				// 배경 TitleO
				mbgO = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleO_1");
				CSpriteRenderer* SpriteRenderer = mbgO->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleO_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleO_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgO->SetPos(Vector3(0.26f, -0.45f, 0.81f));
				mbgO->SetScale(Vector3(0.025f, 0.025f, 1.f));
			}

			{
				// 배경 TitleKatana
				mbgKatana = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleKatana");
				CSpriteRenderer* SpriteRenderer = mbgKatana->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleKatana", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleKatana", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgKatana->SetPos(Vector3(0.f, -0.3f, 0.8f));
				mbgKatana->SetScale(Vector3(0.3f, 0.3f, 1.f));
			}


			{
				// 배경 Fence
				mbgChain = object::Instantiate<CBackground>(eLayerType::BackGround, L"Fence");
				CSpriteRenderer* SpriteRenderer = mbgChain->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Fence", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Fence", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgChain->SetPos(Vector3(0.f, 0.1f, 0.7f));
				mbgChain->SetScale(Vector3(1.28f, 1.28f, 1.f));
			}

			{
				// 배경 Grass
				mbgGrass = object::Instantiate<CBackground>(eLayerType::BackGround, L"Grass");
				CSpriteRenderer* SpriteRenderer = mbgGrass->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Grass", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Grass", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgGrass->SetPos(Vector3(0.f, -1.f, 0.69f));
				mbgGrass->SetScale(Vector3(0.15f, 0.15f, 1.f));
			}

			{
				//// 배경 UI

				mbgUIBlack = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"Black");
				CSpriteRenderer* SpriteRenderer = mbgUIBlack->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				mbgUIBlack->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"ColorMaterial");
				SpriteRenderer->SetMaterial(Material);
				mbgUIBlack->SetPos(Vector3(0.f, -1.35f, 0.5f));
				mbgUIBlack->SetScale(Vector3(0.3f, 0.3f, 1.f));
			}



			{
				mCamTarget = object::Instantiate<CBackground>(eLayerType::None, L"CamTargetTitleScene");
				mCamTarget->SetPos(Vector3(0.f, -0.6f, 1.f));
				mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}

		}

		mCamera->GetComponent<CCamera>()->SetTarget(mCamTarget);
		
		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		if (CInput::GetKeyDown(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
		}

		CScene::update();
	}

	void CSceneTitle::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}

	void CSceneTitle::Enter()
	{
		CScene::Enter();
	}

	void CSceneTitle::Exit()
	{
		CScene::Exit();
	}


}