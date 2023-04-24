#include "PlayerAfterImage.h"
#include "AfterImageRenderer.h"
#include "Animator.h"
#include "Player.h"

namespace dru
{
	CPlayerAfterImage::CPlayerAfterImage()
		: mPlayerFrameCaptures{}
		, mOwner(nullptr)
		, mAlpha(1.f)
		, mIndex(0)
	{
	}

	CPlayerAfterImage::~CPlayerAfterImage()
	{
	}

	void CPlayerAfterImage::Initialize()
	{
		CAfterImageRenderer* Renderer = this->AddComponent<CAfterImageRenderer>(eComponentType::AfterImageRenderer);
		// 인덱스마다 머티리얼 다르게해야함
		std::wstring matName = L"PlayerMatAfterImage_";
		std::wstring idx = std::to_wstring(mIndex);
		matName += idx;
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(matName);
	
		Renderer->SetMaterial(Material);

		Renderer->SetAfterImageOwner(this);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"AfterImage", Material->GetTexture(), { 0.f, 0.f }, { 0.f, 0.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Play(L"AfterImage");


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