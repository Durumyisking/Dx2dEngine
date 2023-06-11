#include "Headhunter.h"
#include "HeadhunterScript.h"

namespace dru
{
	CHeadhunter::CHeadhunter()
		: mAnimator(nullptr)
		, mAnimOffset(Vector2(0.f, 9.f))
	{
		SetName(L"headhunter");
		SetScale(Vector3(2.25f, 2.25f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"headhunter", L"SpriteShader");
		CResources::Insert<CMaterial>(L"headhunterMat", Material);
		SpriteRenderer->SetMaterial(Material);

		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Headhunter_Idle", Material->GetTexture(), { 960.f, 256.f }, { 64.f, 64.f }, mAnimOffset, 12, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_TumbleAir", Material->GetTexture(), { 1152.f, 128.f }, { 64.f, 64.f }, mAnimOffset, 2, { 100.f, 100.f }, 0.1f);	
		mAnimator->Create(L"Headhunter_TumbleLand", Material->GetTexture(), { 1280.f, 128.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_HurtAir", Material->GetTexture(), { 1600.f, 192.f }, { 64.f, 64.f }, mAnimOffset, 3, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_HurtLand", Material->GetTexture(), { 1792.f, 192.f }, { 64.f, 64.f }, mAnimOffset, 7, { 100.f, 100.f }, 0.1f);

		mAnimator->Create(L"Headhunter_Dash", Material->GetTexture(), { 320.f, 64.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_DashLand", Material->GetTexture(), { 384.f, 64.f }, { 64.f, 64.f }, mAnimOffset, 10, { 100.f, 100.f }, 0.1f);

		// pattern1
		mAnimator->Create(L"Headhunter_TakeoutRifle", Material->GetTexture(), { 448.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 8, { 100.f, 100.f }, 0.1f);

		// pattern2
		mAnimator->Create(L"Headhunter_SweepRifleStart", Material->GetTexture(), { 1472.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_SweepRifle", Material->GetTexture(), { 768.f, 448.f }, { 64.f, 64.f }, mAnimOffset, 18, { 100.f, 100.f }, 0.1f);


		for (UINT i = 0; i < 18; i++)
		{
			std::wstring key = L"Headhunter_AimRifle";
			key += std::to_wstring(i);
			float LTx = 1664.f + (-64.f * i);
			mAnimator->Create(key, Material->GetTexture(), { LTx, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 1.f);
		}
		mAnimator->Create(L"Headhunter_PutbackRifle", Material->GetTexture(), { 960.f, 384.f }, { 64.f, 64.f }, mAnimOffset, 8, { 100.f, 100.f }, 0.1f);


		mAnimator->Play(L"Headhunter_Idle");

		AddComponent<CHeadhunterScript>(eComponentType::Script)->Initialize();

		mAfterImageCount = 0;

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.15f, 0.34f));
	}

	CHeadhunter::~CHeadhunter()
	{
	}

	void CHeadhunter::Initialize()
	{
		mMaxHp = 5;
		mHp = 5;
		CBoss::Initialize();
	}

	void CHeadhunter::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(true, 100.f);
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