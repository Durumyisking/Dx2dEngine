#include "GruntScript.h"

namespace dru
{
	CGruntScript::CGruntScript()
	{
	}
	CGruntScript::~CGruntScript()
	{
	}
	void CGruntScript::Initialize()
	{
		mAttackRadius = 1.f;

		CMonsterScript::Initialize();

		mAnimator->GetFrameEvent(GetOwner()->GetName() + L"_Attack", 4) = std::bind(&CGruntScript::attackFrame2, this);

	}
	void CGruntScript::update()
	{

		CMonsterScript::update();
	}
	void CGruntScript::fixedUpdate()
	{

		CMonsterScript::fixedUpdate();
	}
	void CGruntScript::render()
	{

		CMonsterScript::render();
	
	}
	void CGruntScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			CMonsterScript::attack();
		}
	}

	void CGruntScript::patrol()
	{
	}

	void CGruntScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}
	void CGruntScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}
	void CGruntScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}
	void CGruntScript::SetMonsterAttack()
	{
		GetOwner()->GetComponent<CRigidBody>()->SetVelocity(Vector3::Zero);
		if (mAttackTimer >= 0.5f)
		{
			SetSingleState(eMonsterState::Attack);
			attack();
		}
		else
		{
			runTrigger();
		}
	}
	void CGruntScript::attackFrame2()
	{
		makeSlash({ 7296.f, 0.f }, { 64.f, 64.f }, 4, { 64.f, 64.f });
	}
}
