#include "Kissyface.h"
#include "KissyfaceScript.h"
#include "Input.h"
#include "Object.h"

namespace dru
{
	CKissyface::CKissyface()
		: mAnimator(nullptr)
		, mAxe(nullptr)
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

		// pattern 1
		mAnimator->Create(L"kissyface_JumpStart", Material->GetTexture(), { 2304.f, 128.f }, { -128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowAxe", Material->GetTexture(), { 1152.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 4, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowEnd", Material->GetTexture(), { 1664.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Land", Material->GetTexture(), { 1792.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);



		mAnimator->Create(L"kissyface_DeadGround", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Attack", Material->GetTexture(), { 7296.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);

		mAnimator->Play(L"kissyface_Waiting");

		AddComponent<CKissyfaceScript>(eComponentType::Script)->Initialize();

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
		if (CInput::GetKeyDown(eKeyCode::N_9))
		{
			mAnimator->Play(L"kissyface_JumpStart");
		}
		if (CInput::GetKeyDown(eKeyCode::N_8))
		{
			mAnimator->Play(L"kissyface_Land");
		}
		if (CInput::GetKeyDown(eKeyCode::N_7))
		{
			mAnimator->Play(L"kissyface_AirThrowAxe");
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
		mAxe = object::Instantiate<CLiveGameObj>(eLayerType::Bullet, this, L"Axe");
		CSpriteRenderer* SpriteRenderer = mAxe->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		mAxe->SetScale({ 0.125f, 0.125f, 1.f });
		mAxe->SetPosAbs({ 0.5f, 0.f, 0.f});

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyface_axeMat", Material);
		SpriteRenderer->SetMaterial(Material);

//		mAxe->RenderingBlockOn();	

		CCollider2D* coll = mAxe->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_kissyFaceAxe");
		coll->SetType(eColliderType::Rect);
//		coll->SetScale(Vector2(0.4f, 0.6f));

//		coll->Off();
	}

}