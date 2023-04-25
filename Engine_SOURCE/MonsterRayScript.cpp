#include "MonsterRayScript.h"
#include "GameObj.h"
#include "Monster.h"
#include "Animator.h"
#include "Player.h"
#include "PlayerScript.h"
#include "SceneMain.h"

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
		eStageState stagestate = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState();
		if (stagestate == eStageState::LoadEnd)
		{

			if (mRayOwner->GetScript<CMonsterScript>()->GetTarget() && !mRayOwner->IsMonsterDead())
			{
				// 플레이어 상태 dead면
				bool state = dynamic_cast<CPlayer*>(mMonsterScript->mTarget)->GetScript<CPlayerScript>()->GetPlayerState(ePlayerState::Dead);
				if (!state)
				{
					SetMonsterAttack();
				}
				else
				{
					SetMonsterIdle();
				}
			}
		}
	}

	void CMonsterRayScript::render()
	{

	}

	void CMonsterRayScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		eStageState stagestate = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState();
		if (stagestate == eStageState::LoadEnd)
		{
			if (L"col_player" == _oppo->GetName())
			{
				mMonsterScript->SetTarget(_oppo->GetOwner_LiveObject());
				bool state = dynamic_cast<CPlayer*>(mMonsterScript->mTarget)->GetScript<CPlayerScript>()->GetPlayerState(ePlayerState::Dead);

				if (!state)
				{
					SetMonsterRun();
				}
			}
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
	void CMonsterRayScript::SetMonsterAttack()
	{
		if (mMonsterScript->GetPlayerDistance() <= 1.f)
		{
			mRayOwner->GetComponent<CRigidBody>()->SetVelocity(Vector3::Zero);
			if (mMonsterScript->mAttackTimer >= 1.f)
			{
				mMonsterScript->mState.reset();
				mMonsterScript->mState[(UINT)eMonsterState::Attack] = true;
				mMonsterScript->attack();
			}
		}
	}
	void CMonsterRayScript::SetMonsterIdle()
	{
		if (mMonsterScript->mState[(UINT)eMonsterState::Idle] == false)
		{
			mMonsterScript->mState.reset();
			mAnimator->Play(mRayOwner->GetName() + L"_Idle");
			mMonsterScript->mState[(UINT)eMonsterState::Idle] = true;
		}
	}
	void CMonsterRayScript::SetMonsterRun()
	{
		if (mMonsterScript->mState[(UINT)eMonsterState::Run] == false)
		{
			mAnimator->Play(mRayOwner->GetName() + L"_Run");
			mMonsterScript->mState.reset();
			mMonsterScript->mState[(UINT)eMonsterState::Run] = true;
		}
	}
}