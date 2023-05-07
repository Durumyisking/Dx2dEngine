#include "Kissyface.h"
#include "KissyfaceScript.h"
#include "Input.h"

namespace dru
{
	CKissyface::CKissyface()
		: mAnimator(nullptr)
	{
		SetName(L"kissyface");
		SetScale(Vector3(1.75f, 1.75f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyfaceMat", Material);
		SpriteRenderer->SetMaterial(Material);

		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"kissyface_Idle", Material->GetTexture(), { 256.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Waiting", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_WaitingEnd", Material->GetTexture(), { 4608.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Walk", Material->GetTexture(), { 6272.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 10, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_DeadGround", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Attack", Material->GetTexture(), { 7296.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);

		mAnimator->Play(L"kissyface_Waiting");

		AddComponent<CKissyfaceScript>(eComponentType::Script)->Initialize();
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
		if (CInput::GetKeyDown(eKeyCode::N_9))
		{
			mAnimator->Play(L"kissyface_Waiting");
		}
		if (CInput::GetKeyDown(eKeyCode::N_8))
		{
			mAnimator->Play(L"kissyface_Walk");
		}
		if (CInput::GetKeyDown(eKeyCode::N_7))
		{
			mAnimator->Play(L"kissyface_Idle");
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

}