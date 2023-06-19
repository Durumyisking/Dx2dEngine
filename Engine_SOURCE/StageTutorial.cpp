#include "StageTutorial.h"
#include "SceneMain.h"

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
		, mbCorrectSoundPlayed(false)
		, mCount1(0)
		, mCount2(0)
		, mCount3(0)
		, mMaskTarget(nullptr)
		, mCamTarget(nullptr)
		, mScreenMask(nullptr)
		, mUIBg(nullptr)
		, mTutorialtxt(nullptr)
		, mTutorStage(TutorialStage::Move)
		, mTutorBg(nullptr)
		, mTutorBgTarget(nullptr)
		, mTKeyLeft(nullptr)
		, mTKeyRight(nullptr)
		, mTKeyUp(nullptr)
		, mTKeyDown(nullptr)
		, mTKeyShift(nullptr)
		, mTKeyEnter(nullptr)
		, mTKeyLClick(nullptr)
		, mMask(nullptr)

	{
		mStageNumbmer = 0;
	}

	CStageTutorial::~CStageTutorial()
	{
	}

	void CStageTutorial::InitStage()
	{

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// 배경 튵리얼
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stagetutorial");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

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
			mPlayer->GetComponent<CAudioSource>()->Play(L"player_footstep", true);

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
		CreatePostProcess_Snow();
		mPostProcess_Snow->RenderingBlockOff();
	}

	void CStageTutorial::LoadinReady()
	{
		renderer::mainCamera->SetProjectionType(eProjectionType::Perspective);
		Vector3 pos = renderer::mainCamera->GetOwner()->GetPos();
		renderer::mainCamera->GetOwner()->SetPos(Vector3(pos.x, pos.y, -CAMTYPEGAP));
		renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>()->SetScale(Vector2(10.f, 10.f));
		mPlayer->SetPos(Vector3(mPlayer->GetPos().x, mPlayer->GetPos().y, 4.999f));

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

		CStage::Update();
	}


	void CStageTutorial::Exit()
	{
		mbZoomDone = false;
		mPostProcess_Snow->RenderingBlockOn();
		renderer::mainCamera->SetProjectionType(eProjectionType::Orthographic);
		CCollider2D* coll = renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>();
		coll->SetScale(Vector2(GetDevice()->ViewportWidth() / 102.5f, GetDevice()->ViewportHeight() / 100.f));
		renderer::mainCamera->GetOwner()->SetPos(Vector3::Zero);
		mPlayer->GetComponent<CAudioSource>()->Stop(L"song_tutorial_bgm");

		CStage::Exit();
	}
	void CStageTutorial::Reset()
	{
		CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
		playerScript->Reset();
		
		CStage::Reset();
	}
	void CStageTutorial::AddStartingLiveObjects()
	{
		CStage::AddStartingLiveObjects();
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
				// 줌 끝나면
				mCamTarget->Die();
				CreateTitle();
				mbZoomDone = true;

			}
			else
			{
				if (mPostProcess_Snow->MoveToTarget_Smooth_bool(mPlayer, 0.001f, true))
				{
					Vector3 vPos = mPlayer->GetPos();
					vPos.x += 0.229f;
					vPos.y += 2.3325f;
					mPostProcess_Snow->SetPos(vPos);
					mPostProcess_Snow->SetScale({ 10.25f, 5.765625f, 1.f });
				}
				else
				{
					Vector3 vPos = mPlayer->GetPos();
					vPos.x += 0.229f;
					vPos.y += 2.3325f;
					mPostProcess_Snow->SetPos(vPos);
				}
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
				mFadeTimer = 0.f;
			}
		}
		CStage::ReadyEndOperate();
	}
	void CStageTutorial::LoadUIOperate()
	{
		mUIBg->Die();
		mTutorialtxt->Die();
		mTKeyEnter->Die();

		{
			// 튜토리얼 배경
			mTutorBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"TutorBg");
			CSpriteRenderer* SpriteRenderer = mTutorBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

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

		// 클리어시 넘어가야댐
		if (mTutorStage == TutorialStage::Clear)
		{
			if (!mbFadeDone)
			{
				if (mFadeTimer > 3.f)
				{
					mbFadeDone = true;
				}
				else
				{
					mFadeTimer += CTimeMgr::DeltaTime();
					mPlayer->GetComponent<CAudioSource>()->SetVolume(L"song_tutorial_bgm", Interpolation<float>(0.f, 3.f, mFadeTimer, 1.f, 0.f));
				}
			}
			else
			{
				mbFadeDone = false;
			
				Reset();
				Exit();

				mbClear = true;
				return;
			}
		}

		CStage::LoadEndOperate();
	}


	void CStageTutorial::CreateTitle()
	{
		{
			// 튜토리얼 제목 UI
			mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"TutorialTitleBg");
			CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
			SpriteRenderer->SetMaterial(Material);

			mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
			mUIBg->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);
			mUIBg->SetPos(Vector3(0.f, -1.f, 2.5f));
			mUIBg->SetScale(Vector3(10.f, 0.05f, 1.f));
			mPlayer->GetComponent<CAudioSource>()->Play(L"song_tutorial_bgm", true);
		}
		{
			mTutorialtxt = object::Instantiate<CGameObj>(eLayerType::UI, L"Tutorialtxt");

			CSpriteRenderer* SpriteRenderer = mTutorialtxt->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
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
			mTKeyEnter = object::Instantiate<CGameObj>(eLayerType::UI, mTutorialtxt, L"keyEnter");
			CSpriteRenderer* SpriteRenderer = mTKeyEnter->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyEnter->SetPos(Vector3(0.f, -0.75f, 0.f));

			CAnimator* mAnimator = mTKeyEnter->AddComponent<CAnimator>(eComponentType::Animator);
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
	}
	void CStageTutorial::TutorMove()
	{
		mTKeyLeft->RenderingBlockOff();
		mTKeyRight->RenderingBlockOff();

		mTKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mTKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
	}


	void CStageTutorial::TutorJumpAndCrouch()
	{
		mTKeyUp->RenderingBlockOff();
		mTKeyDown->RenderingBlockOff();

		mTKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim", false);
		mTKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_none");
	}

	void CStageTutorial::TutorRoll()
	{
		mTKeyLeft->RenderingBlockOff();
		mTKeyRight->RenderingBlockOff();
		mTKeyDown->RenderingBlockOff();

		mTKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mTKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mTKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_anim");
	}

	void CStageTutorial::TutorAttack()
	{
		CreateMonster();

		mTKeyLClick->RenderingBlockOff();
		mTKeyLClick->GetComponent<CAnimator>()->Play(L"LClick_anim");

	}

	void CStageTutorial::TutorWall()
	{
		{
			CGameObj* mLeftwall = object::Instantiate<CWall>(eLayerType::Platforms, L"lwall");
			mLeftwall->SetPos(Vector3(-9.f, -0.25f, 4.999f));
			mLeftwall->SetScale(Vector3(1.f, 5.f, 4.999f));

			CSpriteRenderer* SpriteRenderer = mLeftwall->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"wallMat");
			SpriteRenderer->SetMaterial(Material);
		}

		{
			CGameObj* mRightwall = object::Instantiate<CWall>(eLayerType::Platforms, L"rwall");
			mRightwall->SetPos(Vector3(9.f, -0.25f, 4.999f));
			mRightwall->SetScale(Vector3(1.f, 5.f, 4.999f));

			CSpriteRenderer* SpriteRenderer = mRightwall->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"wallMat");
			SpriteRenderer->SetMaterial(Material);
		}

		mTKeyLeft->RenderingBlockOff();
		mTKeyRight->RenderingBlockOff();
		mTKeyUp->RenderingBlockOff();
	
		mTKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
		mTKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mTKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim");
	}

	void CStageTutorial::TutorBulletTime()
	{
		mTKeyShift->RenderingBlockOff();
		mTKeyShift->GetComponent<CAnimator>()->Play(L"Shift_anim");

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
		if (5 >= mBulletTimeGauge)
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
		if (!mbCorrectSoundPlayed)
		{
			mPlayer->GetComponent<CAudioSource>()->Play(L"SE_correct");
			mbCorrectSoundPlayed = true;
		}

		mTutorBgTarget->SetPos(Vector3(-10.f, 2.f, 4.999f));
		if (TutorialStage::Clear != mTutorStage)
		{
			mTutorBg->GetScript<CBackgroundColorScript>()->SetColor(Vector4{ 0.f, 0.5f, 0.f, 0.5f });
		}

		mTutorGapTimer += CTimeMgr::DeltaTime();

		if (1.f < mTutorGapTimer)
		{
			if (mTutorBg->MoveToTarget_Smooth_bool(mTutorBgTarget, 0.3f, true))
			{
				mTutorStage = _Stage;
				mTutorGapTimer = 0.f;
				mbTutorBgMoveDone = false;
				mbCorrectSoundPlayed = false;

				if (TutorialStage::Clear ==  mTutorStage)
				{
					// 검정 텍스처 Fadein용 오브젝트 생성
					mMask = object::Instantiate<CGameObj>(eLayerType::UI, L"StageMask");
					CSpriteRenderer* SpriteRenderer = mMask->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

					std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"FadeShader");
					CResources::Insert<CMaterial>(L"TutorEndMat", Material);
					SpriteRenderer->SetMaterial(Material);

					CFadeScript* script = mMask->AddComponent<CFadeScript>(eComponentType::Script);
					script->SetFadeTextureType(0);
					script->SetFadeTime(3.f);
					script->SetFadeType(1);
	
					Vector3 camPos = renderer::mainCamera->GetOwnerPos();
					camPos.z += 3.f;
					mMask->SetPos(camPos);
					mMask->SetScale(Vector3(100.f, 100.f, 1.f));

					mbFadeDone = false;
				}
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
			mTKeyLeft->RenderingBlockOn();
			mTKeyRight->RenderingBlockOn();
			break;
		case dru::TutorialStage::Roll:
			mTKeyUp->RenderingBlockOn();
			mTKeyDown->RenderingBlockOn();
			break;
		case dru::TutorialStage::Attack:
			mTKeyLeft->RenderingBlockOn();
			mTKeyRight->RenderingBlockOn();
			mTKeyDown->RenderingBlockOn();
			break;
		case dru::TutorialStage::Wall:
			mTKeyLClick->RenderingBlockOn();
			break;
		case dru::TutorialStage::BulletTime:
			mTKeyLeft->RenderingBlockOn();
			mTKeyRight->RenderingBlockOn();
			mTKeyUp->RenderingBlockOn();
			break;
		case dru::TutorialStage::Clear:
			mTKeyShift->RenderingBlockOn();
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
			mTKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyA");
			CSpriteRenderer* SpriteRenderer = mTKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyLeft->SetPos(Vector3(-0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mTKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_press", Material->GetTexture(), { 42.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyA_anim", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyA_anim", false);
			mAnimator->GetCompleteEvent(L"KeyA_anim") = std::bind(&CStageTutorial::LComplete, this);
		}

		{
			mTKeyRight = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyD");
			CSpriteRenderer* SpriteRenderer = mTKeyRight->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyRight->SetPos(Vector3(0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mTKeyRight->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyD_none", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_press", Material->GetTexture(), { 70.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyD_none", false);
			mAnimator->GetCompleteEvent(L"KeyD_anim") = std::bind(&CStageTutorial::RComplete, this);
		}

		{
			mTKeyUp = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyW");
			CSpriteRenderer* SpriteRenderer = mTKeyUp->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyUp->SetPos(Vector3(0.f, -0.2f, 0.f));

			CAnimator* mAnimator = mTKeyUp->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyW_none", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_press", Material->GetTexture(), { 98.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyW_anim", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyW_anim", false);
			mAnimator->GetCompleteEvent(L"KeyW_anim") = std::bind(&CStageTutorial::UComplete, this);

		}

		{
			mTKeyDown = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyS");
			CSpriteRenderer* SpriteRenderer = mTKeyDown->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyDown->SetPos(Vector3(0.f, -0.5f, 0.f));

			CAnimator* mAnimator = mTKeyDown->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyS_none", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_press", Material->GetTexture(), { 14.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_anim", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyS_none", false);
			mAnimator->GetCompleteEvent(L"KeyS_anim") = std::bind(&CStageTutorial::DComplete, this);
		}

		{
			mTKeyLClick = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"LClick");
			CSpriteRenderer* SpriteRenderer = mTKeyLClick->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyLClick->SetPos(Vector3(0.f, -0.35f, 0.f));

			CAnimator* mAnimator = mTKeyLClick->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"LClick_anim", Material->GetTexture(), { 112.f, 0.f }, { 13.f, 17.f }, Vector2::Zero, 2, { 75.f, 60.f }, 0.5f);
			mAnimator->Play(L"LClick_anim");
		}
		{
			mTKeyShift = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"Shift");
			CSpriteRenderer* SpriteRenderer = mTKeyShift->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mTKeyShift->SetPos(Vector3(0.f, -0.35f, 0.f));

			CAnimator* mAnimator = mTKeyShift->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"Shift_anim", Material->GetTexture(), { 215.f, 2.f }, { 32.f, 16.f }, Vector2::Zero, 2, { 75.f, 60.f }, 2.f);
			mAnimator->Play(L"Shift_anim");
		}
		mTKeyLeft->RenderingBlockOn();
		mTKeyRight->RenderingBlockOn();
		mTKeyUp->RenderingBlockOn();
		mTKeyDown->RenderingBlockOn();
		mTKeyLClick->RenderingBlockOn();
		mTKeyShift->RenderingBlockOn();
	}

	void CStageTutorial::CreateMonster()
	{	
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(-4.f, -2.3f, 4.999f));
			Mon->Initialize();
		}
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(-0.f, -2.3f, 4.999f));
			Mon->Initialize();
		}
		{
			CGameObj* Mon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			Mon->SetPos(Vector3(4.f, -2.3f, 4.999f));
			Mon->Initialize();
		}
	}

	void CStageTutorial::LComplete()
	{
		mTKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_none");
		mTKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_anim", false);
	}
	void CStageTutorial::RComplete()
	{
		mTKeyRight->GetComponent<CAnimator>()->Play(L"KeyD_none");
		mTKeyLeft->GetComponent<CAnimator>()->Play(L"KeyA_anim", false);
	}
	void CStageTutorial::UComplete()
	{
		if (mTutorStage == dru::TutorialStage::Jump_Crouch)
		{
			mTKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_none");
			mTKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_anim", false);
		}
	}
	void CStageTutorial::DComplete()
	{
		if (mTutorStage == dru::TutorialStage::Jump_Crouch)
		{
			mTKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_none");
			mTKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim", false);
		}

	}
}