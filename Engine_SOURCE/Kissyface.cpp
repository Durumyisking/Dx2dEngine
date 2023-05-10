#include "Kissyface.h"
#include "KissyfaceScript.h"
#include "Input.h"
#include "Object.h"
#include "Axe.h"

namespace dru
{
	CKissyface::CKissyface()
		: mAnimator(nullptr)
		, mAxe(nullptr)
	{
		SetName(L"kissyface");
		SetScale(Vector3(2.5f, 2.5f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyfaceMat", Material);
		SpriteRenderer->SetMaterial(Material);

		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"kissyface_Idle", Material->GetTexture(), { 256.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Waiting", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_WaitingEnd", Material->GetTexture(), { 4608.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Walk", Material->GetTexture(), { 6272.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 10, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Block", Material->GetTexture(), { 128.f, 0.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);

		// pattern 1
		mAnimator->Create(L"kissyface_JumpStart", Material->GetTexture(), { 2304.f, 128.f }, { -128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowAxe", Material->GetTexture(), { 1152.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 4, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowEnd", Material->GetTexture(), { 1664.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 100.f);
		mAnimator->Create(L"kissyface_Land", Material->GetTexture(), { 1792.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);


		// pattern 2
		mAnimator->Create(L"kissyface_ThrowAxe", Material->GetTexture(), { 3584.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_ThrowAxeEnd", Material->GetTexture(), { 4480.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 100.f);
		mAnimator->Create(L"kissyface_RecieveAxe", Material->GetTexture(), { 0.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);

		// pattern 3
		mAnimator->Create(L"kissyface_LungeReady", Material->GetTexture(), { 4864.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 4, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Lunge", Material->GetTexture(), { 2432.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_LungeAttack", Material->GetTexture(), { 3072.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 7, { 90.f, 90.f }, 0.1f);


		mAnimator->Create(L"kissyface_DeadGround", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Attack", Material->GetTexture(), { 7296.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);

		mAnimator->Play(L"kissyface_Waiting");

		AddComponent<CKissyfaceScript>(eComponentType::Script)->Initialize();

		mAfterImageCount = 0;

		CraeteAxe();
	}

	CKissyface::~CKissyface()
	{
	}

	void CKissyface::Initialize()
	{
		CBoss::Initialize();
	}

	void CKissyface::update()
	{
		
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(true, 90);
		}

		CBoss::update();
	}

	void CKissyface::fixedUpdate()
	{
		CBoss::fixedUpdate();
	}

	void CKissyface::render()
	{
		CBoss::render();
	}

	void CKissyface::CraeteAxe()
	{
		mAxe = object::Instantiate<CAxe>(eLayerType::Bullet, this, L"Axe");		
		mAxe->SetKissyface(this);
	}

}