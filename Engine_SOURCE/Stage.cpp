#include "Stage.h"
#include "BlinkScript.h"
#include "SceneMain.h"

namespace dru
{

	CStage::CStage()
		: mStageState(eStageState::NotReady)
		, mbClear(false)
		, mClearCollider(nullptr)
		, mScene(nullptr)
		, mDeadBg(nullptr)
		, mbIsDeadBgOn(false)
		, mPlayer(nullptr)
		, mUICursor(nullptr)
		, mHudBatteryParts{}
		, mHudTimerBar(nullptr)
		, mHudLeftHand(nullptr)
		, mHudRightHand(nullptr)
		, mKeyEnter(nullptr)
		, mBulletTimeMask(nullptr)
		, mBulletTimeGaugePrev(10)
		, mBulletTimeGaugeCurrent(10)
		, mPlayerDefaultPos{}
		, mDefaultTimerBarPos{}
		, mDefaultTimerBarScale{}
		, mTimer(2000.f)
		, mElapsedTime(0.f)
		, mbRewinding(false)
		, mEnemyCount(0)
		, mRewindTimer(0.f)
		, mRewindObjects{}

	{
	}

	CStage::~CStage()
	{
	}

	void CStage::Update()
	{
		if (CInput::GetKeyTap(eKeyCode::M))
		{
			{
				CGameObj* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
				mMon->SetPos({ mPlayer->GetPos().x + 2.f, mPlayer->GetPos().y, 3.f });
				mMon->Initialize();
			}
		}
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
		}

	}

	void CStage::Exit()
	{
		mStageState = eStageState::NotReady;

		renderer::mainCamera->GetCamScript()->CamFollowOff();
		renderer::mainCamera->GetOwner()->SetPos(Vector3::Zero);

		CSceneMgr::LoadScene(CSceneMgr::eSceneType::Temp);
	}

	
	void CStage::LoadUI()
	{
		renderer::mainCamera->GetCamScript()->CamFollowOff();
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

			mHudTimerBar->SetPos(Vector3(0.228f, 4.248f, 1.f));
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
			for (int i = 0; i < 11; ++i)
			{
				std::wstring str = L"Hud_BatteryPartMat";
				std::wstring num = std::to_wstring(i);
				str += num;

				CGameObj* mHudBatteryPart = object::Instantiate<CBackground>(eLayerType::UI, str);

				mHudBatteryParts.push_back(mHudBatteryPart);

				CSpriteRenderer* SpriteRenderer = mHudBatteryPart->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_batterypart", L"UIShader");
				CResources::Insert<CMaterial>(str, Material);
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


		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"CursorMat");
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script)->Initialize();
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 4.9999f));
		}
		{			
			mBulletTimeMask = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"BulletTimeMask");

			CSpriteRenderer* SpriteRenderer = mBulletTimeMask->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
			CResources::Insert<CMaterial>(L"BulletTimeMaskMat", Material);
			SpriteRenderer->SetMaterial(Material);

			SpriteRenderer->ChangeColor(Vector4{ 0.f, 0.f, 0.f, 0.75f });
			mBulletTimeMask->SetPos(Vector3(0.f, 0.f, 5.f));
			mBulletTimeMask->SetScale(Vector3(30.f, 30.f, 0.f));
			mBulletTimeMask->RenderingBlockOn();
		}
	}

	void CStage::NotReadyOperate()
	{

	}

	void CStage::ReadyOperate()
	{
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
					DeadReset();
				}
			}
			else
			{
				mElapsedTime += CTimeMgr::DeltaTime();
				TimerBarOperate();

				if (CInput::GetKeyDown(eKeyCode::LSHIFT))
				{
					mBulletTimeMask->RenderingBlockOff();
				}
				if (CInput::GetKeyUp(eKeyCode::LSHIFT))
				{
					mBulletTimeMask->RenderingBlockOn();
				}

			}

			if (CInput::GetKeyTap(eKeyCode::R))
			{
				RewindStart();
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
		mElapsedTime = 0.f;
	}

	void CStage::AddStartingLiveObjects()
	{
		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(mPlayerDefaultPos);
			mRewindObjects.push_back(mPlayer);
		}
	}


	void CStage::BulletTimeBatteryOperation()
	{
		float gauge = mPlayer->GetScript<CPlayerScript>()->GetBulletTimeGauge();
		mBulletTimeGaugeCurrent = static_cast<UINT>(gauge);

		if (mBulletTimeGaugePrev <= mBulletTimeGaugeCurrent)
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
			mPlayer->GetScript<CPlayerScript>()->BulletTimeStun();
		}

		mBulletTimeGaugePrev = mBulletTimeGaugeCurrent;
	}

	void CStage::CreateDeadUI()
	{
		{
			if (!mDeadBg)
			{
				// 튜토리얼 배경
				mDeadBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"TutorBg");
				CSpriteRenderer* SpriteRenderer = mDeadBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

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
				CSpriteRenderer* SpriteRenderer = mKeyEnter->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
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
	void CStage::RewindStart()
	{
		if (CTimeMgr::IsBulletTimeOn())
			CTimeMgr::BulletTimeOff();

		mPlayer->GetScript<CPlayerScript>()->InputBlocking();
		mPlayer->RemoveAfterImage();
		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			mRewindObjects[i]->SetRewindOn();

			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->Disable();
			}
		}

		mbRewinding = true;
	}
	void CStage::Rewinding()
	{
	
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

		mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
		mPlayer->SetRight();
		mPlayer->Flip();

		for (size_t i = 0; i < mRewindObjects.size(); i++)
		{
			if (eLayerType::Monster == mRewindObjects[i]->GetLayerType())
			{
				dynamic_cast<CMonster*>(mRewindObjects[i])->AddRay();
			}
		}

		Reset();

		mbRewinding = false;

	}
	void CStage::DeadReset()
	{
		if (CTimeMgr::IsBulletTimeOn())
			CTimeMgr::BulletTimeOff();

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
}