#include "Stage.h"
#include "BlinkScript.h"
#include "SceneMain.h"
#include "ParticleSystem.h"

namespace dru
{
	CGameObj* CStage::mKeyLeft = nullptr;
	CGameObj* CStage::mKeyRight = nullptr;
	CGameObj* CStage::mKeyUp = nullptr;
	CGameObj* CStage::mKeyDown = nullptr;
	CGameObj* CStage::mKeyShift = nullptr;
	CGameObj* CStage::mKeyLClick = nullptr;


	CStage::CStage()
		: mStageState(eStageState::NotReady)
		, mStageBackground(nullptr)
		, mbClear(false)
		, mPostProcess_Rewind(nullptr)
		, mPostProcess_Replay(nullptr)
		, mPostProcess_Snow(nullptr)
		, mClearCollider(nullptr)
		, mScene(nullptr)
		, mDeadBg(nullptr)
		, mbIsDeadBgOn(false)
		, mPlayer(nullptr)
		, mHudTop(nullptr)
		, mHudTimer(nullptr)
		, mHudInventory(nullptr)
		, mUICursor(nullptr)
		, mKeyEnter(nullptr)
		, mHudBattery(nullptr)
		, mBatteryParticle(nullptr)
		, mHudBatteryParts{}
		, mHudTimerBar(nullptr)
		, mHudLeftHand(nullptr)
		, mHudRightHand(nullptr)
		, mBulletTimeMask(nullptr)
		, mBulletTimeGaugePrev(10)
		, mBulletTimeGaugeCurrent(10)
		, mPlayerDefaultPos{}
		, mDefaultTimerBarPos{}
		, mDefaultTimerBarScale{}
		, mTimer(100.f)
		, mElapsedTime(0.f)
		, mbRewinding(false)
		, mbReplaying(false)
		, mEnemyCount(0)
		, mFrameCount(0)
		, mRewindTimer(0.f)
		, mBulletTimeGauge(10.f)
		, mbBulletTimeStun(false)
		, mBulletTimeCooldown(0.f)
		, mRewindObjects{}

	{
	}

	CStage::~CStage()
	{
	}

	void CStage::Update()
	{
		if (CInput::GetKeyTap(eKeyCode::X))
		{
			renderer::mainCamera->GetCamScript()->CamFollowOff();
			renderer::mainCamera->GetCamScript()->FreeViewOn();
		}
		if (CInput::GetKeyTap(eKeyCode::C))
		{
			renderer::mainCamera->GetCamScript()->CamFollowOn();
			renderer::mainCamera->GetCamScript()->FreeViewOff();
		}

		if (mStageState == eStageState::NotReady)
		{
			NotReadyOperate();
		}

		else if (mStageState == eStageState::Ready)
		{
			ReadyOperate();
		}

		else if (mStageState == eStageState::ReadyEnd)
		{
			ReadyEndOperate();
		}

		else if (mStageState == eStageState::LoadUI)
		{
			LoadUIOperate();
		}

		else if (mStageState == eStageState::LoadEnd)
		{
			LoadEndOperate();
			if (mbClear)
			{
				ClearOperate();
				return;
			}
			BulletTimeBatteryOperation();
			BulletTimeBatteryParticleOperation();
		}

	}

