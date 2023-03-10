#include "Monster.h"
#include "RigidBody.h"


namespace dru
{
	CMonster::CMonster()
	{
		SetLayerType(eLayerType::Monster);

		CGameObj* monsterObj = dynamic_cast<CGameObj*>(this);

		CRigidBody* rigidbody = monsterObj->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = monsterObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(2.f, 2.f));


	}


	CMonster::~CMonster()
	{
	}

	void CMonster::Initialize()
	{
		CGameObj::Initialize();
	}

	void CMonster::update()
	{
		CGameObj::update();
	}

	void CMonster::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CMonster::render()
	{
		CGameObj::render();
	}
}