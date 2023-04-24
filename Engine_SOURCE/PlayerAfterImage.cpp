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


		CResources::Insert<CMaterial>(L"PlayerMatAfterImage", Material);
		Renderer->SetMaterial(Material);

		int randvalue = GetRandomNumber(1, 0);
		if (0 == randvalue)
		{
			Renderer->ChangeColor(Vector4(0.f, 1.f, 1.f, 0.05f));
		}
		else if(1 == randvalue)
		{
			Renderer->ChangeColor(Vector4(1.f, 0.f, 1.f, 0.05f));
		}
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