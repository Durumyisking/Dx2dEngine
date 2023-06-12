#include "Script.h"
#include "Transform.h"
#include "GameObj.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"
#include "Input.h"
#include "SlashShadeScript.h"

namespace dru
{
	CScript::CScript()
		: CComponent(eComponentType::Script)
	{
	}

	CScript::~CScript()
	{
	}

	void CScript::Initialize()
	{
	}

	void CScript::update()
	{
	}

	void CScript::fixedUpdate()
	{
	}

	void CScript::render()
	{

	}
	void CScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName() && GetOwner()->GetComponent<CRigidBody>())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetVelocityY(0.f);
//			PushRect(_oppo);
		}


	}
	void CScript::OnCollision(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName() && GetOwner()->GetComponent<CRigidBody>())
		{
//			PushRect(_oppo);
		}
	}
	void CScript::CreateSlashShade(Vector3& _targetPos)
	{
		CGameObj* SlashShade = object::Instantiate<CGameObj>(eLayerType::FX, L"SlashShade");
		CSpriteRenderer* SpriteRenderer = SlashShade->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slash", L"SpriteShader");
		CResources::Insert<CMaterial>(L"SlashShadeMat", Material);
		SpriteRenderer->SetMaterial(Material);
		SlashShade->SetPos(GetOwner()->GetPos());
		SlashShade->SetScale(Vector3(0.2f, 0.0125f, 0.f));
		CSlashShadeScript* script = SlashShade->AddComponent<CSlashShadeScript>(eComponentType::Script);
		script->Initialize();
		script->SlashOperate(_targetPos);


		CCollider2D* coll = SlashShade->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_slashshade");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 1.f));
		coll->Initialize();
	}
	//void CScript::PushRect(CCollider2D* _oppo)
	//{
	//	Vector2 myscale = GetOwner()->GetComponent<CCollider2D>()->GetScale() * 100.f;
	//	Vector2 opposcale = _oppo->GetScale() * 100.f;

	//	Vector3 mypos = GetOwnerWorldPos();
	//	Vector3 oppopos = _oppo->GetOwnerWorldPos();

	//	RECT rect = {};
	//	RECT myrect = { mypos.x - myscale.x / 2.f, mypos.y - myscale.y / 2.f, mypos.x + myscale.x / 2.f, mypos.y + myscale.y / 2.f };
	//	RECT opporect = { oppopos.x - opposcale.x / 2.f, oppopos.y - opposcale.y / 2.f, oppopos.x + opposcale.x / 2.f, oppopos.y + opposcale.y / 2.f };
	//	IntersectRect(&rect, &myrect, &opporect);
	//	float bottom = static_cast<float>(rect.bottom);
	//	float top = static_cast<float>(rect.top);
	//	bottom /= 100.f;
	//	top /= 100.f;
	//	float result = 0.f;
	//	if (top > 0.f)
	//	{
	//		result = fabs(bottom - top);
	//	}
	//	else
	//	{
	//		result = fabs(bottom + top);
	//	}

	//	GetOwner()->GetComponent<CTransform>()->AddPositionY(result);

	//}
}