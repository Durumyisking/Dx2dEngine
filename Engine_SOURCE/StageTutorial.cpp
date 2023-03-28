#include "StageTutorial.h"
#include "SceneMain.h"

namespace dru
{
	CStageTutorial::CStageTutorial()
		: mFadeTimer(0.f)
		, mbFadeDone(false)
		, mbZoomDone(false)
		, mbMaskMove(false)
		, mbTutorBgMoveDone(false)

		, mT1RCount(0)
		, mT1LCount(0)


		, mMaskTarget(nullptr)
		, mCamTarget(nullptr)
		, mStageBackground(nullptr)
		, mScreenMask(nullptr)
		, mUIBg(nullptr)
		, mTutorialtxt(nullptr)
		, mTutorStage(TutorialStage::Move)
		, mTutorBg(nullptr)
		, mTutorBg1Target(nullptr)
		, mKeyLeft(nullptr)
		, mKeyRight(nullptr)
		, mKeyUp(nullptr)
		, mKeyDown(nullptr)
		, mKeyShift(nullptr)
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
			// 硅版 篻府倔
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
			CGameObj* mReadyTrigger= object::Instantiate<CGameObj>(eLayerType::Platforms, L"TutorialReadyTrigger");
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

		{
			CGrunt* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.3f, 4.999f));
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
				
				if(renderer::mainCamera->GetOwner()->MoveToTarget_Smooth(mCamTarget, 0.5f))
				{
					mbZoomDone = true;
					mCamTarget->Die();

					{
						// 譬配府倔 力格 UI
						mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"TutorialTitleBg");
						CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

						std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
						//CResources::Insert<CMaterial>(L"TutorialTitleBgMat", Material);
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
						std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"tutorialtxt", L"UIShader");
						CResources::Insert<CMaterial>(L"tutorialtxtmat", Material);
						SpriteRenderer->SetMaterial(Material);
						// mTutorialtxt->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);

						mTutorialtxt->SetPos(Vector3(0.f, 3.5f, 2.4f));
						mTutorialtxt->SetScale(Vector3(0.5f, 0.5f, 1.f));




						mbFadeDone = true;
					}
				}
			}

			if (dynamic_cast<CSceneMain*>(mOwner)->ISLoad() && (mReady == eReadyState::ReadyEnd))
			{
				//dynamic_cast<CFadeScript*>(mUIBg->GetScripts()[1])->restart(0);
				mUIBg->Die();
				mTutorialtxt->Die();

				mReady = eReadyState::LoadEnd;

				{
					// 譬配府倔 力格 UI
					mTutorBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"TutorBg1");
					CSpriteRenderer* SpriteRenderer = mTutorBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

					std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
					CResources::Insert<CMaterial>(L"TB1Mat", Material);
					SpriteRenderer->SetMaterial(Material);

					mTutorBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
					mTutorBg->SetPos(Vector3(-10.f, 2.f, 4.999f));
					mTutorBg->SetScale(Vector3(0.20f, 0.25f, 1.f));
				}

				{
					mTutorBg1Target = object::Instantiate<CGameObj>(eLayerType::None, L"TB1T");
					mTutorBg1Target->SetPos(Vector3(0.f, 2.f, 4.999f));
					mTutorBg1Target->SetScale(Vector3(0.4f, 0.4f, 1.f));
				}

			}
		}

		if (mReady == eReadyState::LoadEnd)
		{
			if (mTutorStage == TutorialStage::Move)
			{
				TutorMove();
			}
			if (mTutorStage == TutorialStage::Jump_Crouch)
			{

			}
		}



		CStage::Update();
	}
	void CStageTutorial::TutorMove()
	{
		if (!mbTutorBgMoveDone)
		{
			if (mTutorBg->MoveToTarget_Smooth(mTutorBg1Target, 0.3f))
			{
				{
					mKeyLeft = object::Instantiate<CGameObj>(eLayerType::UI, mTutorBg, L"keyA");
					CSpriteRenderer* SpriteRenderer = mKeyLeft->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
					std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"keys");
					SpriteRenderer->SetMaterial(Material);
					mKeyLeft->SetPos(Vector3(-0.2f, -0.5f, 0.f));

					CAnimator* mAnimator = mKeyLeft->AddComponent<CAnimator>(eComponentType::Animator);
					mAnimator->Create(L"KeyA_none", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 1, { 75.f, 75.f }, 1.f);
					mAnimator->Create(L"KeyA_anim", Material->GetTexture(), { 28.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 1.f);
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
					mAnimator->Create(L"KeyD_anim", Material->GetTexture(), { 56.f, 3.f }, { 14.f, 14.f }, Vector2::Zero, 2, { 75.f, 75.f }, 1.f);
					mAnimator->Play(L"KeyD_none");
					mAnimator->GetCompleteEvent(L"KeyD_anim") = std::bind(&CStageTutorial::RComplete, this);
				}

				mbTutorBgMoveDone = true;
			}
		}
		else
		{
			if (3 <= mT1LCount && 3 <= mT1RCount)
			{
				mTutorBg1Target->SetPos(Vector3(-10.f, -1.f, 4.99999f));
				mTutorBg->GetScript<CBackgroundColorScript>()->SetColor(Vector4{ 0.f, 0.5f, 0.f, 0.5f });
				mTutorStage = TutorialStage::Jump_Crouch;
				mbTutorBgMoveDone = false;
			}

			if (CInput::GetKeyTap(eKeyCode::A))
			{
				++mT1LCount;
			}
			if (CInput::GetKeyTap(eKeyCode::D))
			{
				++mT1RCount;
			}

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
}