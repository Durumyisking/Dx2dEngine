#include "PlayerAfterImage.h"
#include "AfterImageRenderer.h"
#include "Animator.h"

namespace dru
{
	CPlayerAfterImage::CPlayerAfterImage()
		: mPlayerFrameCaptures{}
		, mOwner(nullptr)
	{
		CAfterImageRenderer* Renderer = this->AddComponent<CAfterImageRenderer>(eComponentType::AfterImageRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");


		CResources::Insert<CMaterial>(L"PlayerMat", Material);

		Renderer->SetMaterial(Material);
		Renderer->SetAfterImageOwner(this);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"AfterImage", Material->GetTexture(), { 0.f, 0.f }, { 0.f, 0.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Play(L"AfterImage");
	}

	CPlayerAfterImage::~CPlayerAfterImage()
	{
	}

	void CPlayerAfterImage::Initialize()
	{
		CGameObj::Initialize();
	}

	void CPlayerAfterImage::update()
	{
		SetPos(mPlayerFrameCaptures.Position);

		CGameObj::update();
	}

	void CPlayerAfterImage::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CPlayerAfterImage::render()
	{
		CGameObj::render();
	}

}