#include "Floor.h"

namespace dru
{
	CFloor::CFloor()
	{
		SetLayerType(eLayerType::Platforms);
		//this->AddComponent<CPlayerScript>(eComponentType::Script);

		CGameObj* Obj = dynamic_cast<CGameObj*>(this);

		CCollider2D* coll = Obj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_floor");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 1.f));

	}

	CFloor::~CFloor()
	{
	}

	void CFloor::Initialize()
	{
		CGameObj::Initialize();
	}

	void CFloor::update()
	{
		CGameObj::update();
	}

	void CFloor::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CFloor::render()
	{
		CGameObj::render();
	}

	void CFloor::SetColliderScale(Vector2 _Scale)
	{
		CGameObj* Obj = dynamic_cast<CGameObj*>(this);

		CCollider2D* coll = Obj->GetComponent<CCollider2D>();

		coll->SetScale(_Scale);
	}

}