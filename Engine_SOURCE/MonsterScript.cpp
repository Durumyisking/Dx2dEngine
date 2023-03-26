#include "MonsterScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"

namespace dru
{
	CMonsterScript::CMonsterScript()
		: mState{}
		, mbOnWall(false)
	{

	}

	CMonsterScript::~CMonsterScript()
	{
	}

	void CMonsterScript::Initialize()
	{
		mState[(UINT)eMonsterState::Idle] = true;

		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mTransform = GetOwner()->GetComponent<CTransform>();
	}

	void CMonsterScript::update()
	{
		mPos = mTransform->GetPosition();



		mTransform->SetPosition(mPos);
		GetOwner()->Flip();
	}

	void CMonsterScript::fixedUpdate()
	{
	}

	void CMonsterScript::render()
	{
	}

	void CMonsterScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{

			mRigidbody->SetGround();
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = true;
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			mState.reset();
			mState[(UINT)eMonsterState::Die] = true;
			 
		}
	}

	void CMonsterScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = false;
		}
	}

	void CMonsterScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

}