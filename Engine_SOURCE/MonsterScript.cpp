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
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
		, mHitDir(Vector3::Zero)
		, mbOnWall(false)
		, mbDead(false)
		, mHitTimer(0.f)
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
		mMoveDir = mRigidbody->GetVelocity();
		mMoveDir.Normalize();


		if (mbDead)
		{
			if (mState[(UINT)eMonsterState::DieGround] == false)
			{
				if (mMoveDir.y > 0.f)
				{
					mState[(UINT)eMonsterState::DieAirUp] = true;
					mAnimator->Play(L"Grunt_DeadAirUp");
				}
				else if (mMoveDir.y < 0.f)
				{
					mState[(UINT)eMonsterState::DieAirDown] = true;
					mAnimator->Play(L"Grunt_DeadAirDown");
				}

				mHitTimer += CTimeMgr::DeltaTime();

				if (mHitTimer <= 1.f)
				{
					mRigidbody->AddForce({mHitDir.x * 30.f, mHitDir.y * 30.f, 0.f});
				}
			}
		}

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
			mRigidbody->SetMaxVelocity({ 5.f, 0.f, vel.z });
			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });

			if (mbDead)
			{
				mState[(UINT)eMonsterState::DieGround] = true;
				mAnimator->Play(L"Grunt_DeadGround", false);
			}

		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = true;
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			mState.reset();

			Vector3 playerPos = _oppo->GetOwner()->GetPos();
			Vector3 monsterPos = GetOwner()->GetPos();

			mHitDir = playerPos - monsterPos;
			mHitDir.Normalize();

			mRigidbody->SetMaxVelocity({ 10.f, 10.f, 0.f });

			mbDead = true;
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