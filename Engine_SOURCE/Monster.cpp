#include "Monster.h"
#include "RigidBody.h"
#include "MonsterScript.h"

namespace dru
{
	CMonster::CMonster()
	{
		SetLayerType(eLayerType::Monster);

		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));



		CMonsterScript* script = this->AddComponent<CMonsterScript>(eComponentType::Script);

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