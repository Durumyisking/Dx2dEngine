#include "HeadhunterScript.h"
#include "Headhunter.h"
#include "TimeMgr.h"
#include "CameraScript.h"

namespace dru
{
	CHeadhunterScript::CHeadhunterScript()
		: mHeadhunter(nullptr)
		, mAudioSource(nullptr)
		, mAttackCollider(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mStatePattern3{}
		, mDashOrigin{}
		, mDashDest{}
		, mDodgeDir{}
		, mDodgeCooldown(5.f)
		, mDodgeRadius(2.5f)
		, mDodgeTimer(0.f)
		, mHideTimer(0.f)
		, mDashElapsedTime(0.f)
		, mPattern1_AimingTime(0.f)
	{
	}

	CHeadhunterScript::~CHeadhunterScript()
	{
	}

	void CHeadhunterScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAudioSource = GetOwner()->GetComponent<CAudioSource>();

		mPatternCount = 1;

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
			if (!GetStatePattern2(ePattern2::Dash) && !GetState(eBossState::Hide) && !GetState(eBossState::Dodge) && !GetState(eBossState::Hurt))
			{
				Hit();
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
			if (GetStatePattern2(ePattern2::Dash))
			{
				SetStatePattern2Off(ePattern2::Dash);
				SetStatePattern2On(ePattern2::DashLand);
				mAnimator->Play(L"Headhunter_DashLand", false);
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
		GetOwner()->RenderingBlockOff();
		mDodgeCooldown = 5.f;

		AllPatternReset();
		AfterImageReset();

		CBossScript::Reset();
	}

	void CHeadhunterScript::AllPatternReset()
	{
		mStatePattern1.reset();
		mStatePattern2.reset();
		mStatePattern3.reset();
	
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
			mHeadhunter->SetAfterImageCount(0);
			mDodgeTimer = 0.f;
			SetSingleState(eBossState::Idle);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_HurtLand") = [this]
		{
			mRigidbody->SwitchOff();
			GetOwner()->SetPos(SCREEN_CENTERTOP);
			GetOwner()->RenderingBlockOn();
			SetSingleState(eBossState::Hide);
		};

		mAnimator->GetCompleteEvent(L"Headhunter_TakeoutRifle") = [this]
		{
			SetStatePattern1Off(ePattern1::Takeout);
			SetStatePattern1On(ePattern1::Aim);
		};

		mAnimator->GetCompleteEvent(L"Headhunter_PutbackRifle") = [this]
		{
			PatternEnd();
		};
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifleStart") = [this]
		{
			SetStatePattern2Off(ePattern2::SweepStart);
			SetStatePattern2On(ePattern2::Sweep);
			mAnimator->Play(L"Headhunter_SweepRifle", false);
		};
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifle") = [this]
		{
			SetStatePattern2Off(ePattern2::Sweep);
			SetStatePattern2On(ePattern2::Dash);
			mHeadhunter->SetAfterImageColor(RED);
			mHeadhunter->SetAfterImageCount(50);
			mDashOrigin = GetOwnerWorldPos();
			mAnimator->Play(L"Headhunter_Dash");
		};
		mAnimator->GetCompleteEvent(L"Headhunter_DashLand") = [this]
		{
			PatternEnd();
		};

		
	}

	void CHeadhunterScript::DodgeOperate()
	{
		DodgeStart();
		Dodge();
	}

	void CHeadhunterScript::DodgeStart()
	{
		if (mDodgeCooldown < 5.f)
		{
			mDodgeCooldown += CTimeMgr::DeltaTime();
		}
		else
		{
			if (!Patterning() && !GetState(eBossState::Hide) && GetOwner()->IsOnFloor())
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
		mDodgeDir = DEGREE_15;
		if (GetOwnerWorldPos().x < 0.f)
		{
			mDodgeDir.x *= 1.f;
		}
		else
		{
			mDodgeDir.x *= -1.f;
		}
		mDodgeDir.x *= 10.f;
		mDodgeDir.y *= 1.f;
	}

	void CHeadhunterScript::Dodge()
	{
		if (GetState(eBossState::Dodge))
		{
			if (mDodgeTimer > DODGE_TIMER)
			{
				mDodgeDir.y = 0.f;
			}
			else
			{
				mDodgeTimer += CTimeMgr::DeltaTime();
			}

			mRigidbody->AddVelocity(mDodgeDir);
		}
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
				SetSingleState(eBossState::Pattern2);
				SetStatePattern2On(ePattern2::SweepStart);
				GetOwner()->RenderingBlockOff();
				mAnimator->Play(L"Headhunter_SweepRifleStart", false);
				mHideTimer = 0.f;
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

		int idx = static_cast<int>( angle / 10.f);
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
			mbBlockFlipWhilePattern = true;
			mPattern1_AimingTime = 0.f;
		}
	}

	void CHeadhunterScript::Pattern2()
	{
		if (GetStatePattern2(ePattern2::Dash))
		{
			mDashDest = SCREEN_CENTERFLOOR;
			DashOperate();
		}
	}

	void CHeadhunterScript::Pattern3()
	{
	}

	void CHeadhunterScript::Pattern4()
	{
	}

	void CHeadhunterScript::Pattern5()
	{
	}

	void CHeadhunterScript::PatternEnd()
	{
		Reset();
	}

	void CHeadhunterScript::PlayerReset()
	{
		mPlayer->RenderingBlockOff();
		// mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
	}

}