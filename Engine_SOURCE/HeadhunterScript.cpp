#include "HeadhunterScript.h"
#include "Headhunter.h"
#include "TimeMgr.h"

namespace dru
{
	CHeadhunterScript::CHeadhunterScript()
		: mHeadhunter(nullptr) 
		, mAudioSource(nullptr)
		, mAttackCollider(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mStatePattern3{}
		, mDodgeTimer(0.f)
		, mDodgeRadius(2.5f)
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

		AddAnimationCallBack();
		AddAnimationCallBack_Lamda();

		mHeadhunter = dynamic_cast<CHeadhunter*>(GetOwner());

		CBossScript::Initialize();
	}

	void CHeadhunterScript::update()
	{
		if (!GetOwner_LiveObject()->IsRewindRePlaying())
		{
			DodgeStart();

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
		mAnimator->GetCompleteEvent(L"Headhunter_Tumble") = [this]
		{
			SetSingleState(eBossState::Idle);
		};

		mAnimator->GetCompleteEvent(L"Headhunter_TakeoutRifle") = [this]
		{
			SetStatePattern1Off(ePattern1::Takeout);
			SetStatePattern1On(ePattern1::Aim);
		};

		for (int i = 0; i < 18; i++)
		{
			std::wstring key = L"Headhunter_AimRifle";
			key += std::to_wstring(i);
			mAnimator->GetEndEvent(key) = [this]
			{
				SetStatePattern1Off(ePattern1::Aim);
				SetStatePattern1On(ePattern1::Shoot);
				mbBlockFlipWhilePattern = true;
			};
		}
		mAnimator->GetCompleteEvent(L"Headhunter_PutbackRifle") = [this]
		{
			PatternEnd();
		};
	}

	void CHeadhunterScript::DodgeStart()
	{
		if (mDodgeTimer < 5.f)
		{
			mDodgeTimer += CTimeMgr::DeltaTime();
		}
		else
		{
			if (!Patterning())
			{
				if (mDodgeRadius > GetDistanceOfPlayer())
				{
					SetSingleState(eBossState::Dodge);
					mAnimator->Play(L"Headhunter_Tumble");
				}
			}
		}
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

	void CHeadhunterScript::Pattern2()
	{
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