	void CStage::Exit()
	{
		CamReset();
		mStageState = eStageState::NotReady;
		CSceneMgr::LoadScene(CSceneMgr::eSceneType::Temp);
	}

	
	void CStage::LoadUI()
	{
		renderer::mainCamera->GetCamScript()->CamFollowOff();
		{
			mHudTop = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Top");

			CSpriteRenderer* SpriteRenderer = mHudTop->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_top", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_topMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTop->SetPos(Vector3(0.f, 4.225f, 1.f));
			mHudTop->SetScale(Vector3(0.25f, 0.25f, 1.f));
		}
		{
			mHudTimer = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timer");

			CSpriteRenderer* SpriteRenderer = mHudTimer->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timer", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_timerMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTimer->SetPos(Vector3(0.f, 4.2f, 1.f));
			mHudTimer->SetScale(Vector3(0.275f, 0.275f, 1.f));
		}

		{
			mHudTimerBar = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudTimerBar->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timerbar", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_timerbarMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTimerBar->SetPos(Vector3(0.228f, 4.248f, 1.f));
			mHudTimerBar->SetScale(Vector3(0.275f, 0.275f, 1.f));


		}

		{
			mHudBattery = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Battery");

			CSpriteRenderer* SpriteRenderer = mHudBattery->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_battery", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_batteryMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudBattery->SetPos(Vector3(-6.9f, 4.2f, 1.f));
			mHudBattery->SetScale(Vector3(0.265f, 0.265f, 1.f));
		}

		{
			for (int i = 0; i < 11; ++i)
			{
				std::wstring str = L"Hud_BatteryPartMat";
				std::wstring num = std::to_wstring(i);
				str += num;

				CGameObj* mHudBatteryPart = object::Instantiate<CBackground>(eLayerType::UI, str);

				mHudBatteryParts.push_back(mHudBatteryPart);

				CSpriteRenderer* SpriteRenderer = mHudBatteryPart->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_batterypart", L"UIShader");
				CResources::Insert<CMaterial>(str, Material);
				SpriteRenderer->SetMaterial(Material);

				mHudBatteryPart->SetPos(Vector3(-7.6f + (i * 0.14f), 4.22f, 1.f));
				mHudBatteryPart->SetScale(Vector3(0.05f, 0.05f, 1.f));
			}
		}

		{
			mHudInventory = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Inventory");

			CSpriteRenderer* SpriteRenderer = mHudInventory->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_inventory", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_invenMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudInventory->SetPos(Vector3(7.f, 4.2f, 1.f));
			mHudInventory->SetScale(Vector3(0.2f, 0.2f, 1.f));
		}

		{
			mHudLeftHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudLeftHand->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_katana", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_LeftItem", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudLeftHand->SetPos(Vector3(6.625f, 4.2f, 1.f));
			mHudLeftHand->SetScale(Vector3(0.5, 0.5, 1.f));

		}

		{
			mHudRightHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudRightHand->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_hand", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_RightItem", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudRightHand->SetPos(Vector3(7.375f, 4.22f, 1.f));
			mHudRightHand->SetScale(Vector3(0.5f, 0.5, 1.f));

		}


		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"CursorMat");
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script)->Initialize();
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 4.9999f));
		}
		{			
			mBulletTimeMask = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"BulletTimeMask");

			CSpriteRenderer* SpriteRenderer = mBulletTimeMask->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
			CResources::Insert<CMaterial>(L"BulletTimeMaskMat", Material);
			SpriteRenderer->SetMaterial(Material);

			SpriteRenderer->ChangeColor(Vector4{ 0.f, 0.f, 0.f, 0.75f });
			mBulletTimeMask->SetPos(Vector3(0.f, 0.f, 5.f));
			mBulletTimeMask->SetScale(Vector3(30.f, 30.f, 0.f));
			mBulletTimeMask->RenderingBlockOn();
		}

	}

	void CStage::LoadKeyUI()
	{
		if (!mKeyLeft)
		{
			mKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, L"keyA");
			CSpriteRenderer* SpriteRenderer = mKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLeft->SetPos(Vector3::Zero);
			mKeyLeft->DontDestroy();
			CAnimator* mAnimator = mKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_press", Material->GetTexture(), { 42.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_anim", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyA_anim", false);
			mKeyLeft->RenderingBlockOn();

		}

		if (!mKeyRight)
		{
			mKeyRight = object::Instantiate<CGameObj>(eLayerType::UI,  L"keyD");
			CSpriteRenderer* SpriteRenderer = mKeyRight->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyRight->SetPos(Vector3::Zero);
			mKeyRight->DontDestroy();
			CAnimator* mAnimator = mKeyRight->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyD_none", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_press", Material->GetTexture(), { 70.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyD_none", false);
			mKeyRight->RenderingBlockOn();
		}

		if (!mKeyUp)
		{
			mKeyUp = object::Instantiate<CGameObj>(eLayerType::UI,  L"keyW");
			CSpriteRenderer* SpriteRenderer = mKeyUp->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyUp->SetPos(Vector3::Zero);
			mKeyUp->DontDestroy();
			CAnimator* mAnimator = mKeyUp->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyW_none", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_press", Material->GetTexture(), { 98.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_anim", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyW_anim", false);
			mKeyUp->RenderingBlockOn();
		}

		if (!mKeyDown)
		{
			mKeyDown = object::Instantiate<CGameObj>(eLayerType::UI,  L"keyS");
			CSpriteRenderer* SpriteRenderer = mKeyDown->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyDown->SetPos(Vector3::Zero);
			mKeyDown->DontDestroy();
			CAnimator* mAnimator = mKeyDown->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyS_none", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_press", Material->GetTexture(), { 14.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_anim", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyS_none", false);
			mKeyDown->RenderingBlockOn();
		}

		if (!mKeyLClick)
		{
			mKeyLClick = object::Instantiate<CGameObj>(eLayerType::UI,  L"LClick");
			CSpriteRenderer* SpriteRenderer = mKeyLClick->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLClick->SetPos(Vector3::Zero);
			mKeyLClick->DontDestroy();
			CAnimator* mAnimator = mKeyLClick->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"LClick_anim", Material->GetTexture(), { 112.f, 0.f }, { 13.f, 17.f }, Vector2::Zero, 2, { 60.f, 60.f }, 0.5f);
			mAnimator->Play(L"LClick_anim");
			mKeyLClick->RenderingBlockOn();
		}

		if (!mKeyShift)
		{
			mKeyShift = object::Instantiate<CGameObj>(eLayerType::UI,  L"Shift");
			CSpriteRenderer* SpriteRenderer = mKeyShift->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyShift->SetPos(Vector3::Zero);
			mKeyShift->DontDestroy();
			CAnimator* mAnimator = mKeyShift->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"Shift_anim", Material->GetTexture(), { 215.f, 2.f }, { 32.f, 16.f }, Vector2::Zero, 2, { 60.f, 60.f }, 2.f);
			mAnimator->Play(L"Shift_anim");
			mKeyShift->RenderingBlockOn();
		}
	}

	void CStage::NotReadyOperate()
	{
	}

	void CStage::ReadyOperate()
	{
		CreatePostProcess_Rewind();
		CreatePostProcess_Replay();
		LoadKeyUI();

		mPlayer->GetComponent<CRigidBody>()->SetMaxVelocity(Vector3(5.f, 7.f, 0.f));
		LoadinReady();
		mStageState = eStageState::ReadyEnd;
	}

	void CStage::ReadyEndOperate()
	{
		if (CInput::GetKeyTap(eKeyCode::ENTER))
		{
			LoadUI();
			renderer::mainCamera->GetCamScript()->CamFollowOnX();
			renderer::mainCamera->GetCamScript()->CamFollowOnY();
			renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>()->On();

			CPlayerScript* playerscript = mPlayer->GetScript<CPlayerScript>();
			bool state = playerscript->GetPlayerState(ePlayerState::Dead);
			if (!state)
			{
				mStageState = eStageState::LoadUI;
				mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
			}
		}
	}

	void CStage::LoadUIOperate()
	{
		mDefaultTimerBarPos = mHudTimerBar->GetPos();
		mDefaultTimerBarScale = mHudTimerBar->GetScale();
		mStageState = eStageState::LoadEnd;
	}

	void CStage::LoadEndOperate()
	{
		if (mbRewinding)
		{
			Rewinding();
		}
		else if (mbReplaying)
		{
			Replaying();
		}
		else
		{
			bool state = GetPlayerState(ePlayerState::Dead);
			if (state)
			{
				if (!mbIsDeadBgOn)
				{
					CreateDeadUI();
				}

				if (CInput::GetKeyTap(eKeyCode::ENTER))
				{
					renderer::mainCamera->GetOwner()->GetComponent<CAudioSource>()->Play(L"SE_rewind");
					DeadReset();
				}
			}
			else
			{
				mElapsedTime += CTimeMgr::DeltaTime();
				TimerBarOperate();
				bulletTime();

				if (CInput::GetKeyTap(eKeyCode::R))
				{
					renderer::mainCamera->GetOwner()->GetComponent<CAudioSource>()->Play(L"SE_rewind");
					RewindStart();
				}
			}
			if (CTimeMgr::IsFramePass())
			{
				++mFrameCount;
			}
		}
			
	}

	void CStage::ClearOperate()
	{
		mbClear = false;
		
		CSceneMain* mainScene = CSceneMgr::GetScene<CSceneMain>(CSceneMgr::eSceneType::Main);
		UINT stage = mainScene->GetCurrentStageNumber();
		mainScene->SetStage(++stage);
	}

	void CStage::Reset()
	{
		for (size_t i = mBulletTimeGaugePrev; i < mHudBatteryParts.size(); i++)
		{
			mHudBatteryParts[i]->GetComponent<CSpriteRenderer>()->MulColor(Vector4(1.f, 2.f, 2.f, 1.f));
		}
		mBulletTimeGaugePrev = 10;
		mBulletTimeGaugeCurrent = 10;
		mBulletTimeCooldown = 0.f;
		mBulletTimeGauge = 10.f;
		mbBulletTimeStun = false;

		mElapsedTime = 0.f;
		mFrameCount = 0;

	}

	void CStage::AddStartingLiveObjects()
	{
		mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
		mPlayer->SetPos(mPlayerDefaultPos);
		mRewindObjects.push_back(mPlayer);
	}


	void CStage::BulletTimeBatteryOperation()
	{
		float gauge = mBulletTimeGauge;
		mBulletTimeGaugeCurrent = static_cast<UINT>(gauge);

		if (mBulletTimeGaugePrev < mBulletTimeGaugeCurrent)
		{
			mHudBatteryParts[mBulletTimeGaugePrev]->GetComponent<CSpriteRenderer>()->MulColor(Vector4(1.f, 2.f, 2.f, 1.f));
		}

		if (mBulletTimeGaugePrev > mBulletTimeGaugeCurrent)
		{
			mHudBatteryParts[mBulletTimeGaugePrev]->GetComponent<CSpriteRenderer>()->MulColor(Vector4(1.f, 0.25f, 0.25f, 1.f));
		}
		if (gauge == 0.f)
		{
			mHudBatteryParts[0]->GetComponent<CSpriteRenderer>()->MulColor(Vector4(1.f, 0.25f, 0.25f, 1.f));
			mbBulletTimeStun = true;
		}
		if (gauge == 10.f)
		{
			if (9 == mBulletTimeGaugePrev)
			{
				mHudBatteryParts[9]->GetComponent<CSpriteRenderer>()->MulColor(Vector4(1.f, 2.f, 2.f, 1.f));
			}
		}

		mBulletTimeGaugePrev = mBulletTimeGaugeCurrent;
	}

	void CStage::BulletTimeBatteryParticleOperation()
	{
		if (CTimeMgr::IsBulletTimeOn())
		{
			if (!mbBatteryParticleStart)
			{
				BatteryParticleCreateAndStart();
				mbBatteryParticleStart = true;
			}
			Vector3 ParentWorldPos = mHudBattery->GetUIWorldPos();
			mBatteryParticle->SetPos(ParentWorldPos);

			CParticleSystem* ps = mBatteryParticle->GetComponent<CParticleSystem>();
			Vector3 startPos = Vector3(ParentWorldPos.x, ParentWorldPos.y, 1.f);
			ps->SetStartPosition(startPos);

		}
		else
		{
			if (mbBatteryParticleStart)
			{
				mBatteryParticle->Die();
				mbBatteryParticleStart = false;
			}
		}
	}

	void CStage::UIRenderingBlockOn()
	{

		mHudTop->RenderingBlockOn();
		mHudTimer->RenderingBlockOn();
		mHudTimerBar->RenderingBlockOn();
		mHudBattery->RenderingBlockOn();
		for (CGameObj* obj : mHudBatteryParts)
		{
			obj->RenderingBlockOn();
		}
		mHudInventory->RenderingBlockOn();
		mHudLeftHand->RenderingBlockOn();
		mHudRightHand->RenderingBlockOn();
		mUICursor->RenderingBlockOn();
	}

	void CStage::UIRenderingBlockOff()
	{

		mHudTop->RenderingBlockOff();
		mHudTimer->RenderingBlockOff();
		mHudTimerBar->RenderingBlockOff();
		mHudBattery->RenderingBlockOff();
		for (CGameObj* obj : mHudBatteryParts)
		{
			obj->RenderingBlockOff();
		}
		mHudInventory->RenderingBlockOff();
		mHudLeftHand->RenderingBlockOff();
		mHudRightHand->RenderingBlockOff();
		mUICursor->RenderingBlockOff();
	}

	void CStage::CreateDeadUI()
	{
		{
			if (!mDeadBg)
			{
				// 튜토리얼 배경
				mDeadBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"TutorBg");
				CSpriteRenderer* SpriteRenderer = mDeadBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
				CResources::Insert<CMaterial>(L"TB1Mat", Material);
				SpriteRenderer->SetMaterial(Material);

				mDeadBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
				mDeadBg->SetPos(Vector3(0.f, 0.f, 4.999f));
				mDeadBg->SetScale(Vector3(0.3f, 0.3f, 1.f));

				mDeadBg->AddComponent<CBlinkScript>(eComponentType::Script)->SetOnTime(0.5f);
				CBlinkScript* blinkscript = mDeadBg->GetScript<CBlinkScript>();
				blinkscript->SetOffTime(0.1f);
				blinkscript->SetOnTime(0.1f);
				blinkscript->SwitchOn();

			}
		}
		{
			if (!mKeyEnter)
			{
				mKeyEnter = object::Instantiate<CGameObj>(eLayerType::UI, mDeadBg, L"keyEnter");
				CSpriteRenderer* SpriteRenderer = mKeyEnter->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
				SpriteRenderer->SetMaterial(Material);
				mKeyEnter->SetPos(Vector3(0.f, -0.5f, 0.f));

				CAnimator* mAnimator = mKeyEnter->AddComponent<CAnimator>(eComponentType::Animator);
				mAnimator->Create(L"KeyEnter_anim", Material->GetTexture(), { 167.f, 0.f }, { 24.f, 20 }, Vector2::Zero, 2, { 100.f, 70.f }, 1.f);
				mAnimator->Play(L"KeyEnter_anim");
			}
		}
		mDeadBg->RenderingBlockOff();
		mKeyEnter->RenderingBlockOff();
		CBlinkScript* blinkscript = mDeadBg->GetScript<CBlinkScript>();
		blinkscript->SwitchOn();

		mbIsDeadBgOn = true;
	}

	void CStage::TimerBarOperate()
	{
		// 시간 넘어가면 플레이어 사망처리

		bool state = GetPlayerState(ePlayerState::Dead);
		if (mElapsedTime >= mTimer && false == state)
		{
			mPlayer->GetScript<CPlayerScript>()->PlayerDead();
			return;
		}

		// UI
		float Ratio = 1 - mElapsedTime / mTimer;
		if (Ratio >= 0.0f)
		{
			TimerBarScaling(Ratio);
		}
	}

	void CStage::TimerBarScaling(float _Ratio)
	{	
		float NewX = mDefaultTimerBarScale.x * _Ratio;
		mHudTimerBar->GetComponent<CTransform>()->SetScale({ NewX, mDefaultTimerBarScale.y , mDefaultTimerBarScale.z });
		mHudTimerBar->GetComponent<CTransform>()->SetPosition({ mDefaultTimerBarPos.x - (mDefaultTimerBarScale.x - NewX) * 0.5f, mDefaultTimerBarPos.y, mDefaultTimerBarPos.z });
	}
	bool CStage::GetPlayerState(ePlayerState _State)
	{
		CPlayerScript* playerscript = mPlayer->GetScript<CPlayerScript>();
		bool state = playerscript->GetPlayerState(_State);

		return state;
	}
	void CStage::PushRewindObject(CLiveGameObj* _LiveObject)
	{
		mRewindObjects.push_back(_LiveObject);
	}
	void CStage::CreatePostProcess_Rewind()
	{
		if (!mPostProcess_Rewind)
		{
			mPostProcess_Rewind = object::Instantiate<CPostProcessWave>(eLayerType::PostProcess, renderer::mainCamera->GetOwner(), L"PostProcessGameObject_Rewind");

			mPostProcess_Rewind->SetMaterial(L"WaveMaterial");

			mPostProcess_Rewind->RenderingBlockOn();
			mPostProcess_Rewind->DontDestroy();
		}
	}
	void CStage::CreatePostProcess_Replay()
	{
		if (!mPostProcess_Replay)
		{
			mPostProcess_Replay = object::Instantiate<CPostProcess>(eLayerType::PostProcess, renderer::mainCamera->GetOwner(), L"PostProcessGameObject_Replay");

			mPostProcess_Replay->SetMaterial(L"GreyScaleMaterial");

			mPostProcess_Replay->RenderingBlockOn();
			mPostProcess_Replay->DontDestroy();
		}
	}
	void CStage::CreatePostProcess_Snow()
	{
		if (!mPostProcess_Snow)
		{
			mPostProcess_Snow = object::Instantiate<CPostProcess>(eLayerType::PostProcess, renderer::mainCamera->GetOwner(), L"PostProcessGameObject_Snonw");

			mPostProcess_Snow->SetMaterial(L"SnowMaterial");

			mPostProcess_Snow->RenderingBlockOn();
			mPostProcess_Snow->DontDestroy();
		}
	}

	void CStage::PopRewindObject(CLiveGameObj* _LiveGameObject)
	{
		for (std::vector<CLiveGameObj*>::iterator iter = mRewindObjects.begin(); iter != mRewindObjects.end();)
		{
			if ((*iter) == _LiveGameObject)
			{
				iter = mRewindObjects.erase(iter);
				return;
			}
			else
			{
				iter++;
			}
		}
	}

	void CStage::RewindStart()
	{
		--mFrameCount;
		BulletTimeOff();

		UIRenderingBlockOn();

		mPlayer->GetScript<CPlayerScript>()->InputBlocking();
		mPlayer->GetScript<CPlayerScript>()->RewindStart();

		mPlayer->RemoveAfterImage();
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			mRewindObjects[i]->RenderingBlockOn();
			mRewindObjects[i]->SetRewindOn();

			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->Disable();
			}
			if (eLayerType::Boss == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CBoss*>(mRewindObjects[i])->Disable();
			}

		}

		mPostProcess_Rewind->RenderingBlockOff();

		mbRewinding = true;
	}
	void CStage::Rewinding()
	{
		if (mElapsedTime > REWIND_TIME)
		{
			int a = static_cast<int>((mElapsedTime / REWIND_TIME) + 1.f);
			if (0 < mFrameCount)
			{
				for (int i = 0; i < a; i++)
				{
					--mFrameCount;
				}
			}
		}
		else
		{
			--mFrameCount;
		}

		if(RewindEndCheck())
			RewindEnd();

	}
	bool CStage::RewindEndCheck()
	{
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			if (mRewindObjects[i]->IsRewinding())
				return false;
		}

		return true;
	}
	void CStage::RewindEnd()
	{
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			mRewindObjects[i]->SetRewindOff();			
		}

		UIRenderingBlockOff();
		mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
		mPlayer->SetRight();
		mPlayer->Flip();

		RewindLayerTypeException();
		DeleteDeadRewindObject();


		Reset();

		mPostProcess_Rewind->RenderingBlockOn();
		mbRewinding = false;

	}
	void CStage::RewindLayerTypeException()
	{
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->AddRay(dynamic_cast<CMonster*>(mRewindObjects[i])->GetRayScale());
			}
			if (eLayerType::Boss == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CBoss*>(mRewindObjects[i])->ResetHp();
			}
			if (eLayerType::FX == mRewindObjects[i]->GetLayerType() || eLayerType::BackGround == mRewindObjects[i]->GetLayerType())
			{
				mRewindObjects[i]->Die();
			}
		}
	}
	void CStage::DeleteDeadRewindObject()
	{
		for (std::vector<CLiveGameObj*>::iterator iter = mRewindObjects.begin(); iter != mRewindObjects.end();)
		{
			if ((*iter)->GetState() == CGameObj::eState::Dead)
			{
				iter = mRewindObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
	void CStage::ReplayStart()
	{
		BulletTimeOff();
		UIRenderingBlockOn();
		mPlayer->GetScript<CPlayerScript>()->InputBlocking();
		mPlayer->RemoveAfterImage();
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			mRewindObjects[i]->SetReplayOn();
			mRewindObjects[i]->RenderingBlockOn();
			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->Disable();
			}
		}

		mPostProcess_Replay->RenderingBlockOff();

		mFrameCount = -1;
		mbReplaying = true;
	}
	void CStage::Replaying()	
	{
		++mFrameCount;
		if (ReplayEndCheck())
			ReplayEnd();
	}
	bool CStage::ReplayEndCheck()
	{
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			if (mRewindObjects[i]->IsReplaying())
				return false;
		}

		return true;
	}
	void CStage::ReplayEnd()
	{
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			mRewindObjects[i]->SetReplayOff();
		}
		UIRenderingBlockOff();
		mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
		mPlayer->SetRight();
		mPlayer->Flip();

		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->AddRay(dynamic_cast<CMonster*>(mRewindObjects[i])->GetRayScale());
			}
		}	

		mPostProcess_Replay->RenderingBlockOn();
		mbReplaying = false;

		SetClearOn();
		Reset();
		Exit();

	}
	void CStage::DeadReset()
	{

		mDeadBg->RenderingBlockOn();
		mKeyEnter->RenderingBlockOn();
		mbIsDeadBgOn = false;

		CBlinkScript* blinkscript = mDeadBg->GetScript<CBlinkScript>();
		blinkscript->SwitchOff();

		RewindStart();
	}
	void CStage::SetClearCollider(Vector3 _Pos)
	{
		mClearCollider = object::Instantiate<CGameObj>(eLayerType::Platforms, L"ClearCollider");
		mClearCollider->SetPos(_Pos);

		CCollider2D* coll = mClearCollider->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetScale(Vector2(1.f, 5.f));
		coll->Initialize();
		coll->SetName(L"col_clear");
		coll->SetType(eColliderType::Rect);


	}
	void CStage::CamReset()
	{
		renderer::mainCamera->GetCamScript()->CamFollowOff();
		renderer::mainCamera->GetCamScript()->AllDirBlockOff();
		renderer::mainCamera->GetOwner()->SetPos(Vector3::Zero);
	}
	void CStage::BatteryParticleCreateAndStart()
	{
		mBatteryParticle = object::Instantiate<CGameObj>(eLayerType::Particle, mHudBattery, L"BatteryParticle");
		mBatteryParticle->SetName(L"BatteryParticleSystem");
		Vector3 ParentWorldPos =  mHudBattery->GetUIWorldPos();
		mBatteryParticle->SetPos(ParentWorldPos);
		CParticleSystem* particleSystem = mBatteryParticle->AddComponent<CParticleSystem>(eComponentType::Particle);

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BatteryParticleMat");
		particleSystem->SetMaterial(Material);

		Vector4 startPos = Vector4(ParentWorldPos.x, ParentWorldPos.y, 0.f, 1.f);
		particleSystem->MakeParticleBufferData(startPos, 30, 0.5f, 1.f, 10.5f, 0.f, 0);
		particleSystem->SetParticleCountInFrame(3);
		particleSystem->SetFrequency(0.5f);
		renderer::ParticleSystemCB cb = {};
		particleSystem->MakeConstantBufferData(L"BatteryParticleCS", cb);

		particleSystem->SetMaxElapsedTime(5.f);
		particleSystem->Initialize();
	}
	void CStage::KeyUI_LeftOn(Vector3 _Pos)
	{
		mKeyLeft->RenderingBlockOff();
		mKeyLeft->SetPos(_Pos);
	}
	void CStage::KeyUI_RightOn(Vector3 _Pos)
	{
		mKeyRight->RenderingBlockOff();
		mKeyRight->SetPos(_Pos);
	}
	void CStage::KeyUI_UpOn(Vector3 _Pos)
	{
		mKeyUp->RenderingBlockOff();
		mKeyUp->SetPos(_Pos);
	}
	void CStage::KeyUI_DownOn(Vector3 _Pos)
	{
		mKeyDown->RenderingBlockOff();
		mKeyDown->SetPos(_Pos);
	}
	void CStage::KeyUI_ShiftOn(Vector3 _Pos)
	{
		mKeyShift->RenderingBlockOff();
		mKeyShift->SetPos(_Pos);
	}
	void CStage::KeyUI_LClickOn(Vector3 _Pos)
	{
		mKeyLClick->RenderingBlockOff();
		mKeyLClick->SetPos(_Pos);
	}
	void CStage::KeyUI_LeftOff()
	{
		mKeyLeft->RenderingBlockOn();
	}
	void CStage::KeyUI_RightOff()
	{
		mKeyRight->RenderingBlockOn();
	}
	void CStage::KeyUI_UpOff()
	{
		mKeyUp->RenderingBlockOn();
	}
	void CStage::KeyUI_DownOff()
	{
		mKeyDown->RenderingBlockOn();
	}
	void CStage::KeyUI_ShiftOff()
	{
		mKeyShift->RenderingBlockOn();
	}
	void CStage::KeyUI_LClickOff()
	{
		mKeyLClick->RenderingBlockOn();
	}
	void CStage::bulletTime()
	{
		if (CInput::GetKeyUp(eKeyCode::LSHIFT))
		{
			BulletTimeOff();
		}

		if (mbBulletTimeStun)
		{
			bulletTimeStunOperate();
		}
		else
		{
			if (CInput::GetKeyNone(eKeyCode::LSHIFT))
			{
				mBulletTimeGauge += CTimeMgr::DeltaTime() / 2.f;
				if (mBulletTimeGauge > 10.f)
				{
					mBulletTimeGauge = 10.f;
				}
			}
			if (CInput::GetKeyDown(eKeyCode::LSHIFT))
			{
				BulletTimeOn();
				mBulletTimeGauge -= (CTimeMgr::DeltaTime() * 3.f);
				if (mBulletTimeGauge < 0.f)
				{
					mBulletTimeGauge = 0.f;
				}
			}
		}

	}
	void CStage::bulletTimeStunOperate()
	{
		mBulletTimeCooldown += CTimeMgr::DeltaTimeConstant();
		CTimeMgr::BulletTimeOff();
		mBulletTimeMask->RenderingBlockOn();

		if (mBulletTimeCooldown >= 3.f)
		{
			mbBulletTimeStun = false;
			mBulletTimeGauge = 1.f;
			mBulletTimeCooldown = 0.f;
		}
	}
	void CStage::BulletTimeOn()
	{
		if (!CTimeMgr::IsBulletTimeOn())
		{
			CTimeMgr::BulletTimeOn();
			mBulletTimeMask->RenderingBlockOff();
		}
	}
	void CStage::BulletTimeOff()
	{
		if (CTimeMgr::IsBulletTimeOn())
		{
			CTimeMgr::BulletTimeOff();
			mBulletTimeMask->RenderingBlockOn();
		}
	}
}