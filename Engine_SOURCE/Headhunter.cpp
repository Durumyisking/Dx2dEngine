#include "Headhunter.h"
#include "HeadhunterScript.h"
#include "Object.h"

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

		CAudioSource* audioSource = AddComponent<CAudioSource>(eComponentType::AudioSource);
		audioSource->AddClipByKey(L"appear1");
		audioSource->AddClipByKey(L"appear2");
		audioSource->AddClipByKey(L"appear3");
		audioSource->AddClipByKey(L"deadground");
		audioSource->AddClipByKey(L"gatling");
		audioSource->AddClipByKey(L"hurt1");
		audioSource->AddClipByKey(L"hurt2");
		audioSource->AddClipByKey(L"jump");
		audioSource->AddClipByKey(L"lasershot");
		audioSource->AddClipByKey(L"lasershot_swipe");
		audioSource->AddClipByKey(L"lasershot_vertical");
		audioSource->AddClipByKey(L"lockon");
		audioSource->AddClipByKey(L"vanish");
		audioSource->AddClipByKey(L"walljump1");
		audioSource->AddClipByKey(L"walljump2");
		audioSource->AddClipByKey(L"walljump3");


		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Headhunter_Idle", Material->GetTexture(), { 960.f, 256.f }, { 64.f, 64.f }, mAnimOffset, 12, { 100.f, 100.f },		0.1f);
		mAnimator->Create(L"Headhunter_TumbleAir", Material->GetTexture(), { 1152.f, 128.f }, { 64.f, 64.f }, mAnimOffset, 2, { 100.f, 100.f }, 0.1f);	
		mAnimator->Create(L"Headhunter_TumbleLand", Material->GetTexture(), { 1280.f, 128.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f },0.1f);
		mAnimator->Create(L"Headhunter_HurtAir", Material->GetTexture(), { 1600.f, 192.f }, { 64.f, 64.f }, mAnimOffset, 3, { 100.f, 100.f },	0.1f);
		mAnimator->Create(L"Headhunter_HurtLand", Material->GetTexture(), { 1792.f, 192.f }, { 64.f, 64.f }, mAnimOffset, 7, { 100.f, 100.f },	0.1f);
		mAnimator->Create(L"Headhunter_Hide", Material->GetTexture(), { 256.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f },			0.1f);

		mAnimator->Create(L"Headhunter_Dash", Material->GetTexture(), { 320.f, 64.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f },		0.1f);
		mAnimator->Create(L"Headhunter_DashEnd", Material->GetTexture(), { 384.f, 64.f }, { 64.f, 64.f }, mAnimOffset, 10, { 100.f, 100.f },	0.1f);

		// pattern1
		mAnimator->Create(L"Headhunter_TakeoutRifle", Material->GetTexture(), { 448.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 8, { 100.f, 100.f }, 0.1f);
		for (UINT i = 0; i < 18; i++)
		{
			std::wstring key = L"Headhunter_AimRifle";
			key += std::to_wstring(i);
			float LTx = 1664.f + (-64.f * i);
			mAnimator->Create(key, Material->GetTexture(), { LTx, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 0.5f);
		}
		mAnimator->Create(L"Headhunter_PutbackRifle", Material->GetTexture(), { 960.f, 384.f }, { 64.f, 64.f }, mAnimOffset, 8, { 100.f, 100.f }, 0.1f);


		// pattern2
		mAnimator->Create(L"Headhunter_BackJump", Material->GetTexture(), { 1792.f, 256.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_WallKickReady", Material->GetTexture(), { 1024.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 3, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_WallKick", Material->GetTexture(), { 1216.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 0.3f);
		mAnimator->Create(L"Headhunter_WallKickAttack", Material->GetTexture(), { 1280.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 5, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_WallKickFall", Material->GetTexture(), { 1600.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 1, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_WallKickLand", Material->GetTexture(), { 1664.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);

		// pattern3
		mAnimator->Create(L"Headhunter_TakeoutDagger", Material->GetTexture(), { 0.f, 384.f }, { 64.f, 64.f }, mAnimOffset, 5, { 100.f, 100.f }, 0.1f);

		// pattern5
		mAnimator->Create(L"Headhunter_SweepRifleStart", Material->GetTexture(), { 1472.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_SweepRifle", Material->GetTexture(), { 768.f, 448.f }, { 64.f, 64.f }, mAnimOffset, 18, { 100.f, 100.f }, 0.1f);

		// pattern6
		mAnimator->Create(L"Headhunter_VerticalLaserAppear", Material->GetTexture(), { 960.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_VerticalLaserDisappear", Material->GetTexture(), { 1728.f, 512.f }, { 64.f, 64.f }, mAnimOffset, 4, { 100.f, 100.f }, 0.1f);
		mAnimator->Create(L"Headhunter_SweepRifleDisappear", Material->GetTexture(), { 320.f, 576.f }, { 64.f, 64.f }, mAnimOffset, 3, { 100.f, 100.f }, 0.1f);

		mAnimator->Create(L"Headhunter_Dead", Material->GetTexture(), { 320.f, 256.f }, { 64.f, 64.f }, mAnimOffset, 10, { 100.f, 100.f }, 0.1f);

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
		mMaxHp = 3;
		mHp = 3;
		
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