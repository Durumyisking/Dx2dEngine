#include "KissyHeadScript.h"
#include "GameObj.h"
#include "RigidBody.h"

namespace dru
{
	CKissyHeadScript::CKissyHeadScript()
	{
	}

	CKissyHeadScript::~CKissyHeadScript()
	{
	}

	void CKissyHeadScript::Initialize()
	{
	}

	void CKissyHeadScript::update()
	{
	}

	void CKissyHeadScript::fixedUpdate()
	{
	}

	void CKissyHeadScript::render()
	{
	}

	void CKissyHeadScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetGround();
			GetOwner()->SetFloorOn();
		}
	}

	void CKissyHeadScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CKissyHeadScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

}