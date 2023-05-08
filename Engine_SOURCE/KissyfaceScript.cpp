#include "KissyfaceScript.h"
#include "Kissyface.h"
#include "Axe.h"

namespace dru
{
	CKissyfaceScript::CKissyfaceScript()
		: mKissyface(nullptr)
		, mStatePattern1{}
		, mPattern1_AirTime(0.f)
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

		mKissyface = dynamic_cast<CKissyface*>(GetOwner());

		CBossScript::Initialize();
	}

	void CKissyfaceScript::update()
	{
		mKissyface->GetAxe()->SetKissyfaceCenter(mKissyface->GetWorldPos());

		CBossScript::update();
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
				mStatePattern1.reset();
				SetStatePattern1On(ePattern1::Land);
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
		mKissyface->GetAxe()->Reset();
		mStatePattern1.reset();
		GetOwner_LiveObject()->RemoveAfterImage();

		CBossScript::Reset();
	}

	void CKissyfaceScript::Pattern1()
	{
		if (!GetStatePattern1(ePattern1::Jump))
		{
			mAnimator->Play(L"kissyface_JumpStart", false);
			mStatePattern1 = true;
			mKissyface->SetAfterImageCount(30);
		}
		if (GetStatePattern1(ePattern1::Throw) && !GetStatePattern1(ePattern1::ThrowEnd))
		{
			mRigidbody->AddForceY(50.f);
		}
		if ((GetStatePattern1(ePattern1::Throw) || GetStatePattern1(ePattern1::ThrowEnd)))
		{
			mKissyface->GetAxe()->Spin();
		}
	}

	void CKissyfaceScript::Pattern2()
	{
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

	}

	void CKissyfaceScript::AxeOn()
	{
		mKissyface->GetAxe()->RenderingBlockOff();
		mKissyface->GetAxe()->SetAfterImageCount(50);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->On();
		coll->RenderingOn();
	}

	void CKissyfaceScript::AxeOff()
	{
		mKissyface->GetAxe()->RenderingBlockOn();
		mKissyface->GetAxe()->Reset();
		mKissyface->GetAxe()->RemoveAfterImage();
		mKissyface->GetAxe()->SetAfterImageCount(0);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->Off();
		coll->RenderingOff();
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
	}

	void CKissyfaceScript::landComplete()
	{
		mKissyface->SetAfterImageCount(0);
		PatternEnd(1);
	}


}