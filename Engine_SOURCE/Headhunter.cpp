#include "Headhunter.h"
#include "HeadhunterScript.h"

namespace dru
{
	CHeadhunter::CHeadhunter()
		: mAnimator(nullptr)
	{
		SetName(L"headhunter");
		SetScale(Vector3(1.15f, 1.15f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"headhunter", L"SpriteShader");
		CResources::Insert<CMaterial>(L"headhunterMat", Material);
		SpriteRenderer->SetMaterial(Material);

		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Headhunter_Idle", Material->GetTexture(), { 960.f, 256.f }, { 64.f, 64.f }, Vector2::Zero, 12, { 50.f, 50.f }, 0.1f);
	
		mAnimator->Play(L"Headhunter_Idle");

		AddComponent<CHeadhunterScript>(eComponentType::Script)->Initialize();

		mAfterImageCount = 0;
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