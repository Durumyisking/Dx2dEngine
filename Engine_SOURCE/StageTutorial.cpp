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

		, mCount1(0)
		, mCount2(0)
		, mCount3(0)

		, mMaskTarget(nullptr)
		, mCamTarget(nullptr)
		, mStageBackground(nullptr)
		, mScreenMask(nullptr)
		, mUIBg(nullptr)
		, mTutorialtxt(nullptr)
		, mTutorStage(TutorialStage::Move)
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
			// 배경 튵리얼
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

	void CStageTutorial::LoadAfterReady()
	{
		renderer::mainCamera->SetProjectionType(eProjectionType::Perspective);
		Vector3 pos = renderer::mainCamera->GetOwner()->GetPos();
		renderer::mainCamera->GetOwner()->SetPos(Vector3(pos.x, pos.y, -CAMTYPEGAP));

		//Vector3 pos2 = mStageBackground->GetPos();
		//mStageBackground->SetPos(Vector3(pos2.x, pos2.y - 0.75f, pos2.z));

		{
			mCamTarget = object::Instantiate<CGameObj>(eLayerType::None, L"CamTargetTutorialStage");
			mCamTarget->SetPos(Vector3(0.f, -2.f, 0.25f));
			mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}



		{
			COutWall* LeftOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-8.25f, 0.f, 4.999f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}


		{
			COutWall* RightOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(8.25f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}
	}

	void CStageTutorial::Update()
	{
		if (mReady == eReadyState::NotReady)
		{
			mPlayer->GetComponent<CRigidBody>()->AddForce({ 100.f, 0.f, 0.f });
		}

		if (mReady == eReadyState::ReadyEnd)
		{
			if (!mbZoomDone)
			{

				if (renderer::mainCamera->GetOwner()->MoveToTarget_Smooth(mCamTarget, 0.5f))
				{
					mbZoomDone = true;
					mCamTarget->Die();

					{
						// 튜토리얼 제목 UI
						mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"TutorialTitleBg");
						CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

						std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
						SpriteRenderer->SetMaterial(Material);

						mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
						mUIBg->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);
						mUIBg->SetPos(Vector3(0.f, -1.f, 2.5f));
						mUIBg->SetScale(Vector3(10.f, 0.05f, 1.f));
					}

				}

			}
			else
			{
				if (!mbFadeDone)
				{

					if (mFadeTimer < 1.f)
					{
						mFadeTimer += CTimeMgr::DeltaTime();
					}
					else
					{
						mTutorialtxt = object::Instantiate<CGameObj>(eLayerType::UI, L"Tutorialtxt");

						CSpriteRenderer* SpriteRenderer = mTutorialtxt->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
						std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"tutorialtxt", L"FadeShader");
						CResources::Insert<CMaterial>(L"tutorialtxtmat", Material);
						SpriteRenderer->SetMaterial(Material);
						mTutorialtxt->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);

						mTutorialtxt->SetPos(Vector3(0.f, 3.5f, 2.4f));
						mTutorialtxt->SetScale(Vector3(0.5f, 0.5f, 1.f));

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

						mbFadeDone = true;
					}
				}
			}

			if (dynamic_cast<CSceneMain*>(mOwner)->ISLoad() && (mReady == eReadyState::ReadyEnd))
			{
				mUIBg->Die();
				mTutorialtxt->Die();
				mKeyEnter->Die();

				mReady = eReadyState::LoadEnd;

				{
					// 튜토리얼 배경
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

			}
		}

		if (mReady == eReadyState::LoadEnd)
		{
			TutorialOperation(mTutorStage);

		}



		CStage::Update();
	}
	void CStageTutorial::TutorialOperation(TutorialStage _Stage)
	{
		if (!mbTutorBgMoveDone)
		{
			TutorReset(_Stage);
			if (mTutorBg->MoveToTarget_Smooth(mTutorBgTarget, 0.3f))
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
	void CStageTutorial::TutorMove()
	{
		{
			mKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyA");
			CSpriteRenderer* SpriteRenderer = mKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLeft->SetPos(Vector3(-0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
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
			mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyD_none");
			mAnimator->GetCompleteEvent(L"KeyD_anim") = std::bind(&CStageTutorial::RComplete, this);
		}

	}


	void CStageTutorial::TutorJumpAndCrouch()
	{
		{
			mKeyUp = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyW");
			CSpriteRenderer* SpriteRenderer = mKeyUp->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyUp->SetPos(Vector3(0.f, -0.25f, 0.f));

			CAnimator* mAnimator = mKeyUp->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyW_none", Material->GetTexture(), { 84.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
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
			mAnimator->Create(L"KeyS_anim", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyS_none");
			mAnimator->GetCompleteEvent(L"KeyS_anim") = std::bind(&CStageTutorial::DComplete, this);
		}
	}

	void CStageTutorial::TutorRoll()
	{
		{
			mKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyA");
			CSpriteRenderer* SpriteRenderer = mKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLeft->SetPos(Vector3(-0.2f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
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
			mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyD_none");
			mAnimator->GetCompleteEvent(L"KeyD_anim") = std::bind(&CStageTutorial::RComplete, this);
		}

		{
			mKeyDown = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyS");
			CSpriteRenderer* SpriteRenderer = mKeyDown->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyDown->SetPos(Vector3(0.f, -0.5f, 0.f));

			CAnimator* mAnimator = mKeyDown->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"KeyS_none", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
			mAnimator->Create(L"KeyS_anim", Material->GetTexture(), { 0.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 0.5f);
			mAnimator->Play(L"KeyS_anim");
		}

	}

	void CStageTutorial::TutorAttack()
	{
		{
			CGameObj* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.3f, 4.999f));
		}

		{
			mKeyLClick = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"LClick");
			CSpriteRenderer* SpriteRenderer = mKeyLClick->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
			SpriteRenderer->SetMaterial(Material);
			mKeyLClick->SetPos(Vector3(0.f, -0.4f, 0.f));

			CAnimator* mAnimator = mKeyLClick->AddComponent<CAnimator>(eComponentType::Animator);
			mAnimator->Create(L"LClick_anim", Material->GetTexture(), { 112.f, 0.f }, { 13.f, 17.f }, Vector2::Zero, 2, { 75.f, 60.f }, 0.5f);
			mAnimator->Play(L"LClick_anim");

		}

	}

	void CStageTutorial::TutorWall()
	{
	}

	void CStageTutorial::TutorBulletTime()
	{
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
			TutorSuccess(TutorialStage::Attack);
		}

		if (CInput::GetKeyTap(eKeyCode::LBTN))
		{
			++mCount1;
		}
	}

	void dru::CStageTutorial::TutorWallCheck()
	{
	}

	void dru::CStageTutorial::TutorBulletTimeCheck()
	{
	}

	void CStageTutorial::TutorSuccess(TutorialStage _Stage)
	{
		mTutorBgTarget->SetPos(Vector3(-10.f, 2.f, 4.999f));
		mTutorBg->GetScript<CBackgroundColorScript>()->SetColor(Vector4{ 0.f, 0.5f, 0.f, 0.5f });

		mTutorGapTimer += CTimeMgr::DeltaTime();

		if (1.f < mTutorGapTimer)
		{
			if (mTutorBg->MoveToTarget_Smooth(mTutorBgTarget, 0.3f))
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
			mKeyLeft->Die();
			mKeyRight->Die();
			break;
		case dru::TutorialStage::Roll:
			mKeyUp->Die();
			mKeyDown->Die();
			break;
		case dru::TutorialStage::Attack:
			mKeyLeft->Die();
			mKeyRight->Die();
			mKeyDown->Die();
			break;
		case dru::TutorialStage::Wall:
			mKeyLClick->Die();
			break;
		case dru::TutorialStage::BulletTime:
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
		mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_none");
		mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_anim", false);
	}
	void CStageTutorial::DComplete()
	{
		mKeyDown->GetComponent<CAnimator>()->Play(L"KeyS_none");
		mKeyUp->GetComponent<CAnimator>()->Play(L"KeyW_anim", false);
	}
}