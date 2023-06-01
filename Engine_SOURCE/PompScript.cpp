#include "PompScript.h"
#include "TimeMgr.h"

namespace dru
{
	CPompScript::CPompScript()
		: mAnimator(nullptr)
		, mBlockTimer(0.f)
		, mbCanBlock(true)
	
	{
	}

	CPompScript::~CPompScript()
	{
	}

	void CPompScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();

		mAttackRadius = 1.f;

		CMonsterScript::Initialize();

		mAnimator->GetFrameEvent(GetOwner()->GetName() + L"_Attack", 4) = [this]
		{
			makeSlash({ 12720.f, 0.f }, { 64.f, 64.f }, 6, { 50.f, 50.f });
		};
		mAnimator->GetCompleteEvent(L"Pomp_KnockedDown") = [this]
		{
			SetSingleState(eMonsterState::Idle);
		};

	}

	void CPompScript::update()
	{
		if (1.5f > mBlockTimer)
		{
			mBlockTimer += CTimeMgr::DeltaTime();
		}
		else
		{
			mbCanBlock = true;
		}

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
		if (!mTarget && mState[(UINT)eMonsterState::Block] == false)
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
		if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!mbDead && mbCanBlock)
			{
				mBlockTimer = 0.f;
				mbCanBlock = false;
				mAnimator->Play(L"Pomp_KnockedDown", false);
				SetSingleState(eMonsterState::Block);

				return;
			}
		}
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