#include "StageTutorial.h"
#include "SceneMain.h"
#include "PlayerScript.h"

namespace dru
{
	CStageTutorial::CStageTutorial()
		: mFadeTimer(0.f)
		, mTutorGapTimer(0.f)
		, mbFadeDone(false)
		, mbZoomDone(false)
		, mbMaskMove(false)
		, mbTutorBgMoveDone(false)
		, mbBulletTimeSuccess(false)

		, mCount1(0)
		, mCount2(0)
		, mCount3(0)

		, mMaskTarget(nullptr)
		, mCamTarget(nullptr)
		, mStageBackground(nullptr)
		, mScreenMask(nullptr)
		, mUIBg(nullptr)
		, mTutorialtxt(nullptr)
		, mTutorStage(TutorialStage::Attack)
		, mTutorBg(nullptr)
		, mTutorBgTarget(nullptr)
		, mKeyLeft(nullptr)
		, mKeyRight(nullptr)
		, mKeyUp(nullptr)
		, mKeyDown(nullptr)
		, mKeyShift(nullptr)
		, mKeyEnter(nullptr)
		, mKeyLClick(nullptr)

	{
	}

	CStageTutorial::~CStageTutorial()
	{
	}

	void CStageTutorial::InitStage()
	{

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// ¹è°æ ºg¸®¾ó
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stagetutorial");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stagetutorial", L"SpriteShader");
			CResources::Insert<CMaterial>(L"StageTutorial", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(3.f, 0.f, 5.f));
			mStageBackground->SetScale(Vector3(8.f, 8.f, 1.f));
		}

		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-0.f, -2.9f, 4.999f));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}

		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-9.f, -2.3f, 4.999f));
			mPlayer->GetComponent<CAnimator>()->Play(L"Player_Run");
			mPlayer->SetRight();
			mPlayer->GetComponent<CRigidBody>()->SetMaxVelocity(Vector3(3.f, 7.f, 0.f));
			mPlayer->GetScript<CPlayerScript>()->InputBlocking();

			dynamic_cast<CSceneMain*>(mScene)->SetPlayer(mPlayer);
		}

		{
			CGameObj* mReadyTrigger = object::Instantiate<CGameObj>(eLayerType::Platforms, L"TutorialReadyTrigger");
			mReadyTrigger->SetPos(Vector3(0.f, 0.f, 1.f));
			mReadyTrigger->SetScale(Vector3(1.f, 1.f, 1.f));

			CCollider2D* coll = mReadyTrigger->AddComponent<CCollider2D>(eComponentType::Collider);
			coll->SetName(L"col_readyTrigger");
			coll->SetType(eColliderType::Rect);
			coll->SetScale(Vector2(0.2f, 10.f));

		}

	}

	void CStageTutorial::LoadinReady()
	{
		renderer::mainCamera->SetProjectionType(eProjectionType::Perspective);
		Vector3 pos = renderer::mainCamera->GetOwner()->GetPos();
		renderer::mainCamera->GetOwner()->SetPos(Vector3(pos.x, pos.y, -CAMTYPEGAP));
		renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>()->SetScale(Vector2(10.f, 10.f));

		{
			mCamTarget = object::Instantiate<CGameObj>(eLayerType::None, L"CamTargetTutorialStage");
			mCamTarget->SetPos(Vector3(0.f, -2.f, 0.25f));
			mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}



		{
			COutWallSide* LeftOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-10.f, 0.f, 4.999f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}


		{
			COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(10.f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}

		{
			COutWall* UpOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"UpOutWall");
			UpOutWall->SetPos(Vector3(0.f, 18.f, 4.999f));
			UpOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}

		{
			COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
			DownOutWall->SetPos(Vector3(0.f, -18.f, 4.999f));
			DownOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}	
	}

	void CStageTutorial::Update()
	{
		if (mStageState == eStageState::NotReady)
		{
			NotReadyOperate();
		}

		if (mStageState == eStageState::ReadyEnd)
		{
			ReadyEndOperate();
		}

		if (mStageState == eStageState::LoadUI)
		{
			LoadUIOperate();
		}

		if (mStageState == eStageState::LoadEnd)
		{
			LoadEndOperate();
		}

		CStage::Update();
	}


	void CStageTutorial::Exit()
	{
		mStageState = eStageState::NotReady;
		mbZoomDone = false;
	}
	void CStageTutorial::NotReadyOperate()
	{
		mPlayer->GetComponent<CRigidBody>()->AddForce({ 100.f, 0.f, 0.f });

		CStage::NotReadyOperate();
	}
	void CStageTutorial::ReadyOperate()
	{

		CStage::ReadyOperate();
	}
	void CStageTutorial::ReadyEndOperate()
	{
		if (!mbZoomDone)
		{
			if (renderer::mainCamera->GetOwner()->MoveToTarget_Smooth_bool(mCamTarget, 0.5f, true))
			{
				// ÁÜ ³¡³ª¸é
				mCamTarget->Die();
				CreateTitle();
				mbZoomDone = true;
			}
		}		

		if (mbZoomDone && !mbFadeDone)
		{
			if (mFadeTimer < 1.f)
			{
				mFadeTimer += CTimeMgr::DeltaTime();
			}
			else
			{
				CreateEnterKeyUI();
				mbFadeDone = true;
			}
		}

		CStage::ReadyEndOperate();
	}
	void CStageTutorial::LoadUIOperate()
	{
		mUIBg->Die();
		mTutorialtxt->Die();
		mKeyEnter->Die();

		{
			// Æ©Åä¸®¾ó ¹è°æ
			mTutorBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"TutorBg");
			CSpriteRenderer* SpriteRenderer = mTutorBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
			CResources::Insert<CMaterial>(L"TB1Mat", Material);
			SpriteRenderer->SetMaterial(Material);

			mTutorBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
			mTutorBg->SetPos(Vector3(-10.f, 2.f, 4.999f));
			mTutorBg->SetScale(Vector3(0.20f, 0.25f, 1.f));
		}

		{
			mTutorBgTarget = object::Instantiate<CGameObj>(eLayerType::None, L"TB1T");
			mTutorBgTarget->SetPos(Vector3(0.f, 2.f, 4.999f));
			mTutorBgTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}

		LoadKeyUI();
		CStage::LoadUIOperate();
	}


	void CStageTutorial::LoadEndOperate()
	{
		TutorialOperation(mTutorStage);

		CStage::LoadEndOperate();
	}


	void CStageTutorial::CreateTitle()
	{
		{
			// Æ©Åä¸®¾ó Á¦¸ñ UI
			mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"TutorialTitleBg");
			CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
			SpriteRenderer->SetMaterial(Material);

			mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
			mUIBg->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);
			mUIBg->SetPos(Vector3(0.f, -1.f, 2.5f));
			mUIBg->SetScale(Vector3(10.f, 0.05f, 1.f));
		}
		{
			mTutorialtxt = object::Instantiate<CGameObj>(eLayerType::UI, L"Tutorialtxt");

			CSpriteRenderer* SpriteRenderer = mTutorialtxt->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"tutorialtxt", L"FadeShader");
			CResources::Insert<CMaterial>(L"tutorialtxtmat", Material);
			SpriteRenderer->SetMaterial(Material);
			CFadeScript* script = mTutorialtxt->AddComponent<CFadeScript>(eComponentType::Script);
			script->SetFadeTextureType(1);
			script->SetFadeType(1);

			mTutorialtxt->SetPos(Vector3(0.f, 3.5f, 2.4f));
			mTutorialtxt->SetScale(Vector3(0.5f, 0.5f, 1.f));

		}
	}
	void CStageTutorial::CreateEnterKeyUI()
	{
		{
			mKeyEnter = object::Instantiate<CGameObj>(eLayerType::UI, mTutorialtxt, L"keyEnter");
			CSpriteRenderer* SpriteRenderer = mKeyEnter->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyEnter->SetPos(Vector3(0.f, -0.75f, 0.f));

			CAnimator* mAnimator = mKeyEnter->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyEnter_anim", Material->GetTexture(), { 167.f, 0.f }, { 24.f, 20 }, Vector2::Zero, 2, { 100.f, 80.f }, 1.f);
			mAnimator->Play(L"KeyEnter_anim");
		}
	}
	void CStageTutorial::TutorialOperation(TutorialStage _Stage)
	{
		if (mTutorStage != TutorialStage::Clear)
		{
			if (!mbTutorBgMoveDone)
			{
				TutorReset(_Stage);
				if (mTutorBg->MoveToTarget_Smooth_bool(mTutorBgTarget, 0.3f, true))
				{

					switch (_Stage)
					{
					case dru::TutorialStage::Move:
						TutorMove();
						break;
					case dru::TutorialStage::Jump_Crouch:
						TutorJumpAndCrouch();
						break;
					case dru::TutorialStage::Roll:
						TutorRoll();
						break;
					case dru::TutorialStage::Attack:
						TutorAttack();
						break;
					case dru::TutorialStage::Wall:
						TutorWall();
						break;
					case dru::TutorialStage::BulletTime:
						TutorBulletTime();
						break;
					case dru::TutorialStage::End:
						break;
					default:
						break;
					}
					mbTutorBgMoveDone = true;
				}
			}
			else
			{

				switch (_Stage)
				{
				case dru::TutorialStage::Move:
					TutorMoveCheck();
					break;
				case dru::TutorialStage::Jump_Crouch:
					TutorJumpAndCrouchCheck();
					break;
				case dru::TutorialStage::Roll:
					TutorRollCheck();
					break;
				case dru::TutorialStage::Attack:
					TutorAttackCheck();
					break;
				case dru::TutorialStage::Wall:
					TutorWallCheck();
					break;
				case dru::TutorialStage::BulletTime:
					TutorBulletTimeCheck();
					break;
				case dru::TutorialStage::End:
					break;
				default:
					break;
				}
			}
		}
		else
		{
			int i = 0;

		}
	}
	void CStageTutorial::TutorMove()
	{
		mKeyLeft->RenderingBlockOff();
		mKeyRight->RenderingBlockOff();

		mKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
	}


	void CStageTutorial::TutorJumpAndCrouch()
	{
		mKeyUp->RenderingBlockOff();
		mKeyDown->RenderingBlockOff();

		mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim", false);
		mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_none");
	}

	void CStageTutorial::TutorRoll()
	{
		mKeyLeft->RenderingBlockOff();
		mKeyRight->RenderingBlockOff();
		mKeyDown->RenderingBlockOff();

		mKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_anim");
	}

	void CStageTutorial::TutorAttack()
	{
		CreateMonster();

		mKeyLClick->RenderingBlockOff();
		mKeyLClick->GetComponent<CAnimator>()->Play(L"LClick_anim");

	}

	void CStageTutorial::TutorWall()
	{
		{
			CGameObj* mLeftwall = object::Instantiate<CWall>(eLayerType::Platforms, L"lwall");
			mLeftwall->SetPos(Vector3(-9.f, -0.25f, 4.999f));
			mLeftwall->SetScale(Vector3(1.f, 5.f, 4.999f));

			CSpriteRenderer* SpriteRenderer = mLeftwall->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"wallMat");
			SpriteRenderer->SetMaterial(Material);
		}

		{
			CGameObj* mRightwall = object::Instantiate<CWall>(eLayerType::Platforms, L"rwall");
			mRightwall->SetPos(Vector3(9.f, -0.25f, 4.999f));
			mRightwall->SetScale(Vector3(1.f, 5.f, 4.999f));

			CSpriteRenderer* SpriteRenderer = mRightwall->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"wallMat");
			SpriteRenderer->SetMaterial(Material);
		}

		mKeyLeft->RenderingBlockOff();
		mKeyRight->RenderingBlockOff();
		mKeyUp->RenderingBlockOff();
	
		mKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim");
	}

	void CStageTutorial::TutorBulletTime()
	{
		mKeyShift->RenderingBlockOff();
		mKeyShift->GetComponent<CAnimator>()->Play(L"Shift_anim");

	}

	void dru::CStageTutorial::TutorMoveCheck()
	{
		if (3 <= mCount1 && 3 <= mCount2)
		{
			TutorSuccess(TutorialStage::Jump_Crouch);
		}

		if (CInput::GetKeyTap(eKeyCode::A))
		{
			++mCount1;
		}
		if (CInput::GetKeyTap(eKeyCode::D))
		{
			++mCount2;
		}
	}

	void dru::CStageTutorial::TutorJumpAndCrouchCheck()
	{
		if (3 <= mCount1)
		{
			TutorSuccess(TutorialStage::Roll);
		}

		if (CInput::GetKeyTap(eKeyCode::W))
		{
			++mCount1;
		}
	}

	void dru::CStageTutorial::TutorRollCheck()
	{
		if (3 <= mCount1)
		{
			TutorSuccess(TutorialStage::Attack);
		}

		if ((CInput::GetKeyDown(eKeyCode::S) && (CInput::GetKeyTap(eKeyCode::A) || CInput::GetKeyTap(eKeyCode::D)))
			|| (CInput::GetKeyTap(eKeyCode::S) && (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D))))
		{
			++mCount1;
		}
	}

	void dru::CStageTutorial::TutorAttackCheck()
	{

		if (3 <= mCount1)
		{
			TutorSuccess(TutorialStage::Wall);
		}

		if (CInput::GetKeyTap(eKeyCode::LBTN))
		{
			++mCount1;
		}
	}

	void dru::CStageTutorial::TutorWallCheck()
	{
		if (3 <= mCount1)
		{
			TutorSuccess(TutorialStage::BulletTime);
		}

		CPlayerScript* script = mPlayer->GetScript<CPlayerScript>();

		if (script->IsOnWall() && CInput::GetKeyTap(eKeyCode::W))
		{
			++mCount1;
		}
	}

	void dru::CStageTutorial::TutorBulletTimeCheck()
	{
		if (5 >= mPlayer->GetScript<CPlayerScript>()->GetBulletTimeGauge())
		{
			mbBulletTimeSuccess = true;
		}
		if (mbBulletTimeSuccess)
		{
			TutorSuccess(TutorialStage::Clear);
		}
	}

	void CStageTutorial::TutorSuccess(TutorialStage _Stage)
	{
		mTutorBgTarget->SetPos(Vector3(-10.f, 2.f, 4.999f));
		mTutorBg->GetScript<CBackgroundColorScript>()->SetColor(Vector4{ 0.f, 0.5f, 0.f, 0.5f });

		mTutorGapTimer += CTimeMgr::DeltaTime();

		if (1.f < mTutorGapTimer)
		{
			if (mTutorBg->MoveToTarget_Smooth_bool(mTutorBgTarget, 0.3f, true))
			{
				mTutorStage = _Stage;
				mTutorGapTimer = 0.f;
				mbTutorBgMoveDone = false;
			}
		}
	}

	void CStageTutorial::TutorReset(TutorialStage _Stage)
	{
		switch (_Stage)
		{
		case dru::TutorialStage::Move:
			break;
		case dru::TutorialStage::Jump_Crouch:
			mKeyLeft->RenderingBlockOn();
			mKeyRight->RenderingBlockOn();
			break;
		case dru::TutorialStage::Roll:
			mKeyUp->RenderingBlockOn();
			mKeyDown->RenderingBlockOn();
			break;
		case dru::TutorialStage::Attack:
			mKeyLeft->RenderingBlockOn();
			mKeyRight->RenderingBlockOn();
			mKeyDown->RenderingBlockOn();
			break;
		case dru::TutorialStage::Wall:
			mKeyLClick->RenderingBlockOn();
			break;
		case dru::TutorialStage::BulletTime:
			mKeyLeft->RenderingBlockOn();
			mKeyRight->RenderingBlockOn();
			mKeyUp->RenderingBlockOn();
			break;
		case dru::TutorialStage::Clear:
			mKeyShift->RenderingBlockOn();
			break;
		case dru::TutorialStage::End:
			break;
		default:
			break;
		}
		mCount1 = 0;
		mCount2 = 0;
		mCount3 = 0;
		mTutorBgTarget->SetPos(Vector3(0.f, 2.f, 4.999f));
		mTutorBg->GetScript<CBackgroundColorScript>()->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
	}

	void CStageTutorial::LoadKeyUI()
	{
		{
			mKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyA");
			CSpriteRenderer* SpriteRenderer = mKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLeft->SetPos(Vector3(-0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_press", Material->GetTexture(), { 42.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_anim", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyA_anim", false);
			mAnimator->GetCompleteEvent(L"KeyA_anim") = std::bind(&CStageTutorial::LComplete, this);
		}

		{
			mKeyRight = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyD");
			CSpriteRenderer* SpriteRenderer = mKeyRight->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyRight->SetPos(Vector3(0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyRight->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyD_none", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_press", Material->GetTexture(), { 70.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyD_none", false);
			mAnimator->GetCompleteEvent(L"KeyD_anim") = std::bind(&CStageTutorial::RComplete, this);
		}

		{
			mKeyUp = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyW");
			CSpriteRenderer* SpriteRenderer = mKeyUp->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyUp->SetPos(Vector3(0.f, -0.2f, 0.f));

			CAnimator* mAnimator = mKeyUp->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyW_none", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_press", Material->GetTexture(), { 98.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_anim", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyW_anim", false);
			mAnimator->GetCompleteEvent(L"KeyW_anim") = std::bind(&CStageTutorial::UComplete, this);

		}

		{
			mKeyDown = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyS");
			CSpriteRenderer* SpriteRenderer = mKeyDown->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyDown->SetPos(Vector3(0.f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyDown->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyS_none", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_press", Material->GetTexture(), { 14.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_anim", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyS_none", false);
			mAnimator->GetCompleteEvent(L"KeyS_anim") = std::bind(&CStageTutorial::DComplete, this);
		}

		{
			mKeyLClick = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"LClick");
			CSpriteRenderer* SpriteRenderer = mKeyLClick->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLClick->SetPos(Vector3(0.f, -0.35f, 0.f));

			CAnimator* mAnimator = mKeyLClick->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"LClick_anim", Material->GetTexture(), { 112.f, 0.f }, { 13.f, 17.f }, Vector2::Zero, 2, { 75.f, 60.f }, 0.5f);
			mAnimator->Play(L"LClick_anim");
		}
		{
			mKeyShift = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"Shift");
			CSpriteRenderer* SpriteRenderer = mKeyShift->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyShift->SetPos(Vector3(0.f, -0.35f, 0.f));

			CAnimator* mAnimator = mKeyShift->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"Shift_anim", Material->GetTexture(), { 215.f, 2.f }, { 32.f, 16.f }, Vector2::Zero, 2, { 75.f, 60.f }, 2.f);
			mAnimator->Play(L"Shift_anim");
		}
		mKeyLeft->RenderingBlockOn();
		mKeyRight->RenderingBlockOn();
		mKeyUp->RenderingBlockOn();
		mKeyDown->RenderingBlockOn();
		mKeyLClick->RenderingBlockOn();
		mKeyShift->RenderingBlockOn();
	}

	void CStageTutorial::CreateMonster()
	{	
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(-4.f, -2.3f, 4.999f));
		}
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(-0.f, -2.3f, 4.999f));
		}
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(4.f, -2.3f, 4.999f));
		}
	}

	void CStageTutorial::LComplete()
	{
		mKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_none");
		mKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_anim", false);
	}
	void CStageTutorial::RComplete()
	{
		mKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
	}
	void CStageTutorial::UComplete()
	{
		if (mTutorStage == dru::TutorialStage::Jump_Crouch)
		{
			mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_none");
			mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_anim", false);
		}
	}
	void CStageTutorial::DComplete()
	{
		if (mTutorStage == dru::TutorialStage::Jump_Crouch)
		{
			mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_none");
			mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim", false);
		}

	}
}