#include "Platforms.h"

namespace dru
{
	CPlatforms::CPlatforms(ePlatformType _Type)
		: mType(_Type)
	{
		SetLayerType(eLayerType::Platforms);
		//this->AddComponent<CPlayerScript>(eComponentType::Script);

		CGameObj* Obj = dynamic_cast<CGameObj*>(this);

		CCollider2D* coll = Obj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetScale(Vector2(1.f, 1.f));


		switch (_Type)
		{
		case dru::ePlatformType::Floor:
			coll->SetName(L"col_floor");
			coll->SetType(eColliderType::Rect);
			break;
		case dru::ePlatformType::Wall:
			coll->SetName(L"col_wall");
			coll->SetType(eColliderType::Rect);
			break;
		case dru::ePlatformType::Stair:
			coll->SetName(L"col_stair");
			coll->SetType(eColliderType::Rect); // 라인으로 변경해야해
			break;
		default:
			break;
		}
	}

	CPlatforms::~CPlatforms()
	{
	}

	void CPlatforms::SetColliderScale(Vector2 _Scale)
	{
		CGameObj* Obj = dynamic_cast<CGameObj*>(this);

		CCollider2D* coll = Obj->GetComponent<CCollider2D>();

		coll->SetScale(_Scale);

	}


}