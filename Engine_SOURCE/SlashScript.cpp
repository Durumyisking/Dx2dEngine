#include "SlashScript.h"
#include "Animator.h"
#include "GameObj.h"
#include "TimeMgr.h"
#include "Input.h"

namespace dru
{
	CSlashScript::CSlashScript()
	{
	}
	CSlashScript::~CSlashScript()
	{
	}
	void CSlashScript::Initialize()
	{
		CAnimator* mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAnimator->GetCompleteEvent(GetOwner()->GetName() + L"Anim") = std::bind(&CSlashScript::slashEnd, this);

	}
	void CSlashScript::update()
	{
		Vector3 pos = GetOwner()->GetPos();
		if (CInput::GetKeyState(eKeyCode::NUM_7) == eKeyState::DOWN)
		{
			CTransform* tr = GetOwner()->GetComponent<CTransform>();
			pos -= 10.f * tr->Up() * CTimeMgr::DeltaTime();

		}

		GetOwner()->SetPos(pos);
	
	}
	void CSlashScript::fixedUpdate()
	{
	}
	void CSlashScript::render()
	{
	}
	void CSlashScript::OnCollisionEnter(CCollider2D* _oppo)
	{
	}
	void CSlashScript::OnCollision(CCollider2D* _oppo)
	{
	}
	void CSlashScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}
	void CSlashScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}
	void CSlashScript::OnTrigger(CCollider2D* _oppo)
	{
	}
	void CSlashScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}
	void CSlashScript::slashEnd()
	{
		//GetOwner()->Die();
	}
}
