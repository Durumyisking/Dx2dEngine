#include "Script.h"
#include "Transform.h"
#include "GameObj.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"
#include "Input.h"

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
	void CScript::MakeSlash(const std::wstring& _TextureName, Vector3 _PlayerPos, UINT _AnimSize, Vector2 _Ratio)
	{
		CGameObj* SlashObj = object::Instantiate<CGameObj>(eLayerType::FX, GetOwner()->GetName() + L"_Slash");

		CCollider2D* coll = SlashObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_" + SlashObj->GetName());
		coll->Initialize();
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 0.15f));


		Vector3 MousePos = CInput::GetMousePosition();
		MousePos /= 100.f;

		SlashObj->SetScale({ 2.f, 2.5f, 1.f });
		SlashObj->SetPos(_PlayerPos);

		if (MousePos.x < GetOwner()->GetPos().x)
			GetOwner()->SetLeft();
		else
			GetOwner()->SetRight();

		GetOwner()->Flip();


		Vector3 rotation = SlashObj->GetRotation();
		rotation.z = atan2(MousePos.y - SlashObj->GetPos().y, MousePos.x - SlashObj->GetPos().x);
		SlashObj->SetRotation(rotation);


		CSpriteRenderer* SpriteRenderer = SlashObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(_TextureName, L"SpriteShader");
		CResources::Insert<CMaterial>(GetOwner()->GetName() + L"SlashMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = SlashObj->AddComponent<CAnimator>(eComponentType::Animator);
		std::wstring animname = GetOwner()->GetName() + L"_SlashAnim";
		mAnimator->Create(animname, Material->GetTexture(), {0.f, 0.f}, {100.f, 100.f}, Vector2::Zero, _AnimSize, _Ratio, 0.025f);
		mAnimator->Play(animname, false);

		SlashObj->AddComponent<CSlashScript>(eComponentType::Script)->Initialize();


	}
}