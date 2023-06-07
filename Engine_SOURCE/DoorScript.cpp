#include "DoorScript.h"
#include "Animator.h"
#include "LiveGameObj.h"

namespace dru
{
	CDoorScript::CDoorScript()
		: mAnimator(nullptr)
		, mCollider(nullptr)
		, mbOpen(false)
	{
	}

	CDoorScript::~CDoorScript()
	{
	}

	void CDoorScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mCollider = GetOwner()->GetComponent<CCollider2D>();

		mAnimator->GetCompleteEvent(L"DoorOpen") = [this]
		{
			mAnimator->Play(L"DoorOpened", false);
		};
	}

	void CDoorScript::update()
	{
	}

	void CDoorScript::fixedUpdate()
	{
	}

	void CDoorScript::render()
	{
	}

	void CDoorScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!mbOpen)
			{
				mAnimator->Play(L"DoorOpen", false);
				mbOpen = true;

			}
		}
	}

	void CDoorScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CDoorScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

	void CDoorScript::Reset()
	{
		mAnimator->Play(L"DoorClosed", false);
		mbOpen = false;
	}


}