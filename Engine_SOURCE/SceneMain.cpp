#include "SceneMain.h"
#include "TimeMgr.h"
#include "Background.h"
#include "GridScript.h"
#include "FadeScript.h"
#include "PlayerScript.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "Collider2D.h"
#include "CursorScript.h"

namespace dru
{
	CSceneMain::CSceneMain()
	{
	}
	CSceneMain::~CSceneMain()
	{
	}
	void CSceneMain::Initialize()
	{
		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
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
			renderer::Cameras[static_cast<UINT>(mType)].push_back(cameraComp);
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");
			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Cursor", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Cursor", Material);
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script);
			mUICursor->SetPos(Vector3(0.f, 0.f, 0.f));
			mUICursor->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		{
			CBackground* mbgZer = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleZer_1");
			CSpriteRenderer* SpriteRenderer = mbgZer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleZer_1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"TitleZer_1", Material);
			SpriteRenderer->SetMaterial(Material);

			mbgZer->SetPos(Vector3(-0.09f, -0.45f, 0.81f));
			mbgZer->SetScale(Vector3(0.25f, 0.25f, 1.f));

			CCollider2D* coll = mbgZer->AddComponent<CCollider2D>(eComponentType::Collider);
			coll->SetType(eColliderType::Rect);
		}

		CScene::Initialize();
	}

	void CSceneMain::update()
	{
		if (CInput::GetKeyDown(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Title);
		}
		CScene::update();
	}

	void CSceneMain::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneMain::render()
	{
		CScene::render();
	}

	void CSceneMain::Enter()
	{
		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		CScene::Exit();
	}

}