#include "SceneMain.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "Collider2D.h"
#include "CollisionMgr.h"
#include "Light.h"

#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Grunt.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "CursorScript.h"
#include "MaskScript.h"

#include "Animator.h"

#include "Floor.h"
#include "Wall.h"

#include "StageTutorial.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "BossStage1.h"
#include "BossStage2.h"

#include "GraphicDevice.h"

using namespace dru::graphics;

namespace dru
{
	CSceneMain::CSceneMain()
		: mCamera(nullptr)
		, mUICamera(nullptr)
		, mUICursor(nullptr)
		, mMaskTarget(nullptr)
		, mScreenMask(nullptr)
		, mStages{}
		, mCurrentStage(3)
		, mPlayer(nullptr)
	{
	}
	CSceneMain::~CSceneMain()
	{
		for (size_t i = 0; i < mStages.size(); i++)
		{
			delete mStages[i];
		}
	}
	void CSceneMain::Initialize()
	{
		mStages.push_back(new CStageTutorial);
		mStages.push_back(new CStage1);
		mStages.push_back(new CStage2);
		mStages.push_back(new CBossStage1);
		mStages.push_back(new CStage3);
		mStages.push_back(new CBossStage2);

//		mStages.push_back(new CStage3);
//		mStages.push_back(new CBossStage2);

		for (size_t i = 0; i < mStages.size(); i++)
		{
			mStages[i]->SetOwner(this);
		}
		CCollisionMgr::CollisionLayerCheck(eLayerType::Camera, eLayerType::Platforms);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Ray, eLayerType::Objects);

		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Platforms);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Ray);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Objects);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Monster, eLayerType::Objects);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Monster, eLayerType::Platforms);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Boss, eLayerType::Platforms);

		CCollisionMgr::CollisionLayerCheck(eLayerType::Monster, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Boss, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Camera, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Platforms, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Objects, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Bullet, eLayerType::FX);

		CCollisionMgr::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Player);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Boss);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Platforms);

		CScene::Initialize();
	}

	void CSceneMain::update()
	{
		mStages[mCurrentStage]->Update();

		if (CInput::GetKeyTap(eKeyCode::N))
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
		mDeleteObj = true;

		
		if (!mCamera) // 메인캠은 최초 한번만 만들거
		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, this, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
			mCamera->DontDestroy();

			CAudioSource* audioSource = mCamera->AddComponent<CAudioSource>(eComponentType::AudioSource);
			audioSource->AddClipByKey(L"song_title_bgm");

			CCollider2D* coll = mCamera->AddComponent<CCollider2D>(eComponentType::Collider);
			coll->SetName(L"col_maincam");
			coll->SetType(eColliderType::Rect);
			coll->SetScale(Vector2(GetDevice()->ViewportWidth() / 100.f, GetDevice()->ViewportHeight() / 100.f));
			coll->Off();
		}

		{
			// ui 카메라
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightMainScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}
		{
			// 배경 black
			CGameObj* bgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
			CSpriteRenderer* SpriteRenderer = bgBlack->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Black", Material);
			SpriteRenderer->SetMaterial(Material);
			bgBlack->SetPos(Vector3(0.f, 0.f, 5.f));
			bgBlack->SetScale(Vector3(100.f, 100.f, 1.f));
		}

		mStages[mCurrentStage]->InitStage();

		{
			mMaskTarget = object::Instantiate<CBackground>(eLayerType::None, L"UITargetTitleScene");
			mMaskTarget->SetPos(Vector3(0.f, 40.f, 0.1f));
			mMaskTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}

		{
			mScreenMask = object::Instantiate<CBackground>(eLayerType::BackGround, L"mask");

			CSpriteRenderer* SpriteRenderer = mScreenMask->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"mask", L"SpriteShader");
			CResources::Insert<CMaterial>(L"maskMat", Material);

			SpriteRenderer->SetMaterial(Material);

			mScreenMask->SetPos(Vector3(0.f, 0.f, 0.1f));
			mScreenMask->SetScale(Vector3(2.5f, 2.5f, 1.f));

			mScreenMask->AddComponent<CMaskScript>(eComponentType::Script)->SetTarget(mMaskTarget->GetComponent<CTransform>());
		}

		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		CScene::Exit();
	}

}