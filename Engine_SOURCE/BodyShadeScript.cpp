#include "BodyShadeScript.h"
#include "Animator.h"
#include "GameObj.h"

namespace dru
{
	CBodyShadeScript::CBodyShadeScript()
		: CScript() 
		, mMonster(nullptr)
		, mAnimator(nullptr	)
	{
	}

	CBodyShadeScript::~CBodyShadeScript()
	{
	}

	void CBodyShadeScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAnimator->GetCompleteEvent(L"BodySlash") = std::bind(&CBodyShadeScript::animComplete, this);
	}

	void CBodyShadeScript::update()
	{
		GetOwner()->SetPos(mMonster->GetPos());
	}

	void CBodyShadeScript::fixedUpdate()
	{
	}

	void CBodyShadeScript::render()
	{
	}

	void CBodyShadeScript::animComplete()
	{
		GetOwner()->Die();
	}

}