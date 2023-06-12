#include "HeadhunterScript.h"
#include "Headhunter.h"
#include "TimeMgr.h"
#include "CameraScript.h"
#include "Object.h"

namespace dru
{
	CHeadhunterScript::CHeadhunterScript()
		: mHeadhunter(nullptr)
		, mAudioSource(nullptr)
		, mExplosion(nullptr)
		, mAttackCollider(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mStatePattern3{}
		, mStatePattern4{}
		, mStatePattern5{}
		, mDashOrigin{}
		, mDashDest{}
		, mDodgeCooldown(5.f)
		, mDodgeRadius(2.5f)
		, mDodgeTimer(0.f)
		, mHideTimer(0.f)
		, mDashElapsedTime(0.f)
		, mPattern1_AimingTime(0.f)
		, mVerticalShootCount(0)
	{
	}

	CHeadhunterScript::~CHeadhunterScript()
	{
	}

	void CHeadhunterScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAudioSource = GetOwner()->GetComponent<CAudioSource>();

		mPatternCount = 3;

		AddAnimationCallBack();
		AddAnimationCallBack_Lamda();

		mHeadhunter = dynamic_cast<CHeadhunter*>(GetOwner());

		CBossScript::Initialize();
	}

	void CHeadhunterScript::update()
	{
		if (!GetOwner_LiveObject()->IsRewindRePlaying())
		{

			DodgeOperate();
			Hide();

			CBossScript::update();
		}
	}

	void CHeadhunterScript::fixedUpdate()
	{
		CBossScript::fixedUpdate();
	}

	void CHeadhunterScript::render()
	{
		CBossScript::render();
	}

