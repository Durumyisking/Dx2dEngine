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

using namespace dru::graphics;

namespace dru
{
	CSceneMain::CSceneMain()
		: mCamera(nullptr)
		, mUICamera(nullptr)
		, mUICursor(nullptr)
		, mMaskTarget(nullptr)
		, mScreenMask(nullptr)
		, mbLoad(false)
		, mStages{}
		, mCurrentStage(0)
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

		for (size_t i = 0; i < mStages.size(); i++)
		{
			mStages[i]->SetOwner(this);
		}


		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Platforms);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Monster, eLayerType::Platforms);

		CCollisionMgr::CollisionLayerCheck(eLayerType::Monster, eLayerType::FX);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::FX);

		CScene::Initialize();
	}

	void CSceneMain::update()
	{
		mStages[mCurrentStage]->Update();

		if (CInput::GetKeyTap(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Title);
		}

		if (CInput::GetKeyTap(eKeyCode::ENTER) && !mbLoad)
		{
			if (mStages[mCurrentStage]->GetReadyState() == eReadyState::ReadyEnd)
			{
				mStages[mCurrentStage]->LoadUI();
				mbLoad = true;
			}
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

		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightMainScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
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
		{
			// ui 카메라
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		{
			mMaskTarget = object::Instantiate<CBackground>(eLayerType::None, L"UITargetTitleScene");
			mMaskTarget->SetPos(Vector3(0.f, 40.f, 0.1f));
			mMaskTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}


		{
			mScreenMask = object::Instantiate<CBackground>(eLayerType::BackGround, L"mask");

			CSpriteRenderer* SpriteRenderer = mScreenMask->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"mask", L"SpriteShader");
			CResources::Insert<CMaterial>(L"maskMat", Material);

			SpriteRenderer->SetMaterial(Material);

			mScreenMask->SetPos(Vector3(0.f, 0.f, 0.1f));
			mScreenMask->SetScale(Vector3(2.5f, 2.5f, 1.f));

			mScreenMask->AddComponent<CMaskScript>(eComponentType::Script)->SetTarget(mMaskTarget->GetComponent<CTransform>());
		}

		mStages[mCurrentStage]->InitStage();

		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		mbLoad = false;
		CScene::Exit();
	}

}