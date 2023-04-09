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
		ray->SetType(eColliderType::Ray);


		SetScale(Vector3(5.f, 2.f, 1.f));

		CMonsterRayScript* script = AddComponent<CMonsterRayScript>(eComponentType::Script);
		script->Initialize();
	}

	CMonsterRay::~CMonsterRay()
	{
	}

	void CMonsterRay::Initialize()
	{
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