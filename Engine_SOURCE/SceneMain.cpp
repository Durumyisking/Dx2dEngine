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
		, mCurrentStage(0)
		, mPauseMenuNumber(0)
		, mPauseMenuDepth(0)
		, mPauseMenuPlayerAfterimageColor(0)
		, mPlayer(nullptr)
		, mPauseMenuBg(nullptr)
		, mPauseMenuSelector(nullptr)
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
		if (CInput::GetKeyTap(eKeyCode::ESC))
		{
			if (!mbPause)
			{
				mPauseMenuSelector->SetPos(Vector3(0.f, 3.15f, 0.1f));
				mPauseMenuNumber = 0;
				mPauseMenuDepth = 0;
				mPauseMenuBg->RenderingBlockOff();
				mPauseMenuSelector->RenderingBlockOff();
				mbPause = true;
			}
			else
			{
				mPauseMenuBg->RenderingBlockOn();
				mPauseMenuSelector->RenderingBlockOn();
				mbPause = false;
			}
		}
		PauseMenuOperate();

		CScene::update();

	}

	void CSceneMain::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneMain::render()
	{
		if (mbPause)
		{
			switch (mPauseMenuDepth)
			{
			case 0:
				CFontWrapper::DrawFont(L"Continue", 50.f, 115.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				CFontWrapper::DrawFont(L"Change AfterImeage Color", 50.f, 165.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				CFontWrapper::DrawFont(L"Exit Game", 50.f, 215.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				break;
			case 1:
				CFontWrapper::DrawFont(L"Default", 50.f, 115.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				CFontWrapper::DrawFont(L"Red", 50.f, 165.f, 30.f, FONT_RGBA(255, 0, 0, 255));
				CFontWrapper::DrawFont(L"Green", 50.f, 215.f, 30.f, FONT_RGBA(0, 255, 0, 255));
				CFontWrapper::DrawFont(L"Blue", 50.f, 265.f, 30.f, FONT_RGBA(0, 0, 255, 255));
				CFontWrapper::DrawFont(L"Gold", 50.f, 315.f, 30.f, FONT_RGBA(191, 140, 38, 255));
				break;
			default:
				break;
			}
		}
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

		{
			mPauseMenuBg = object::Instantiate<CBackground>(eLayerType::UI, L"PauseMenuBg");

			CSpriteRenderer* SpriteRenderer = mPauseMenuBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"UIShader");
			CResources::Insert<CMaterial>(L"PauseMenuBgMat", Material);

			SpriteRenderer->SetMaterial(Material);
			SpriteRenderer->ChangeColor(LIGHT_BLUE);

			mPauseMenuBg->SetPos(Vector3(0.f, 0.f, 0.1f));
			mPauseMenuBg->SetScale(Vector3(10.f, 10.f, 1.f));

			mPauseMenuBg->RenderingBlockOn();
		}
		{
			mPauseMenuSelector = object::Instantiate<CBackground>(eLayerType::UI, L"PauseMenuSelector");

			CSpriteRenderer* SpriteRenderer = mPauseMenuSelector->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"UIShader");
			CResources::Insert<CMaterial>(L"PauseMenuSelectorMat", Material);

			SpriteRenderer->SetMaterial(Material);
			SpriteRenderer->ChangeColor(LIGHT_MAGENTA);

			mPauseMenuSelector->SetPos(Vector3(0.f, 3.15f, 0.1f));
			mPauseMenuSelector->SetScale(Vector3(10.f, 0.05f, 1.f));

			mPauseMenuSelector->RenderingBlockOn();

		}

		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		CScene::Exit();
	}

	void CSceneMain::PauseMenuOperate()
	{
		if (mbPause)
		{
			if (CInput::GetKeyTap(eKeyCode::ENTER))
			{
				if (0 == mPauseMenuDepth)
				{
					switch (mPauseMenuNumber)
					{
					case 0:
						mPauseMenuBg->RenderingBlockOn();
						mPauseMenuSelector->RenderingBlockOn();
						mbPause = false;
						break;
					case 1:
						mPauseMenuDepth = 1;
						mPauseMenuNumber = mPauseMenuPlayerAfterimageColor;
						mPauseMenuSelector->SetPos(Vector3(0.f, 3.15f - 0.5f * mPauseMenuPlayerAfterimageColor, 0.1f));

						break;
					default:
						break;
					}
				}
				else if (1 == mPauseMenuDepth)
				{
					switch (mPauseMenuNumber)
					{
					case 0:
						mPauseMenuPlayerAfterimageColor = 0;
						mPlayer->SetAfterImageColor(Vector4::Zero);
						break;
					case 1:
						mPauseMenuPlayerAfterimageColor = 1;
						mPlayer->SetAfterImageColor(RED);
						break;
					case 2:
						mPauseMenuPlayerAfterimageColor = 2;
						mPlayer->SetAfterImageColor(GREEN);
						break;
					case 3:
						mPauseMenuPlayerAfterimageColor = 3;
						mPlayer->SetAfterImageColor(BLUE);
						break;
					case 4:
						mPauseMenuPlayerAfterimageColor = 4;
						mPlayer->SetAfterImageColor(GOLD);
						break;
					default:
						break;
					}

					mPauseMenuDepth = 0;
					mPauseMenuNumber = 1;
					mPauseMenuSelector->SetPos(Vector3(0.f, 2.65f, 0.1f));
				}
			}
			switch (mPauseMenuDepth)
			{
			case 0:
				if (CInput::GetKeyTap(eKeyCode::UP))
				{
					if (0 != mPauseMenuNumber)
					{
						mPauseMenuSelector->GetComponent<CTransform>()->AddPositionY(0.5f);
						--mPauseMenuNumber;
					}
				}
				if (CInput::GetKeyTap(eKeyCode::DOWN))
				{
					if (2 != mPauseMenuNumber)
					{
						mPauseMenuSelector->GetComponent<CTransform>()->AddPositionY(-0.5f);
						++mPauseMenuNumber;
					}
				}
				break;
			case 1:
				if (CInput::GetKeyTap(eKeyCode::UP))
				{
					if (0 != mPauseMenuNumber)
					{
						mPauseMenuSelector->GetComponent<CTransform>()->AddPositionY(0.5f);
						--mPauseMenuNumber;
					}
				}
				if (CInput::GetKeyTap(eKeyCode::DOWN))
				{
					if (4 != mPauseMenuNumber)
					{
						mPauseMenuSelector->GetComponent<CTransform>()->AddPositionY(-0.5f);
						++mPauseMenuNumber;
					}
				}
				break;
			default:
				break;
			}

		}
	}

}