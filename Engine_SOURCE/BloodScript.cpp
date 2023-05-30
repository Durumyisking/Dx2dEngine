#include "BloodScript.h"
#include "GameObj.h"
#include "RigidBody.h"
#include "Object.h"
#include "SmallBlood.h"

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
		if (L"col_floor" == _oppo->GetName() || L"col_wall" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetMaxVelocity(Vector3::Zero);

			CSmallBlood* smallBlood = object::Instantiate<CSmallBlood>(eLayerType::BackGround,  L"smallBlood");
			Vector3 pos = GetOwnerWorldPos();

			if (L"col_floor" == _oppo->GetName())
			{
				pos.y -= 0.125f;
			}
			if (L"col_wall" == _oppo->GetName())
			{
				Vector3 oppoPos = _oppo->GetOwnerWorldPos();
				if (pos.x < oppoPos.x)
				{
					pos.x += 0.125f;
				}
				else
				{
					pos.x -= 0.125f;
				}
			}


			smallBlood->SetPos(pos);
			smallBlood->SetScale({ 0.025f, 0.025f, 0.f });
			smallBlood->Initialize();

		}

	}

	void CBloodScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBloodScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}


}