#include "Boss.h"
#include "BossScript.h"

namespace dru
{
	CBoss::CBoss()
		: mHP(5)
	{
		SetLayerType(eLayerType::Boss);

		CRigidBody* rigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		// coll->Initialize();
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));
	}

	CBoss::~CBoss()
	{
	}

	void CBoss::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CBoss::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}

		CLiveGameObj::update();
	}

	void CBoss::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBoss::render()
	{
		CLiveGameObj::render();
	}

	void CBoss::Disable()
	{
		GetScript<CBossScript>()->Reset();
	}

}