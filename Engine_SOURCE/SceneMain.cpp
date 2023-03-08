#include "SceneMain.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "Collider2D.h"
#include "CollisionMgr.h"

#include "Background.h"
#include "Player.h"
#include "Monster.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "CursorScript.h"


namespace dru
{
	CSceneMain::CSceneMain()
		: mCamera(nullptr)
		, mUICamera(nullptr)
		, mUICursor(nullptr)
		, mPlayer(nullptr)

	{
	}
	CSceneMain::~CSceneMain()
	{
	}
	void CSceneMain::Initialize()
	{
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);

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
			// 배경 Stage1
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Stage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage1", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(7.f, 5.f, 5.f));
			mStageBackground->SetScale(Vector3(8.f, 8.f, 1.f));
		}

		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-6.f, -2.65f, 3.f));
			mPlayer->SetScale(Vector3(5.f, 5.f, 3.f));
			CGameObj* playerObj = dynamic_cast<CGameObj*>(mPlayer);
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TexCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
			SpriteRenderer->SetMaterial(Material);
//			mUICursor->AddComponent<CCursorScript>(eComponentType::Script);
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.5f, 0.5f, 1.f));
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