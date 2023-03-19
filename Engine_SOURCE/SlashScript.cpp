#include "SlashScript.h"
#include "Animator.h"
#include "GameObj.h"

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
		GetOwner()->Die();
	}
}
