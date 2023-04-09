#include "MonsterRayScript.h"
#include "GameObj.h"
#include "Monster.h"

namespace dru
{

	CMonsterRayScript::CMonsterRayScript()
		: CScript()
		, mTarget(nullptr)
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

		if (mTarget && mRayOwner)
		{
			Vector3 vPos = mRayOwner->GetPos();
			Vector3 vTargetPos = mTarget->GetPos();
			Vector3 vDir = vTargetPos - vPos;
			vDir.Normalize();
			if (mRayOwner)
			{
				mRayOwner->GetComponent<CRigidBody>()->AddForce(vDir * 50.f);


			}
		}
	}

	void CMonsterRayScript::fixedUpdate()
	{

	}

	void CMonsterRayScript::render()
	{

	}

	void CMonsterRayScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_player" == _oppo->GetName())
		{
			mTarget = _oppo->GetOwner();

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
	}
}