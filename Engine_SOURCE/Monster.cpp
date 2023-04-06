#include "Monster.h"
#include "Object.h"

namespace dru
{
	CMonster::CMonster()
		: mRay(nullptr)
	{
		SetLayerType(eLayerType::Monster);

		CRigidBody* rigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));

	}


	CMonster::~CMonster()
	{
	}

	void CMonster::Initialize()
	{
		mRay = object::Instantiate<CMonsterRay>(eLayerType::Ray, this, L"MonsterRay");

		Vector3 vPos = GetPos();
		vPos += 1.75f * mRay->GetComponent<CTransform>()->Right();
		vPos -= 0.5f * mRay->GetComponent<CTransform>()->Up();

		mRay->SetPos(vPos);

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