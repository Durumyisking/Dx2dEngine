#include "SceneTitle.h"
#include "TimeMgr.h"
#include "Background.h"
#include "GridScript.h"
#include "FadeScript.h"
#include "Object.h"

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
			CGameObj* camera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = camera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CCameraScript>(eComponentType::Script);
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
				mbgBlack->SetPos(Vector3(0.f, -4.f, 1.f));
				mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", SpriteMaterial);
				SpriteRenderer->SetMaterial(SpriteMaterial);

			}

			{
				// 배경 Steel
				mbgSteel = object::Instantiate<CBackground>(eLayerType::BackGround, L"Steel");
				CSpriteRenderer* SpriteRenderer = mbgSteel->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				mbgSteel->SetPos(Vector3(0.f, -3.f, 1.f));

				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>(L"Steel", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Steel", SpriteMaterial); 
 				SpriteRenderer->SetMaterial(SpriteMaterial);

				mbgSteel->SetScale(Vector3(0.4f, 0.4f, 1.f));
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
		//CGameObj* cam = renderer::Cameras[0]->GetOwner();
		//Vector3 pos = cam->GetPos();
		//pos.y -= 3.f * CTimeMgr::DeltaTime();
		//cam->SetPos(pos);

		CScene::fixedupdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}


}