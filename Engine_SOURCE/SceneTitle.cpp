#include "SceneTitle.h"
#include "TimeMgr.h"
#include "Background.h"
#include "GridScript.h"
#include "FadeScript.h"
#include "Object.h"
#include "Camera.h"

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

		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::Cameras.push_back(cameraComp);
		}
		{
			//// ui 카메라
			//CGameObj* camera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			//CCamera* cameraComp = camera->AddComponent<CCamera>();
			//cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			//cameraComp->DisableLayerMasks();
			//cameraComp->TurnLayerMask(eLayerType::UI, true);
			//camera->AddComponent<CCameraScript>();
			//renderer::Cameras.push_back(cameraComp);
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

				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", SpriteMaterial);
				SpriteRenderer->SetMaterial(SpriteMaterial);
				mbgBlack->SetPos(Vector3(0.f, -1.f, 1.f));
				mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

			}

			{
				// 배경 Steel
				mbgSteel = object::Instantiate<CBackground>(eLayerType::BackGround, L"Steel");
				CSpriteRenderer* SpriteRenderer = mbgSteel->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
	
				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Steel", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Steel", SpriteMaterial); 
 				SpriteRenderer->SetMaterial(SpriteMaterial);
				mbgSteel->SetPos(Vector3(0.f, -0.2f, 1.f));
				mbgSteel->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}

			{
				// 배경 Chain
				mbgChain = object::Instantiate<CBackground>(eLayerType::BackGround, L"Chain");
				CSpriteRenderer* SpriteRenderer = mbgChain->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Chain", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Chain", SpriteMaterial);
				SpriteRenderer->SetMaterial(SpriteMaterial); 
				mbgChain->SetPos(Vector3(0.f, 0.1f, 0.7f));
				mbgChain->SetScale(Vector3(1.28f, 1.28f, 1.f));
			}

			{
				// 배경 Grass
				mbgGrass = object::Instantiate<CBackground>(eLayerType::BackGround, L"Grass");
				CSpriteRenderer* SpriteRenderer = mbgGrass->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Grass", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Grass", SpriteMaterial);
				SpriteRenderer->SetMaterial(SpriteMaterial);
				mbgGrass->SetPos(Vector3(0.f, -0.85f, 0.69f));
				mbgGrass->SetScale(Vector3(0.15f, 0.15f, 1.f));
			}

		}

		mCamera->GetComponent<CCamera>()->SetTarget(mbgSteel);
		
		CScene::Initialize();
	}

	void CSceneTitle::update()
	{

		CScene::update();
	}

	void CSceneTitle::fixedupdate()
	{
		//Vector3 pos = mCamera->GetPos();
		//pos.y -= 1.f * CTimeMgr::DeltaTime();
		//mCamera->SetPos(pos);
		CScene::fixedupdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}


}