#include "SceneTitle.h"
#include "TimeMgr.h"
#include "Background.h"
#include "GridScript.h"

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
			CGameObj* camera = new CGameObj();
			CTransform* cameraTR = new CTransform();
			cameraTR->SetPosition(Vector3(0.f, 0.f, 0.0f));
			camera->AddComponent(cameraTR);
			CCamera* cameraComp = new CCamera();
			camera->AddComponent(cameraComp);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			CCameraScript* cameraScript = new CCameraScript();
			camera->AddComponent(cameraScript);
			this->AddGameObject(camera, eLayerType::Camera);
			//renderer::Cameras.push_back(cameraComp);
		}
		{
			// ui 카메라
			CGameObj* camera = new CGameObj();
			CTransform* cameraTR = new CTransform();
			cameraTR->SetPosition(Vector3(0.f, 0.f, 0.0f));
			camera->AddComponent(cameraTR);
			CCamera* cameraComp = new CCamera();
			cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			camera->AddComponent(cameraComp);
			this->AddGameObject(camera, eLayerType::Camera);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			//renderer::Cameras.push_back(cameraComp);
		}

		{
			//// gridobj
			//CGameObj* gridObj = new CGameObj();
			//gridObj->SetName(L"grid");
			//CMeshRenderer* MeshRenderer = new CMeshRenderer();
			//gridObj->AddComponent(MeshRenderer);
			//CGridScript* gridScript = new CGridScript();
			//gridObj->AddComponent(gridScript);

			//MeshRenderer->SetMesh(CResources::Find<CMesh>(L"Rectmesh"));
			//MeshRenderer->SetMaterial(CResources::Find<CMaterial>(L"GridMaterial"));

			//this->AddGameObject(gridObj, eLayerType::Grid);
		}

		std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"Rectmesh");

		{
			{
				//// 배경 black
				//mbgBlack = new CGameObj();
				//mbgBlack->SetPos(Vector3(0.f, 0.f, 1.f));
				//mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));
				//mbgBlack->SetName(L"Black");

				//CSpriteRenderer* SpriteRenderer = new CSpriteRenderer();
				//mbgBlack->AddComponent(SpriteRenderer);

				//std::shared_ptr<CMaterial> SpriteMaterial = CResources::Find<CMaterial>(L"SpriteMaterial2");

				//SpriteRenderer->SetMesh(mesh);
				//SpriteRenderer->SetMaterial(SpriteMaterial);

				//this->AddGameObject(mbgBlack, eLayerType::BackGround);
			}

			{
				// 배경 Steel
				mbgSteel = new CGameObj();
				mbgSteel->SetPos(Vector3(0.f, -4.f, 1.f));
				mbgSteel->SetScale(Vector3(1.f, 1.f, 1.f));
				mbgSteel->SetName(L"Steel");

				CSpriteRenderer* SpriteRenderer = new CSpriteRenderer();
				mbgSteel->AddComponent(SpriteRenderer);

				std::shared_ptr<CMaterial> SpriteMaterial = CResources::Find<CMaterial>(L"SpriteMaterial");

				SpriteRenderer->SetMesh(mesh);
				SpriteRenderer->SetMaterial(SpriteMaterial);

				this->AddGameObject(mbgSteel, eLayerType::BackGround);
			}

			{
				// hpbar
				mUI = new CGameObj();
				mUI->SetPos(Vector3(0.f, 0.f, 10.f));
				mUI->SetScale(Vector3(5.f, 5.f, 1.f));
				mUI->SetName(L"UI");

				CSpriteRenderer* SpriteRenderer = new CSpriteRenderer();
				mUI->AddComponent(SpriteRenderer);

				std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"Rectmesh");
				std::shared_ptr<CMaterial> SpriteMaterial = CResources::Find<CMaterial>(L"UIMaterial");

				SpriteRenderer->SetMesh(mesh);
				SpriteRenderer->SetMaterial(SpriteMaterial);

				this->AddGameObject(mUI, eLayerType::UI);
			}
		}

		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		CScene::update();
	}

	void CSceneTitle::fixedupdate()
	{
		//Vector3 pos = mbgSteel->GetPos();
		//pos.y += 3.f * CTimeMgr::DeltaTime();
		//mbgSteel->SetPos(pos);

		CScene::fixedupdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}


}