#include "MonsterRay.h"
#include "MonsterRayScript.h"

namespace dru
{
	CMonsterRay::CMonsterRay()
	{
		SetLayerType(eLayerType::Ray);

		CCollider2D* ray = AddComponent<CCollider2D>(eComponentType::Collider);
		ray->Initialize();
		ray->SetName(L"col_monsterray");
		ray->SetType(eColliderType::Rect);

		Vector3 defaultScale = Vector3(5.f, 1.f, 1.f);
		SetScale(defaultScale);


		CMonsterRayScript* script = AddComponent<CMonsterRayScript>(eComponentType::Script);
		//script->Initialize();
	}

	CMonsterRay::~CMonsterRay()
	{
	}

	void CMonsterRay::Initialize()
	{
		//GetComponent<CTransform>()->AddPositionX((GetScale().x / 2.f));

		CGameObj::Initialize();
	}

	void CMonsterRay::update()
	{
		CGameObj::update();
	}

	void CMonsterRay::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CMonsterRay::render()
	{
		CGameObj::render();
	}


}