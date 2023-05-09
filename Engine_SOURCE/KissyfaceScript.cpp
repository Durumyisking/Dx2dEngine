#include "KissyfaceScript.h"
#include "Kissyface.h"
#include "Axe.h"
#include "AxeScript.h"
#include "TimeMgr.h"

namespace dru
{
	CKissyfaceScript::CKissyfaceScript()
		: mKissyface(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mPattern2_RecieveWaitingTime(1.f)
		, mbNoAxe(false)
	{
	}

	CKissyfaceScript::~CKissyfaceScript()
	{
	}

	void CKissyfaceScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAnimator->GetCompleteEvent(L"kissyface_WaitingEnd") = std::bind(&CKissyfaceScript::waitingEndComplete, this);
		mAnimator->GetCompleteEvent(L"kissyface_JumpStart") = std::bind(&CKissyfaceScript::jumpStartComplete, this);
		mAnimator->GetCompleteEvent(L"kissyface_AirThrowAxe") = std::bind(&CKissyfaceScript::airThrowAxeComplete, this);
		mAnimator->GetEndEvent(L"kissyface_AirThrowEnd") = std::bind(&CKissyfaceScript::airThrowAxeEndEnd, this);
		mAnimator->GetCompleteEvent(L"kissyface_Land") = std::bind(&CKissyfaceScript::landComplete, this);

		mAnimator->GetFrameEvent(L"kissyface_ThrowAxe", 5) = std::bind(&CKissyfaceScript::throwAxeFrame5, this);
		mAnimator->GetCompleteEvent(L"kissyface_ThrowAxe") = std::bind(&CKissyfaceScript::throwAxeComplete, this);
		mAnimator->GetCompleteEvent(L"kissyface_RecieveAxe") = std::bind(&CKissyfaceScript::recieveComplete, this);

		mKissyface = dynamic_cast<CKissyface*>(GetOwner());

		CBossScript::Initialize();
	}

	void CKissyfaceScript::update()
	{
		if (!GetOwner_LiveObject()->IsRewindRePlaying())
		{
			mKissyface->GetAxeScript()->SetKissyfaceCenter(mKissyface->GetWorldPos());

			CBossScript::update();
		}
	}

	void CKissyfaceScript::fixedUpdate()
	{
		CBossScript::fixedUpdate();
	}

	void CKissyfaceScript::render()
	{
		CBossScript::render();
	}


