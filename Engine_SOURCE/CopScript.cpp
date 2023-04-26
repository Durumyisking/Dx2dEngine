#include "CopScript.h"

namespace dru
{
	CCopScript::CCopScript()
	{
	}
	CCopScript::~CCopScript()
	{
	}
	void CCopScript::Initialize()
	{
		mAttackRadius = 5.f;
		CMonsterScript::Initialize();
	}
	void CCopScript::update()
	{
		CMonsterScript::update();
	}
	void CCopScript::fixedUpdate()
	{
		CMonsterScript::fixedUpdate();
	}
	void CCopScript::render()
	{
		CMonsterScript::render();
	}
	void CCopScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			Vector3 pos = GetOwnerPos();
			pos.y += 1.f;
			if (GetOwner()->IsLeft())
			{
				pos.x -= 0.5f;
			}
			else
			{
				pos.x += 0.1f;
			}

			CreateBullet(pos);

			CMonsterScript::attack();
		}
	}
	void CCopScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}
	void CCopScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}
	void CCopScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}
	void CCopScript::SetMonsterAttack()
	{
		GetOwner()->GetComponent<CRigidBody>()->SetVelocity(Vector3::Zero);
		if (mAttackTimer >= 1.f)
		{
			SetSingleState(eMonsterState::Attack);
			attack();
		}
		else
		{
			runTrigger();
		}
	}
}
