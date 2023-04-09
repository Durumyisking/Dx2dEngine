#include "Monster.h"
#include "Object.h"
#include "TimeMgr.h"

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

		CGameObj::Initialize();
	}

	void CMonster::update()
	{
		SetRayPos();

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
	void CMonster::SetRayPos()
	{
		if (mRay)
		{

			Vector3 vPos = GetPos();
			float ScaleX = mRay->GetScale().x;
			if (IsLeft())
			{
				vPos += ScaleX / 2.f * -GetComponent<CTransform>()->Right();
			}
			else
			{
				vPos += ScaleX / 2.f * GetComponent<CTransform>()->Right();
			}
			mRay->SetPos(vPos);
		}
	}
}