	void CKissyfaceScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			if (GetState(eBossState::Pattern1))
			{
				mAnimator->Play(L"kissyface_Land", false);
				SetStatePattern1On(ePattern1::Land);
			}
		}
		else if (L"col_kissyFaceAxe" == _oppo->GetName())
		{
			if (mKissyface->GetAxeScript()->GetState(eState::Recieve))
			{
				SetStatePattern2On(ePattern2::Recieve);
				mAnimator->Play(L"kissyface_RecieveAxe", false);
				AxeOff();
			}
		}

		CBossScript::OnCollisionEnter(_oppo);
	}

	void CKissyfaceScript::OnCollision(CCollider2D* _oppo)
	{
	
	
		CBossScript::OnCollision(_oppo);
	}

	void CKissyfaceScript::OnCollisionExit(CCollider2D* _oppo)
	{

		CBossScript::OnCollisionExit(_oppo);
	}

	void CKissyfaceScript::Reset()
	{
		AxeOff();
		mKissyface->GetAxeScript()->Reset();
		mStatePattern1.reset();
		mStatePattern2.reset();
		mPattern2_RecieveWaitingTime = 1.f;
		GetOwner_LiveObject()->RemoveAfterImage();

		CBossScript::Reset();
	}

	void CKissyfaceScript::Pattern1()
	{
		if (!GetStatePattern1(ePattern1::Jump))
		{
			mAnimator->Play(L"kissyface_JumpStart", false);
			SetStatePattern1On(ePattern1::Jump);
			mKissyface->SetAfterImageCount(30);
		}
		if (GetStatePattern1(ePattern1::Throw) && !GetStatePattern1(ePattern1::ThrowEnd))
		{
			mRigidbody->AddForceY(50.f);
		}
	}

	void CKissyfaceScript::Pattern2()
	{
		if (!GetStatePattern2(ePattern2::Throw))
		{
			mAnimator->Play(L"kissyface_ThrowAxe", false);
			SetStatePattern2On(ePattern2::Throw);
			SetAxeDir();
		}
		if (GetStatePattern2(ePattern2::Throw))
		{
			if (mKissyface->GetAxeScript()->GetState(eState::Stuck))
			{
				mPattern2_RecieveWaitingTime -= CTimeMgr::DeltaTime();
				if (0.f >= mPattern2_RecieveWaitingTime)
				{
					mKissyface->GetAxeScript()->SetStateOff(eState::Stuck);
					mKissyface->GetAxeScript()->SetStateOn(eState::Recieve);
					mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);
					mPattern2_RecieveWaitingTime = 1.f;
				}
			}
		}


	}

	void CKissyfaceScript::Pattern3()
	{
	}

	void CKissyfaceScript::Pattern4()
	{
	}

	void CKissyfaceScript::Pattern5()
	{
	}

	void CKissyfaceScript::PatternEnd(UINT _PatternNumber)
	{
		switch (_PatternNumber)
		{
		case 1:
			mStatePattern1.reset();
			break;
		case 2:
			mStatePattern2.reset();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}

		Reset();
	}

	void CKissyfaceScript::SetAxeDir()
	{
		float playerPosX = mPlayer->GetWorldPos().x;
		float KissyPosX = GetOwnerWorldPos().x;

		if (playerPosX > KissyPosX)
		{
			mKissyface->GetAxeScript()->SetDir({ 1.f, 0.f, 0.f });
		}
		else
		{
			mKissyface->GetAxeScript()->SetDir({ -1.f, 0.f, 0.f });
		}

	}

	void CKissyfaceScript::AxeOn()
	{
		mKissyface->GetAxe()->RenderingBlockOff();
		mKissyface->GetAxe()->SetAfterImageCount(50);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->On();
		coll->RenderingOn();
		mbNoAxe = false;
	}

	void CKissyfaceScript::AxeOff()
	{
		mKissyface->GetAxe()->RenderingBlockOn();
		mKissyface->GetAxeScript()->Reset();
		mKissyface->GetAxe()->RemoveAfterImage();
		mKissyface->GetAxe()->SetAfterImageCount(0);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->Off();
		coll->RenderingOff();
		mbNoAxe = true;
	}

	void CKissyfaceScript::waitingEndComplete()
	{
		SetSingleState(eBossState::Idle);
	}

	void CKissyfaceScript::jumpStartComplete()
	{
		if (!GetStatePattern1(ePattern1::Throw))
		{
			SetStatePattern1On(ePattern1::Throw);
			mAnimator->Play(L"kissyface_AirThrowAxe", false);
			AxeOn();
			mKissyface->GetAxeScript()->SetStateOn(eState::Orbit);
			mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);

			mKissyface->GetAxe()->SetAfterImageCount(50);
		}
	}

	void CKissyfaceScript::airThrowAxeComplete()
	{		
		SetStatePattern1Off(ePattern1::Throw);
		SetStatePattern1On(ePattern1::ThrowEnd);
		mAnimator->Play(L"kissyface_AirThrowEnd");
	}

	void CKissyfaceScript::airThrowAxeEndEnd()
	{
		AxeOff();
		mKissyface->GetAxeScript()->SetStateOff(eState::Orbit);
		mKissyface->GetAxeScript()->SetStateOff(eState::Rotate);
	}

	void CKissyfaceScript::landComplete()
	{
		mKissyface->SetAfterImageCount(0);
		PatternEnd(1);
	}
	void CKissyfaceScript::throwAxeFrame5()
	{
		AxeOn();
		mKissyface->GetAxe()->SetPos(Vector3::Zero);
		mKissyface->GetAxeScript()->SetStateOn(eState::Fly);
		mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);
	}

	void CKissyfaceScript::throwAxeComplete()
	{
		mAnimator->Play(L"kissyface_ThrowAxeEnd");
		SetStatePattern2On(ePattern2::ThrowEnd);
	}

	void CKissyfaceScript::throwAxeEndEnd()
	{
	}

	void CKissyfaceScript::recieveComplete()
	{
		PatternEnd(2);
	}


}