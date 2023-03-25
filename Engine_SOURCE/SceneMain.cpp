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

#include "GridScript.h"
#include "FadeScript.h"
#include "CursorScript.h"
#include "MaskScript.h"

#include "Animator.h"

#include "Floor.h"
#include "Wall.h"

using namespace dru::graphics;

namespace dru
{
	CSceneMain::CSceneMain()
		: mCamera(nullptr)
		, mUICamera(nullptr)
		, mUICursor(nullptr)
		, mMaskTarget(nullptr)
		, mHudBatteryParts{}
		, mHudTimerBar(nullptr)
		, mHudLeftHand(nullptr)
		, mHudRightHand(nullptr)
		, mPlayer(nullptr)
		, mStageBackground(nullptr)
		, mScreenMask(nullptr)
		, mbMaskMove(false)
		, mbLoad(false)
		, mbStart(false)

	{
	}
	CSceneMain::~CSceneMain()
	{
	}
	void CSceneMain::Initialize()
	{
		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightMainScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });

		}


		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"PointLight");
			PointLight->SetPos({ -2.5f, -1.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 1.f, 0.f, 0.f, 0.f });

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
			cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}


		/////////////////////////////Obj Add /////////////////////////////////////


		{
			// 배경 Stage1
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage1", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(7.f, 5.f, 5.f));
			mStageBackground->SetScale(Vector3(8.f, 8.f, 1.f));
		}

	
		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-6.f, -2.5f, 3.f));
		}

		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-4.f, -3.4f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.5f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(0.8f, 0.f, 3.f));
			Wall->SetColliderScale({ 0.5f, 20.f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(-1.8f, 1.8f, 3.f));
			Wall->SetColliderScale({ 0.5f, 5.f });
		}


		{
			//CGameObj* mMon = object::Instantiate<CMonster>(eLayerType::Monster, L"Mon");

			//CSpriteRenderer* SpriteRenderer = mMon->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			//std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"SpriteShader");
			//CResources::Insert<CMaterial>(L"MonMat", Material);
			//SpriteRenderer->SetMaterial(Material);

			//mMon->SetPos(Vector3(3.f, -2.f, 3.f));
			//mMon->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script);
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 1.f));
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


		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster);
		CCollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Platforms);

		CScene::Initialize();
	}

	void CSceneMain::update()
	{

		if (mbMaskMove && !mbLoad)
		{
			{
				CGameObj* mHudTop = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Top");

				CSpriteRenderer* SpriteRenderer = mHudTop->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_top", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_topMat", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudTop->SetPos(Vector3(0.f, 4.225f, 1.f));
				mHudTop->SetScale(Vector3(0.25f, 0.25f, 1.f));
			}

			{
				CGameObj* mHudTimer = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timer");

				CSpriteRenderer* SpriteRenderer = mHudTimer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timer", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_timerMat", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudTimer->SetPos(Vector3(0.f, 4.2f, 1.f));
				mHudTimer->SetScale(Vector3(0.275f, 0.275f, 1.f));
			}

			{
				mHudTimerBar = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

				CSpriteRenderer* SpriteRenderer = mHudTimerBar->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timerbar", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_timerbarMat", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudTimerBar->SetPos(Vector3(0.23f, 4.25f, 1.f));
				mHudTimerBar->SetScale(Vector3(0.275f, 0.275f, 1.f));

			}

			{
				CGameObj* mHudBattery = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Battery");

				CSpriteRenderer* SpriteRenderer = mHudBattery->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_battery", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_batteryMat", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudBattery->SetPos(Vector3(-6.9f, 4.2f, 1.f));
				mHudBattery->SetScale(Vector3(0.265f, 0.265f, 1.f));
			}

			{
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_batterypart", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_batteryMat", Material);

				for (int i = 0; i < 11; ++i)
				{
					std::wstring str = L"Hud_BatteryPart";
					std::wstring num = std::to_wstring(i);
					str += num;

					CGameObj* mHudBatteryPart = object::Instantiate<CBackground>(eLayerType::UI, str);

					mHudBatteryParts.push_back(mHudBatteryPart);

					CSpriteRenderer* SpriteRenderer = mHudBatteryPart->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
					SpriteRenderer->SetMaterial(Material);

					mHudBatteryPart->SetPos(Vector3(-7.6f + (i * 0.14f), 4.22f, 1.f));
					mHudBatteryPart->SetScale(Vector3(0.05f, 0.05f, 1.f));
				}
			}

			{
				CGameObj* mHudInventory = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Inventory");

				CSpriteRenderer* SpriteRenderer = mHudInventory->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_inventory", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_invenMat", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudInventory->SetPos(Vector3(7.f, 4.2f, 1.f));
				mHudInventory->SetScale(Vector3(0.2f, 0.2f, 1.f));
			}

			{
				mHudLeftHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

				CSpriteRenderer* SpriteRenderer = mHudLeftHand->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_katana", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_LeftItem", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudLeftHand->SetPos(Vector3(6.625f, 4.2f, 1.f));
				mHudLeftHand->SetScale(Vector3(0.5, 0.5, 1.f));

			}

			{
				mHudRightHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

				CSpriteRenderer* SpriteRenderer = mHudRightHand->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_hand", L"UIShader");
				CResources::Insert<CMaterial>(L"Hud_RightItem", Material);
				SpriteRenderer->SetMaterial(Material);

				mHudRightHand->SetPos(Vector3(7.375f, 4.22f, 1.f));
				mHudRightHand->SetScale(Vector3(0.5f, 0.5, 1.f));

			}
			mbLoad = true;
		}
		else
		{
			if (dynamic_cast<CMaskScript*>(mScreenMask->GetScript())->MoveDone())
				mbMaskMove = true;
		}


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
		CScene::Enter();
	}

	void CSceneMain::Exit()
	{
		CScene::Exit();
		mbMaskMove = false;
	}

}