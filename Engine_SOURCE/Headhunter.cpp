#include "Headhunter.h"
#include "HeadhunterScript.h"

namespace dru
{
	CHeadhunter::CHeadhunter()
		: mAnimator(nullptr)
		, mAnimOffset(Vector2(0.f, 13.485f))
	{
		SetName(L"headhunter");
		SetScale(Vector3(2.25f, 2.25f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"headhunter", L"SpriteShader");
		CResources::Insert<CMaterial>(L"headhunterMat", Material);
		SpriteRenderer->SetMaterial(Material);

		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Headhunter_Idle", Material->GetTexture(), { 960.f, 256.f }, { 64.f, 64.f }, mAnimOffset, 12, { 100.f, 100.f }, 0.1f);
	
		mAnimator->Play(L"Headhunter_Idle");

		AddComponent<CHeadhunterScript>(eComponentType::Script)->Initialize();

		mAfterImageCount = 0;

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.15f, 0.4f));
	}

	CHeadhunter::~CHeadhunter()
	{
	}

	void CHeadhunter::Initialize()
	{
		mMaxHp = 1;
		mHp = 1;
		CBoss::Initialize();
	}

	void CHeadhunter::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(true, 90);
		}
		CBoss::update();
	}

	void CHeadhunter::fixedUpdate()
	{
		CBoss::fixedUpdate();
	}

	void CHeadhunter::render()
	{
		CBoss::render();
	}

	void CHeadhunter::rewindRender()
	{
		CBoss::rewindRender();
	}

}