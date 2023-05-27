#include "BloodScript.h"
#include "GameObj.h"
#include "RigidBody.h"

namespace dru
{
	CBloodScript::CBloodScript()
	{
	}

	CBloodScript::~CBloodScript()
	{
	}

	void CBloodScript::Initialize()
	{
	}

	void CBloodScript::update()
	{
	}

	void CBloodScript::fixedUpdate()
	{
	}

	void CBloodScript::render()
	{
	}

	void CBloodScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName() || L"col_floor2" == _oppo->GetName() || L"col_stair" == _oppo->GetName() || L"col_wall" == _oppo->GetName() || L"col_outWallside" == _oppo->GetName())
		{
			GetOwner()->RenderingBlockOn();
			GetOwner()->GetComponent<CRigidBody>()->SetGravity(0);
		}

	}

	void CBloodScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBloodScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}


}