	void CHeadhunterScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!GetStatePattern5(ePattern5::Dash) && !GetState(eBossState::Hide) && !GetState(eBossState::Dodge) && !GetState(eBossState::Hurt))
			{
				Hit();
				PatternEnd();
				SetSingleState(eBossState::Hurt);		
				mAnimator->Play(L"Headhunter_HurtAir", false);
			}
		}
		if (L"col_floor" == _oppo->GetName())
		{
			if (mAnimator->IsPlaying(L"Headhunter_HurtAir"))
			{
				mAnimator->Play(L"Headhunter_HurtLand", false);
			}
			if (mAnimator->IsPlaying(L"Headhunter_TumbleAir"))
			{
				mAnimator->Play(L"Headhunter_TumbleLand", false);
			}
			if (mAnimator->IsPlaying(L"Headhunter_BackJump"))
			{
				PatternEnd();
			}
			if (GetStatePattern2(ePattern2::WallKickFall))
			{
				SetStatePattern2Off(ePattern2::WallKickFall);
				SetStatePattern2On(ePattern2::WallKickLand);
				mAnimator->Play(L"Headhunter_WallKickLand", false);
			}
			if (GetStatePattern5(ePattern5::Dash))
			{
				SetStatePattern5Off(ePattern5::Dash);
				SetStatePattern5On(ePattern5::DashEnd);
				mAnimator->Play(L"Headhunter_DashEnd", false);
			}		

		}
		if (L"col_wall" == _oppo->GetName())
		{
			if (mAnimator->IsPlaying(L"Headhunter_BackJump"))
			{
				mState[(UINT)eBossState::Dodge] = false;
				mRigidbody->SetVelocityX(0.f);
				mRigidbody->SetVelocityY(0.f);
				WallKickReady();
			}


		}

		CBossScript::OnCollisionEnter(_oppo);
	}

	void CHeadhunterScript::OnCollision(CCollider2D* _oppo)
	{
		CBossScript::OnCollision(_oppo);
	}

	void CHeadhunterScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CBossScript::OnCollisionExit(_oppo);
	}

	void CHeadhunterScript::Reset()
	{
		mRigidbody->SwitchOn();
		mRigidbody->SetVelocity(Vector3::Zero);
		GetOwner()->RenderingBlockOff();
		mDodgeTimer = 0.f;
		mHideTimer = 0.f;
		mbFlipWhilePattern = false;
		mDashElapsedTime = 0.f;
		mVerticalShootCount = 0;

		mRigidbody->SetMaxVelocity(VELOCITY_RUN);

		AllPatternReset();
		AfterImageReset();

		CBossScript::Reset();
	}

	void CHeadhunterScript::AllPatternReset()
	{
		mStatePattern1.reset();
		mStatePattern2.reset();
		mStatePattern3.reset();
		mStatePattern4.reset();
		mStatePattern5.reset();
		mStatePattern6.reset();

	}

	void CHeadhunterScript::AfterImageReset()
	{
		mHeadhunter->ResetAfterImageColor();
		mHeadhunter->SetAfterImageCount(0);
	}

	void CHeadhunterScript::AddAnimationCallBack()
	{
	}

	void CHeadhunterScript::AddAnimationCallBack_Lamda()
	{
		mAnimator->GetCompleteEvent(L"Headhunter_TumbleLand") = [this]
		{
			Reset();
			mRigidbody->SetVelocity(Vector3::Zero);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_HurtLand") = [this]
		{
			mAnimator->Play(L"Headhunter_Hide", false);
			SetSingleState(eBossState::Hide);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_Hide") = [this]
		{
			PlayExplosion();
			PushPlayer();
			mRigidbody->SwitchOff();
			GetOwner()->SetPos(SCREEN_CENTERTOP);
			GetOwner()->RenderingBlockOn();
		};

		mAnimator->GetCompleteEvent(L"Headhunter_TakeoutRifle") = [this]
		{
			SetStatePattern1Off(ePattern1::Takeout);
			SetStatePattern1On(ePattern1::Aim);
			mbFlipWhilePattern = true;
		};

		mAnimator->GetCompleteEvent(L"Headhunter_PutbackRifle") = [this]
		{
			PatternEnd();
		};
		mAnimator->GetCompleteEvent(L"Headhunter_WallKickReady") = [this]
		{
			mRigidbody->SwitchOn();
			SetStatePattern2Off(ePattern2::WallKickReady);
			SetStatePattern2On(ePattern2::WallKick);
			mAnimator->Play(L"Headhunter_WallKick", false);
			WallKick();
		};
		mAnimator->GetCompleteEvent(L"Headhunter_WallKick") = [this]
		{
			SetStatePattern2Off(ePattern2::WallKick);
			SetStatePattern2On(ePattern2::WallKickAttack);
			mAnimator->Play(L"Headhunter_WallKickAttack", false);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_WallKickAttack") = [this]
		{
			SetStatePattern2Off(ePattern2::WallKickAttack);
			SetStatePattern2On(ePattern2::WallKickFall);
			mAnimator->Play(L"Headhunter_WallKickFall", false);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_WallKickLand") = [this]
		{
			PatternEnd();
		};
		mAnimator->GetCompleteEvent(L"Headhunter_TakeoutDagger") = [this]
		{
			SetStatePattern3Off(ePattern3::Takeout);
			SetStatePattern3On(ePattern3::Dash);
			mHeadhunter->SetAfterImageColor(RED);
			mHeadhunter->SetAfterImageCount(100);
			mDashOrigin = GetOwnerWorldPos();
			mDashDest = GetOwnerWorldPos();
			mDashDest.x = 7.f;
			if (mbIsPlayerLeft)
			{
				mDashDest.x *= -1.f;
			}
			mAnimator->Play(L"Headhunter_Dash");
		};

		
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifleStart") = [this]
		{
			SetStatePattern5Off(ePattern5::SweepStart);
			SetStatePattern5On(ePattern5::Sweep);
			mAnimator->Play(L"Headhunter_SweepRifle", false);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifle") = [this]
		{
			SetStatePattern5Off(ePattern5::Sweep);
			SetStatePattern5On(ePattern5::Dash);
			mHeadhunter->SetAfterImageColor(RED);
			mHeadhunter->SetAfterImageCount(100);
			mDashOrigin = GetOwnerWorldPos();
			mAnimator->Play(L"Headhunter_Dash");
		};
		mAnimator->GetCompleteEvent(L"Headhunter_DashEnd") = [this]
		{
			PatternEnd();
		};
		mAnimator->GetCompleteEvent(L"Headhunter_VerticalLaserAppear") = [this]
		{
			mAnimator->Play(L"Headhunter_VerticalLaserDisappear", false);
			SetStatePattern6Off(ePattern6::VerticalLaserAppear);
			SetStatePattern6On(ePattern6::VerticalLaserDisappear);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_VerticalLaserDisappear") = [this]
		{
			SetStatePattern6Off(ePattern6::VerticalLaserDisappear);
		};		
	}

	void CHeadhunterScript::DodgeOperate()
	{
		DodgeStart();
	}

	void CHeadhunterScript::DodgeStart()
	{
		if (mDodgeCooldown < 5.f)
		{
			mDodgeCooldown += CTimeMgr::DeltaTime();
		}
		else
		{
			if (!Patterning() && !GetState(eBossState::Hide) && !GetState(eBossState::Hurt) && GetOwner()->IsOnFloor())
			{
				if (mDodgeRadius > GetDistanceOfPlayer())
				{
					SetSingleState(eBossState::Dodge);
					mHeadhunter->SetAfterImageColor(MAGENTA);
					mHeadhunter->SetAfterImageCount(30);
					mAnimator->Play(L"Headhunter_TumbleAir", false);
					mDodgeCooldown = 0.f;
					SetDodgeDir();
				}
			}
		}
	}

	void CHeadhunterScript::SetDodgeDir()
	{
		mRigidbody->SetMaxVelocity(MV_DODGE);
		if (GetOwnerWorldPos().x < 0.f)
		{
			mRigidbody->AddForceX(100000.f);
		}
		else
		{
			mRigidbody->AddForceX(-100000.f);
		}
		mRigidbody->AddForceY(100000.f);
	}

	void CHeadhunterScript::Hide()
	{
		if (GetState(eBossState::Hide))
		{
			if (mHideTimer < 1.f)
			{
				mHideTimer += CTimeMgr::DeltaTime();
			}
			else
			{
				if (2 == mHeadhunter->GetHp())
				{
					SetSingleState(eBossState::Pattern5);
					SetStatePattern5On(ePattern5::SweepStart);
					GetOwner()->RenderingBlockOff();
					mAnimator->Play(L"Headhunter_SweepRifleStart", false);
					mHideTimer = 0.f;
				}
				else if (1 == mHeadhunter->GetHp())
				{
					SetSingleState(eBossState::Pattern6);
					GetOwner()->RenderingBlockOff();
					mHideTimer = 0.f;
				}
			}
		}
	}

	void CHeadhunterScript::DashOperate()
	{
		if (mDashElapsedTime <= DASH_TIMER)
		{
			Dash();
		}
		else
		{
			DashEnd();
		}
	}

	void CHeadhunterScript::Dash()
	{
		Vector3 newPos = {};
		mDashElapsedTime += CTimeMgr::DeltaTime();
		newPos = Interpolation(0.f, DASH_TIMER, mDashElapsedTime, mDashOrigin, mDashDest);
		Vector3 pos = GetOwnerWorldPos();
		pos = newPos;
		GetOwner()->SetPos(pos);
	}

	void CHeadhunterScript::DashEnd()
	{
		mDashElapsedTime = 0.f;
		mRigidbody->SwitchOn();

		if (GetState(eBossState::Pattern3))
		{
			SetStatePattern3Off(ePattern3::Dash);
			SetStatePattern3On(ePattern3::DashEnd);
			mAnimator->Play(L"Headhunter_DashEnd", false);
		}

		return;
	}

	void CHeadhunterScript::Hit()
	{
		CTimeMgr::BulletTime(0.5f);

		ShakeParams sp = {};
		sp.duration = 0.5f;
		sp.magnitude = 0.0500f;
		renderer::mainCamera->GetCamScript()->Shake(sp);

		SetHitDir();
		mRigidbody->SetVelocity(mMoveDir * 10.f);
		mTransform->AddPositionY(1.f);

		mHeadhunter->Damaged();

		AfterImageReset();
		mbFlipWhilePattern = false;
	}

	void CHeadhunterScript::Pattern1()
	{
		if (!GetStatePattern1(ePattern1::Takeout))
		{
			mAnimator->Play(L"Headhunter_TakeoutRifle", false);
			SetStatePattern1On(ePattern1::Takeout);

		}
		if (GetStatePattern1(ePattern1::Aim))
		{
			AimingOperate();
			mAnimator->Play(GetAimRifleKey());
		}
		if (GetStatePattern1(ePattern1::Shoot))
		{
			SetStatePattern1Off(ePattern1::Shoot);
			SetStatePattern1On(ePattern1::Putback);
			mAnimator->Play(L"Headhunter_PutbackRifle", false);
		}

	}

	std::wstring CHeadhunterScript::GetAimRifleKey()
	{
		float angle = GetDegreeFromTwoPointZ_0180(GetOwner()->GetWorldPos(), mPlayer->GetWorldPos());

		int idx = static_cast<int>(angle / 10.f);
		std::wstring key = L"Headhunter_AimRifle";
		std::wstring stridx = std::to_wstring(idx);
		key += stridx;
		return key;
	}

	void CHeadhunterScript::AimingOperate()
	{
		if (mPattern1_AimingTime < 1.f)
		{
			mPattern1_AimingTime += CTimeMgr::DeltaTime();
		}
		else
		{
			SetStatePattern1Off(ePattern1::Aim);
			SetStatePattern1On(ePattern1::Shoot);
			mbFlipWhilePattern = false;
			mPattern1_AimingTime = 0.f;
		}
	}

	void CHeadhunterScript::Pattern2()
	{
		if (!GetStatePattern2(ePattern2::BackJump))
		{
			BackJump();
		}
	}

	void CHeadhunterScript::BackJump()
	{
		mAnimator->Play(L"Headhunter_BackJump", false);
		SetStatePattern2On(ePattern2::BackJump);
		mState[(UINT)eBossState::Dodge] = true;
		mHeadhunter->SetAfterImageColor(MAGENTA);
		mHeadhunter->SetAfterImageCount(30);

		SetBackJumpForce();
	}

	void CHeadhunterScript::SetBackJumpForce()
	{
		// 벽과의 거리에 따라 X방향 힘 계산
		// 7.7은 벽의 위치
		float posX = GetOwnerPos().x;
		float wallPos = 0.f;
		float dist = 0.f;
		float ForceX = 100000.f;
		if (0.f < posX)
		{
			wallPos = 7.7f;
			dist = wallPos - posX;
		}
		else
		{
			wallPos = -7.7f;
			dist = wallPos - posX;
			ForceX *= -1.f;
		}
		mRigidbody->SetMaxVelocity({ MV_BACKJUMP.x * fabs(dist), MV_BACKJUMP.y, MV_BACKJUMP .z});

		mRigidbody->AddForceX(ForceX);
		mRigidbody->AddForceY(100000.f);
	}


	void CHeadhunterScript::WallKickReady()
	{
		mRigidbody->SwitchOff();
		mAnimator->Play(L"Headhunter_WallKickReady", false);
		SetStatePattern2On(ePattern2::WallKickReady);
	}

	void CHeadhunterScript::WallKick()
	{
		mRigidbody->SetMaxVelocity(MV_WALLKICK);

		if (GetOwner()->IsLeft())
		{
			mRigidbody->AddForceX(-100000.f);
		}
		else
		{
			mRigidbody->AddForceX(100000.f);
		}
		mRigidbody->AddForceY(100000);
	}

	void CHeadhunterScript::WallKickAttackStart()
	{
		SetStatePattern2Off(ePattern2::WallKick);
		SetStatePattern2On(ePattern2::WallKickAttack);
		mAnimator->Play(L"Headhunter_WallKickAttack", false);
	}

	void CHeadhunterScript::Pattern3()
	{
		if (!GetStatePattern3(ePattern3::Takeout))
		{
			SetStatePattern3On(ePattern3::Takeout);
			mAnimator->Play(L"Headhunter_TakeoutDagger", false);
		}
		if (GetStatePattern3(ePattern3::Dash))
		{
			DashOperate();
		}

	}

	void CHeadhunterScript::Pattern4()
	{
	}

	void CHeadhunterScript::Pattern5()
	{
		if (GetStatePattern5(ePattern5::Dash))
		{
			mDashDest = SCREEN_CENTERFLOOR;
			DashOperate();
		}
	}

	void CHeadhunterScript::Pattern6()
	{
		if (!GetStatePattern6(ePattern6::VerticalLaserAppear) && !GetStatePattern6(ePattern6::VerticalLaserDisappear))
		{
			if (7 > mVerticalShootCount)
			{
				SetStatePattern6On(ePattern6::VerticalLaserAppear);
				mAnimator->Play(L"Headhunter_VerticalLaserAppear", false);

			}
			
		}



	}

	void CHeadhunterScript::PatternEnd()
	{
		mPattern1_AimingTime = 0.f;

		Reset();
	}

	void CHeadhunterScript::PlayerReset()
	{
		mPlayer->RenderingBlockOff();
		// mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
	}

	void CHeadhunterScript::PushPlayer()
	{
		if (1.f > GetDistanceOfPlayer())
		{
			mPlayer->GetComponent<CAnimator>()->Play(L"Player_Dead", false);
			mPlayer->SetPlayerStun();
			CAnimator* playerAnimator = mPlayer->GetComponent<CAnimator>();
			{
				CRigidBody* playerRigidBody = mPlayer->GetComponent<CRigidBody>();

				if (mPlayer->GetWorldPos().x > GetOwnerWorldPos().x)
				{
					playerRigidBody->SetVelocity({ 10.f, 0.f, 0.f });
				}
				else
				{
					playerRigidBody->SetVelocity({ -10.f, 0.f, 0.f });
				}
			}
		}
	}

	CGameObj* CHeadhunterScript::GetOrCreateExplosionObject()
	{
		if (!mExplosion)
		{
			// create
			mExplosion = object::Instantiate<CGameObj>(eLayerType::FX, L"Explosion");
			if (mExplosion)
			{
				// intialize
				InitializeExplosionComponent();
			}
		}

		return mExplosion;
	}

	void CHeadhunterScript::InitializeExplosionComponent()
	{
		CGameObj* ExplosionObject = GetOrCreateExplosionObject();
		if (ExplosionObject)
		{
			ExplosionObject->SetScale({ 1.5f, 1.5f, 1.f });

			std::shared_ptr<CTexture> ExplosionObjectTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = ExplosionObject->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"ExplosionMat");
				if (Material)
				{
					ExplosionObjectTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			if (ExplosionObjectTexture)
			{
				CAnimator* ExplosionObjectAnimator = ExplosionObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (ExplosionObjectAnimator)
				{
					ExplosionObjectAnimator->Create(L"Explosion", ExplosionObjectTexture, { 0.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 11, { 50.f, 50.f }, 0.1f);
					ExplosionObjectAnimator->GetCompleteEvent(L"Explosion") = [this]
					{
						mExplosion->RenderingBlockOn();
					};
				}
				else
				{
					assert(false);
				}
			}
			ExplosionObject->RenderingBlockOn();
		}
	}

	void CHeadhunterScript::PlayExplosion()
	{
		CGameObj* ExplosionObject = GetOrCreateExplosionObject();
		if (ExplosionObject)
		{
			ExplosionPositioning();

			CAnimator* ExplosionObjectAnimator = ExplosionObject->GetComponent<CAnimator>();
			if (ExplosionObjectAnimator)
			{
				ExplosionObject->RenderingBlockOff();
				ExplosionObjectAnimator->Play(L"Explosion", false);
			}
			else
			{
				assert(false);
			}
		}
	}

	void CHeadhunterScript::ExplosionPositioning()
	{
		CGameObj* ExplosionObject = GetOrCreateExplosionObject();
		if (ExplosionObject)
		{
			CAnimator* ExplosionObjectAnimator = ExplosionObject->GetComponent<CAnimator>();
			if (ExplosionObjectAnimator)
			{
				ExplosionObject->RenderingBlockOff();
				ExplosionObjectAnimator->Play(L"Explosion", false);
				Vector3 pos = GetOwnerPos();
				pos.y += 0.5f;
				ExplosionObject->SetPos(pos);
			}
			else
			{
				assert(false);
			}
		}
	}

}