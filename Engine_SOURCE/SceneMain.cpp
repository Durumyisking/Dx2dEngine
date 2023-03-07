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
		: mCamera(nullptr)
		, mUICamera(nullptr)
		, mUICursor(nullptr)

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
			renderer::mainCamera = cameraComp;
		}
		{
			// ui 카메라
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");
		
			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TexCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script);
			mUICursor->SetPos(Vector3(0.f, 0.f, 0.f));
			mUICursor->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		{
			CGameObj* mbgZer = object::Instantiate<CGameObj>(eLayerType::Player, L"zz");
			mbgZer->SetPos(Vector3(0.f, 0.f, 0.6f));

			CCollider2D* coll = mbgZer->AddComponent<CCollider2D>(eComponentType::Collider);
			coll->SetType(eColliderType::Circle);
			coll->SetCenter(Vector2(0.f, 0.f));

			CSpriteRenderer* SpriteRenderer = mbgZer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"CursorMat");
			SpriteRenderer->SetMaterial(Material);
			mbgZer->AddComponent<CPlayerScript>(eComponentType::Script);
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