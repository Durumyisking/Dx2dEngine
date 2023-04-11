#include "Script.h"
#include "Transform.h"
#include "GameObj.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"
#include "Input.h"
#include "SlashShadeScript.h"

namespace dru
{
	CScript::CScript()
		: CComponent(eComponentType::Script)
	{
	}

	CScript::~CScript()
	{
	}

	void CScript::Initialize()
	{
	}

	void CScript::update()
	{
	}

	void CScript::fixedUpdate()
	{
	}

	void CScript::render()
	{

	}
	void CScript::CreateSlashShade()
	{
		CGameObj* SlashShade = object::Instantiate<CGameObj>(eLayerType::FX, L"SlashShade");
		CSpriteRenderer* SpriteRenderer = SlashShade->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slash", L"SpriteShader");
		CResources::Insert<CMaterial>(L"SlashShadeMat", Material);
		SpriteRenderer->SetMaterial(Material);
		SlashShade->SetPos(GetOwner()->GetPos());
		SlashShade->SetScale(Vector3(0.2f, 0.0125f, 0.f));
		SlashShade->AddComponent<CSlashShadeScript>(eComponentType::Script)->Initialize();

		CCollider2D* coll = SlashShade->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_slashshade");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 1.f));
		coll->Initialize();
	}
}