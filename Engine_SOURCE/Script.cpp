#include "Script.h"
#include "Transform.h"
#include "GameObj.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"

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
	void CScript::MakeSlash(const std::wstring& _TextureName, UINT _AnimSize, Vector2 _Ratio)
	{
		CGameObj* SlashObj = object::Instantiate<CGameObj>(eLayerType::FX, GetOwner()->GetName() + L"_Slash");

		//CCollider2D* coll = SlashObj->AddComponent<CCollider2D>(eComponentType::Collider);
		//coll->SetName(L"col_" + SlashObj->GetName());
		//coll->SetType(eColliderType::Rect);
		//coll->SetScale(Vector2(0.3f, 0.3f));

		CSpriteRenderer* SpriteRenderer = SlashObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(_TextureName, L"SpriteShader");
		CResources::Insert<CMaterial>(GetOwner()->GetName() + L"SlashMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = SlashObj->AddComponent<CAnimator>(eComponentType::Animator);
		std::wstring animname = GetOwner()->GetName() + L"_SlashAnim";
		mAnimator->Create(animname, Material->GetTexture(), {0.f, 0.f}, {100.f, 100.f}, Vector2::Zero, _AnimSize, _Ratio, 0.1f);
		mAnimator->Play(animname, false);

		SlashObj->AddComponent<CSlashScript>(eComponentType::Script)->Initialize();

	}
}