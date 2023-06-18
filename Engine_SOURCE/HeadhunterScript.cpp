#include "HeadhunterScript.h"
#include "Headhunter.h"
#include "TimeMgr.h"
#include "CameraScript.h"
#include "Object.h"
#include "Bullet.h"
#include "ObjectPool.h"

#include "Input.h"

namespace dru
{
	CHeadhunterScript::CHeadhunterScript()
		: mHeadhunter(nullptr)
		, mAudioSource(nullptr)
		, mExplosion(nullptr)
		, mBeam(nullptr)
		, mAttackCollider(nullptr)
		, mBeamTransform(nullptr)
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
		, mBeamElapsedTime(0.f)
		, mBeamAngle(0.f)
		, mPattern2_ShootedBulletCountL(0)
		, mPattern2_ShootedBulletCountR(100)
		, mPattern5_SweepElapsedTime(0.f)
		, mPattern6_VerticalShootCount(0)
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
		if (L"col_player" == _oppo->GetName())
		{
			if (GetStatePattern3(ePattern3::Dash) || GetStatePattern5(ePattern5::Dash) || GetStatePattern6(ePattern6::Dash))
			{
				Vector3 pos = mHeadhunter->GetWorldPos();
				mPlayer->Hit(pos, 0);
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
		mBeamElapsedTime = 0.f;
		mPattern1_AimingTime = 0.f;
		mPattern2_ShootedBulletCountL = 0;
		mPattern2_ShootedBulletCountR = 100;
		mPattern5_SweepElapsedTime = 0.f;
		mPattern6_VerticalShootCount = 0;

		mRigidbody->SetMaxVelocity(VELOCITY_RUN);

		AllPatternReset();
		AfterImageReset();
		BeamOff();

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
			if (GetState(eBossState::Pattern5))
			{
				SetStatePattern5Off(ePattern5::SweepStart);
				SetStatePattern5On(ePattern5::Sweep);
				mAnimator->Play(L"Headhunter_SweepRifle", false);
			}
			if (GetState(eBossState::Pattern6))
			{
				if (GetStatePattern6(ePattern6::SweepStartL))
				{
					SetStatePattern6Off(ePattern6::SweepStartL);
					SetStatePattern6On(ePattern6::SweepL);
				}
				if (GetStatePattern6(ePattern6::SweepStartR))
				{
					SetStatePattern6Off(ePattern6::SweepStartR);
					SetStatePattern6On(ePattern6::SweepR);
				}
				mAnimator->Play(L"Headhunter_SweepRifle", false);
			}
		};
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifle") = [this]
		{
			if (GetState(eBossState::Pattern6))
			{
				if (GetStatePattern6(ePattern6::SweepL))
				{
					SetStatePattern6Off(ePattern6::SweepL);
					SetStatePattern6On(ePattern6::SweepDisappearL);
				}
				if (GetStatePattern6(ePattern6::SweepR))
				{
					SetStatePattern6Off(ePattern6::SweepR);
					SetStatePattern6On(ePattern6::SweepDisappearR);
				}
				mAnimator->Play(L"Headhunter_SweepRifleDisappear", false);
			}
			else
			{
				BeamOff();
				SetStatePattern5Off(ePattern5::Sweep);
				SetStatePattern5On(ePattern5::Dash);
				mHeadhunter->SetAfterImageColor(RED);
				mHeadhunter->SetAfterImageCount(100);
				mDashOrigin = GetOwnerWorldPos();
				mAnimator->Play(L"Headhunter_Dash");
			}
		};
		mAnimator->GetCompleteEvent(L"Headhunter_SweepRifleDisappear") = [this]
		{
			if (GetStatePattern6(ePattern6::SweepDisappearL))
			{
				GetOwner()->SetRight();
				GetOwner()->SetPos(SCREEN_RIGHTTOP);
				SetStatePattern6Off(ePattern6::SweepDisappearL);
				SetStatePattern6On(ePattern6::SweepStartR);
				mAnimator->Play(L"Headhunter_SweepRifleStart", false);
				PlayBeam();
			}
			if (GetStatePattern6(ePattern6::SweepDisappearR))
			{
				SetStatePattern6Off(ePattern6::SweepDisappearR);
				SetStatePattern6On(ePattern6::Dash);
				mHeadhunter->SetAfterImageColor(RED);
				mHeadhunter->SetAfterImageCount(100);
				mDashOrigin = GetOwnerWorldPos();
				mAnimator->Play(L"Headhunter_Dash");
			}
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
		///////////////////////////////////////////////////////////////

		for (UINT i = 0; i < 18; i++)
		{
			mAnimator->GetStartEvent(L"Headhunter_AimRifle" + std::to_wstring(i)) = [this]
			{
				Vector3 offset = Interpolation<Vector3>(0.f, 90.f, fabs(mBeamAngle), BEAM_OFFSET_0, BEAM_OFFSET_90);
				RepositionBeam(offset);
			};
		}	
		mAnimator->GetStartEvent(L"Headhunter_SweepRifle") = [this]
		{
			mBeam->RenderingBlockOff();
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
					PlayBeam();
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
		if (GetState(eBossState::Pattern6))
		{
			PatternEnd();
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

	void CHeadhunterScript::CreateBullet(float _Angle)
	{
		CBullet* bullet = CObjectPool::PopBullet();
		bullet->Initialize();
		Vector3 pos = GetOwnerWorldPos();
		pos.y -= 0.5f;
		bullet->SetPos(pos);

		// bullet의 진행방향으로 head를 돌린다.
		Vector3 Right = { 1.f, 0.f, 0.f };
		Vector3 dir = RotateVector(Right, _Angle);

		bullet->RotateBullet(dir, pos, _Angle);
		bullet->RotateBulletCollider(_Angle);

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
			mPattern1_ShootAnimName = GetAimRifleKey();
			mAnimator->Play(mPattern1_ShootAnimName, false);
			AimingOperate();

			float angle = GetDegreeFromTwoPointZ_0180(GetOwner()->GetWorldPos(), mPlayer->GetWorldPos());
			RotateBeam(angle - 90.f);
		}
		if (GetStatePattern1(ePattern1::Shoot))
		{
			if (mBeam->IsRenderingBlock())
			{
				mBeamElapsedTime = 0.f;
				SetStatePattern1Off(ePattern1::Shoot);
				SetStatePattern1On(ePattern1::Putback);
				mAnimator->Play(L"Headhunter_PutbackRifle", false);
			}
			else
			{
				BeamYScaling();
			}
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
			PlayBeam();
			SetStatePattern1Off(ePattern1::Aim);
			SetStatePattern1On(ePattern1::Shoot);
			mAnimator->Play(mPattern1_ShootAnimName, false);
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
		if (GetStatePattern2(ePattern2::WallKickAttack))
		{
			if (GetOwner()->IsLeft())
			{
				if (0 < mPattern2_ShootedBulletCountR)
				{
					CreateBullet(static_cast<float>(-7.5f * mPattern2_ShootedBulletCountR));
					--mPattern2_ShootedBulletCountR;
				}
			}
			else
			{
				if (100 > mPattern2_ShootedBulletCountL)
				{
					CreateBullet(static_cast<float>(-7.5f * mPattern2_ShootedBulletCountL));
					++mPattern2_ShootedBulletCountL;
				}
			}

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

		if (GetStatePattern5(ePattern5::SweepStart))
		{
			RotateBeam(0.f);
			RepositionBeam(BEAM_OFFSET_0);
			BeamYScaling();
		}
		if (GetStatePattern5(ePattern5::Sweep))
		{
			mPattern5_SweepElapsedTime += CTimeMgr::DeltaTime();
			BeamSwipeOffsetSetting();
			BeamYScaling();
		}
		if (GetStatePattern5(ePattern5::Dash))
		{
			mDashDest = SCREEN_CENTERFLOOR;
			DashOperate();
		}
	}

	void CHeadhunterScript::Pattern6()
	{
		if (!GetStatePattern6(ePattern6::VerticalLaserAppear) && !GetStatePattern6(ePattern6::VerticalLaserDisappear) && !GetStatePattern6(ePattern6::Dash))
		{
			if (6 > mPattern6_VerticalShootCount)
			{
				mBeamElapsedTime = 0.f;
				SwitchVerticalLaserLR();
				SetStatePattern6On(ePattern6::VerticalLaserAppear);
				mAnimator->Play(L"Headhunter_VerticalLaserAppear", false);
				++mPattern6_VerticalShootCount;
				PlayBeam();
				RotateBeam(90.f);
				RepositionBeam(BEAM_OFFSET_M90);
			}
			else
			{
				mBeamElapsedTime = 0.f;
				GetOwner()->SetLeft();
				GetOwner()->SetPos(SCREEN_LEFTTOP);
				mStatePattern6.reset();
				SetStatePattern6On(ePattern6::VerticalLaserAppear);
				SetStatePattern6On(ePattern6::SweepStartL);
				mAnimator->Play(L"Headhunter_SweepRifleStart", false);
				PlayBeam();
			}
		}
		else if (GetStatePattern6(ePattern6::VerticalLaserAppear))
		{
			BeamYScaling();
		}

		if (GetStatePattern6(ePattern6::SweepStartL) || GetStatePattern6(ePattern6::SweepStartR))
		{
			RotateBeam(0.f);
			RepositionBeam(BEAM_OFFSET_0);
			BeamYScaling();
		}
		if (GetStatePattern6(ePattern6::SweepL) || GetStatePattern6(ePattern6::SweepR))
		{
			mPattern5_SweepElapsedTime += CTimeMgr::DeltaTime();
			BeamSwipeOffsetSetting();
			BeamYScaling();
		}

		if (GetStatePattern6(ePattern6::Dash))
		{
			mDashDest = mPlayer->GetWorldPos();
			DashOperate();
		}

	}

	void CHeadhunterScript::SwitchVerticalLaserLR()
	{
		if (0 == mPattern6_VerticalShootCount % 2)
		{
			GetOwner()->SetLeft();
			Vector3 pos = SCREEN_LEFTTOP;
			int idx = mPattern6_VerticalShootCount / 2;
			pos.x += static_cast<float>(idx) * 1.f;
			GetOwner()->SetPos(pos);
		}
		else
		{
			GetOwner()->SetRight();
			Vector3 pos = SCREEN_RIGHTTOP;
			int idx = mPattern6_VerticalShootCount / 2;
			pos.x -= static_cast<float>(idx) * 1.f;
			GetOwner()->SetPos(pos);
		}
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
			Vector3 pos = GetOwnerPos();
			pos.y += 0.5f;
			ExplosionObject->SetPos(pos);
		}
	}

	CGameObj* CHeadhunterScript::GetOrCreateBeamObject()
	{
		if (!mBeam)
		{
			// create
			mBeam = object::Instantiate<CGameObj>(eLayerType::FX ,L"Beam");
			if (mBeam)
			{
				// intialize
				InitializeBeamComponent();
			}
		}

		return mBeam;
	}

	void CHeadhunterScript::InitializeBeamComponent()
	{
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			BeamObject->SetPos(GetOwnerWorldPos());
			BeamObject->SetScale({ 30.f, 0.5f, 1.f });
			mBeamTransform = BeamObject->GetComponent<CTransform>();

			std::shared_ptr<CTexture> BeamObjectTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = BeamObject->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BeamMat");
				if (Material)
				{
					BeamObjectTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			CCollider2D* BeamObjectCollider= BeamObject->AddComponent<CCollider2D>(eComponentType::Collider);
			if (BeamObjectCollider)
			{
				BeamObjectCollider->SetName(L"col_beam");
				BeamObjectCollider->SetType(eColliderType::Rect);
				BeamObjectCollider->SetScale(Vector2(1.f, 0.25f));
				BeamObjectCollider->Off();
				BeamObjectCollider->RenderingOff();
			}

			if (BeamObjectTexture && BeamObjectCollider)
			{
				CAnimator* BeamObjectAnimator = BeamObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (BeamObjectAnimator)
				{
					BeamObjectAnimator->Create(L"BeamReady", BeamObjectTexture, { 0.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.5f);
					BeamObjectAnimator->Create(L"BeamReady2", BeamObjectTexture, { 0.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
					BeamObjectAnimator->Create(L"BeamReady3", BeamObjectTexture, { 0.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
					BeamObjectAnimator->Create(L"BeamShoot", BeamObjectTexture, { 2048.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.5f);
					BeamObjectAnimator->Create(L"BeamShoot2", BeamObjectTexture, { 2048.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.5f);
					BeamObjectAnimator->Create(L"BeamShoot3", BeamObjectTexture, { 2048.f, 0.f }, { 2048.f, 40.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.25f);


					BeamObjectAnimator->GetCompleteEvent(L"BeamReady") = [this, BeamObjectAnimator, BeamObjectCollider]
					{
						BeamOn(0.5f, 0.0500f);
						BeamObjectAnimator->Play(L"BeamShoot", false);
					};
					BeamObjectAnimator->GetCompleteEvent(L"BeamReady2") = [this, BeamObjectAnimator, BeamObjectCollider]
					{
						BeamOn(1.8f, 0.0250f);
						BeamObjectAnimator->Play(L"BeamShoot2", false);
					};
					BeamObjectAnimator->GetCompleteEvent(L"BeamReady3") = [this, BeamObjectAnimator, BeamObjectCollider]
					{
						BeamOn(0.125f, 0.0125f);
						BeamObjectAnimator->Play(L"BeamShoot3", false);
					};

					BeamObjectAnimator->GetCompleteEvent(L"BeamShoot") = [this, BeamObjectCollider]
					{
						mBeam->RenderingBlockOn();
						BeamObjectCollider->Off();
						BeamObjectCollider->RenderingOff();
					};
				}
				else
				{
					assert(false);
				}
			}
			BeamObject->RenderingBlockOn();
		}
	}

	void CHeadhunterScript::PlayBeam()
	{ 
		mPattern5_SweepElapsedTime = 0.f;
		mBeamElapsedTime = 0.f;
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			CCollider2D* BeamObjectCollider = BeamObject->GetComponent<CCollider2D>();
			CAnimator* BeamObjectAnimator = BeamObject->GetComponent<CAnimator>();
			if (BeamObjectAnimator && BeamObjectCollider)
			{
				mBeam->RenderingBlockOff();
				if (GetState(eBossState::Pattern1))
				{
					BeamObjectAnimator->Play(L"BeamReady", false);
				}
				else if (GetState(eBossState::Pattern5))
				{
					BeamObjectAnimator->Play(L"BeamReady2", false);
				}
				else if (GetState(eBossState::Pattern6))
				{
					if (GetStatePattern6(ePattern6::SweepStartL) || GetStatePattern6(ePattern6::SweepStartR))
					{
						BeamObjectAnimator->Play(L"BeamReady2", false);
					}
					else
					{
						BeamObjectAnimator->Play(L"BeamReady3", false);
					}
				}
			}
			else
			{
				assert(false);
			}
		}
	}
	void CHeadhunterScript::RotateBeam(float _Angle)
	{
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			if (!mHeadhunter->IsLeft())
			{
				_Angle *= -1.f;
			}
			mBeamAngle = _Angle;
			BeamObject->GetComponent<CTransform>()->SetRotationZ(_Angle);
		}
	}

	void CHeadhunterScript::BeamSwipeOffsetSetting()
	{
		float angle = Interpolation<float>(0.f, 1.8f, mPattern5_SweepElapsedTime, 0.f, 180.f);
		RotateBeam(angle);
		Vector3 offset;
		if (0.f <= mBeamAngle && 90.f > mBeamAngle)
		{
			offset = Interpolation<Vector3>(0.f, 90.f, fabs(mBeamAngle), BEAM_OFFSET_0, BEAM_OFFSET_M90);
		}
		else if (90.f <= mBeamAngle && 180.f > mBeamAngle)
		{
			offset = Interpolation<Vector3>(90.f, 180.f, fabs(mBeamAngle), BEAM_OFFSET_M90, BEAM_OFFSET_180);
		}
		RepositionBeam(offset);
	}

	void CHeadhunterScript::RepositionBeam(Vector3 _XY)
	{
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			Vector3 scale = BeamObject->GetScale();
			Vector3 newPos;

			if (mHeadhunter->IsLeft())
			{
				newPos.x -= scale.x * 0.5f;
				newPos.x -= _XY.x;
			}
			else
			{
				newPos.x += scale.x * 0.5f;
				newPos.x += _XY.x;
			}
			newPos.y += _XY.y;
			newPos = RotateZ(newPos, mBeamAngle);

			BeamObject->SetPos(newPos + GetOwnerWorldPos());
		}
	}

	void CHeadhunterScript::BeamYScaling()
	{
		float scaleY = 0.f;
		mBeamElapsedTime += CTimeMgr::DeltaTime();
		CAnimator* anim = mBeam->GetComponent<CAnimator>();
		if (GetState(eBossState::Pattern1))
		{
			if (anim->IsPlaying(L"BeamReady"))
			{
				scaleY = Interpolation<float>(0.f, 0.5f, mBeamElapsedTime, 0.f, 0.5f);
				mBeamTransform->SetScaleY(scaleY);
			}
			else if (anim->IsPlaying(L"BeamShoot"))
			{
				if (0.75f <= mBeamElapsedTime)
				{
					scaleY = Interpolation<float>(0.75f, 1.f, mBeamElapsedTime, 0.5f, 0.f);
					mBeamTransform->SetScaleY(scaleY);
				}
			}
		}
		if (GetState(eBossState::Pattern5))
		{
			if (anim->IsPlaying(L"BeamReady2"))
			{
				scaleY = Interpolation<float>(0.f, 0.1f, mBeamElapsedTime, 0.f, 0.5f);
				mBeamTransform->SetScaleY(scaleY);
			}
			else if (anim->IsPlaying(L"BeamShoot2"))
			{
				if (2.f <= mBeamElapsedTime)
				{
					scaleY = Interpolation<float>(2.f, 2.1f, mBeamElapsedTime, 0.5f, 0.f);
					mBeamTransform->SetScaleY(scaleY);
				}
			}
		}
		if (GetState(eBossState::Pattern6))
		{
			if (anim->IsPlaying(L"BeamReady2"))
			{
				scaleY = Interpolation<float>(0.f, 0.2f, mBeamElapsedTime, 0.f, 0.5f);
				mBeamTransform->SetScaleY(scaleY);
			}
			else if (anim->IsPlaying(L"BeamShoot2"))
			{
				if (4.5f <= mBeamElapsedTime)
				{
					scaleY = Interpolation<float>(4.5f, 4.6f, mBeamElapsedTime, 0.5f, 0.f);
					mBeamTransform->SetScaleY(scaleY);
				}
			}
			else if (anim->IsPlaying(L"BeamReady3"))
			{
				float scaleY = Interpolation<float>(0.f, 0.1f, mBeamElapsedTime, 0.f, 0.5f);
				mBeamTransform->SetScaleY(scaleY);
			}
		}


	}

	void CHeadhunterScript::BeamOn(float _duration, float _mag)
	{
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			CCollider2D* BeamObjectCollider = BeamObject->GetComponent<CCollider2D>();
			if (BeamObjectCollider)
			{
				BeamObjectCollider->On();
				BeamObjectCollider->RenderingOn();
				ShakeParams sp = {};
				sp.duration = _duration;
				sp.magnitude = _mag;
				renderer::mainCamera->GetCamScript()->Shake(sp);
			}
		}
	}

	void CHeadhunterScript::BeamOff()
	{
		CGameObj* BeamObject = GetOrCreateBeamObject();
		if (BeamObject)
		{
			CCollider2D* BeamObjectCollider = BeamObject->GetComponent<CCollider2D>();
			if (BeamObjectCollider)
			{
				mBeam->RenderingBlockOn();
				BeamObjectCollider->Off();
				BeamObjectCollider->RenderingOff();
			}
			else
			{
				assert(false);
			}
		}
	}

}