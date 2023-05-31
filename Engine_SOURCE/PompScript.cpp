#include "PompScript.h"

namespace dru
{
	CPompScript::CPompScript()
	{
	}

	CPompScript::~CPompScript()
	{
	}

	void CPompScript::Initialize()
	{
		mAttackRadius = 1.f;

		CMonsterScript::Initialize();

		mAnimator->GetFrameEvent(GetOwner()->GetName() + L"_Attack", 4) = [this]
		{
			makeSlash({ 12720.f, 0.f }, { 64.f, 64.f }, 6, { 50.f, 50.f });


		};
	}

	void CPompScript::update()
	{
		CMonsterScript::update();
	}

	void CPompScript::fixedUpdate()
	{
		CMonsterScript::fixedUpdate();
	}

	void CPompScript::render()
	{
		CMonsterScript::render();
	}

	void CPompScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			CMonsterScript::attack();
		}
	}

	void CPompScript::patrol()
	{
		if (!mTarget)
		{
			if (mState[(UINT)eMonsterState::Patrol] == false)
			{
				mRigidbody->SetMaxVelocity(VELOCITY_WALK);
				SetSingleState(eMonsterState::Patrol);
			}
			{
				if (GetOwner()->IsLeft())
				{
					mRigidbody->AddForce(Vector3(-1.f, 0.f, 0.f) * 25.f);
				}
				else
				{
					mRigidbody->AddForce(Vector3(1.f, 0.f, 0.f) * 25.f);
				}
			}
		}
	}

	void CPompScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}

	void CPompScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}

	void CPompScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}

	void CPompScript::SetMonsterAttack()
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

}