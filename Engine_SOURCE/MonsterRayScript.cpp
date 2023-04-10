#include "MonsterRayScript.h"
#include "GameObj.h"
#include "Monster.h"
#include "Animator.h"

namespace dru
{

	CMonsterRayScript::CMonsterRayScript()
		: CScript()
		, mRayOwner(nullptr)
		, mAnimator(nullptr)
		, mRigidBody(nullptr)
		, mMonsterScript(nullptr)
	{

	}

	CMonsterRayScript::~CMonsterRayScript()
	{

	}

	void CMonsterRayScript::Initialize()
	{
	}

	void CMonsterRayScript::update()
	{

	}

	void CMonsterRayScript::fixedUpdate()
	{
		if (mRayOwner->GetScript<CMonsterScript>()->GetTarget())
		{
			Vector3 playerPos = mMonsterScript->mTarget->GetPos();
			Vector3 monsterPos = mRayOwner->GetPos();
			float dist = (playerPos - monsterPos).Length();
			if (dist <= 1.5f)
			{
				if (mMonsterScript->mAttackTimer >= 1.f)
				{
					mMonsterScript->mState.reset();
					mMonsterScript->mState[(UINT)eMonsterState::Attack] = true;
					mMonsterScript->attack();
				}
			}	
			else
			{
				if (mMonsterScript->mState[(UINT)eMonsterState::Run] == false)
				{
					mAnimator->Play(mRayOwner->GetName() + L"_Run");
					mMonsterScript->mState.reset();
					mMonsterScript->mState[(UINT)eMonsterState::Run] = true;
				}
			}
		}
	}

	void CMonsterRayScript::render()
	{

	}

	void CMonsterRayScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_player" == _oppo->GetName())
		{
			mMonsterScript->SetTarget(_oppo->GetOwner());
			mAnimator->Play(mRayOwner->GetName() + L"_Run");
			mMonsterScript->mState.reset();
			mMonsterScript->mState[(UINT)eMonsterState::Run] = true;

		}
	}

	void CMonsterRayScript::OnCollision(CCollider2D* _oppo)
	{

	}

	void CMonsterRayScript::OnCollisionExit(CCollider2D* _oppo)
	{

	}
	void CMonsterRayScript::SetMonster(CMonster* _monster)
	{
		mRayOwner = _monster;

		mAnimator = mRayOwner->GetComponent<CAnimator>();
		mRigidBody = mRayOwner->GetComponent<CRigidBody>();
		mMonsterScript = mRayOwner->GetScript<CMonsterScript>();
	}
}