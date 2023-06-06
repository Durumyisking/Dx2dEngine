#include "KissyHead.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "RigidBody.h"
#include "KissyHeadScript.h"

namespace dru
{
	CKissyHead::CKissyHead()
	{
		SetName(L"kissyHead");
		SetScale(Vector3(2.5f, 2.5f, 1.f));

	}

	CKissyHead::~CKissyHead()
	{
	}

	void CKissyHead::Initialize()
	{
		CSpriteRenderer* spr = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyfaceMat2", Material);
		spr->SetMaterial(Material);

		CAnimator* anim = AddComponent<CAnimator>(eComponentType::Animator);
		anim->Create(L"kissyhead", Material->GetTexture(), { 4608.f, 0.f }, { 128.f, 128.f }, Vector2::Zero, 19, { 90.f, 90.f }, 0.1f);
		anim->Play(L"kissyhead", false);

		CRigidBody* rigid = AddComponent<CRigidBody>(eComponentType::RigidBody);
		rigid->SetMaxVelocity({ 10.f, 10.f, 0.f });

		int rand = GetRandomNumber(2, 0);

		if (1 == rand)
		{
			rigid->SetVelocity({ 10.f, 10.f, 0.f });
		}
		else
		{
			rigid->SetVelocity({ -10.f, 10.f, 0.f });
		}

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		// coll->Initialize();
		coll->SetName(L"col_kissyHead");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.1f, 0.1f));

		AddComponent<CKissyHeadScript>(eComponentType::Script);
	}

	void CKissyHead::update()
	{
	}

	void CKissyHead::fixedUpdate()
	{
	}

	void CKissyHead::render()
	{
	}

}