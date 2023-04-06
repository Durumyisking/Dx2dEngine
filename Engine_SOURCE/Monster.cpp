#include "Monster.h"
#include "Object.h"

namespace dru
{
	CMonster::CMonster()
		: mRay(nullptr)
	{
		SetLayerType(eLayerType::Monster);

		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));

		mRay = object::Instantiate<CMonsterRay>(eLayerType::Ray, this ,L"MonsterRay");
		//Vector3 vPos = GetPos();
		//vPos += 2.5 * mRay->GetComponent<CTransform>()->Right();
		//mRay->SetPos(vPos);
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