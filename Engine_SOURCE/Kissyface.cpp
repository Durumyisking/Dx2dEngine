#include "Kissyface.h"

namespace dru
{
	CKissyface::CKissyface()
	{
		SetName(L"Kissyface");
		SetScale(Vector3(1.15f, 1.15f, 1.f));
		CSpriteRenderer* SpriteRenderer = this->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyfaceMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Grunt_Idle", Material->GetTexture(), { 4480.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_Patrol", Material->GetTexture(), { 6656.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_Run", Material->GetTexture(), { 6016.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_Attack", Material->GetTexture(), { 0.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_DeadAirUp", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_DeadAirDown", Material->GetTexture(), { 3392.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Grunt_DeadGround", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 18, { 50.f, 50.f }, 0.1f);

		mAnimator->Play(L"Grunt_Idle");

//		this->AddComponent<CGruntScript>(eComponentType::Script)->Initialize();
	}

	CKissyface::~CKissyface()
	{
	}

	void CKissyface::Initialize()
	{
	}

	void CKissyface::update()
	{
	}

	void CKissyface::fixedUpdate()
	{
	}

	void CKissyface::render()
	{
	}


}