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
				// 플레이어 살아있으면
				if (!IsPlayerDead())
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
		float dist = mMonsterScript->GetPlayerDistance();

		if (dist < mMonsterScript->GetAttackRadius())
		{
			mMonsterScript->SetMonsterAttack();
		}
	}
	void CMonsterRayScript::SetMonsterIdle()
	{
		mMonsterScript->SetSingleState(eMonsterState::Idle);
	}
	void CMonsterRayScript::SetMonsterRun()
	{
		mMonsterScript->SetSingleState(eMonsterState::Idle);
	}
	bool CMonsterRayScript::IsPlayerDead()
	{
		return dynamic_cast<CPlayer*>(mMonsterScript->mTarget)->GetScript<CPlayerScript>()->GetPlayerState(ePlayerState::Dead);
	}
}