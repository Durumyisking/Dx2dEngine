#include "PlayerAfterImage.h"
#include "AfterImageRenderer.h"
#include "Animator.h"
#include "Player.h"

namespace dru
{
	CAfterImage::CAfterImage()
		: mFrameCaptures{}
		, mOwner(nullptr)
		, mIndex(0)
		, mAnimSize(50.f)
	{
	}

	CAfterImage::~CAfterImage()
	{
	}

	void CAfterImage::Initialize()
	{
		CAfterImageRenderer* Renderer = this->AddComponent<CAfterImageRenderer>(eComponentType::Renderer);
		// 인덱스마다 머티리얼 다르게해야함
		std::wstring OwnerName = mOwner->GetName();
		std::wstring matName = L"MatAfterImage_";
		std::wstring idx = std::to_wstring(mIndex);
		matName += idx;
		OwnerName += matName;
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(OwnerName);
	
		Renderer->SetMaterial(Material);

		Renderer->SetAfterImageOwner(this);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"AfterImage", Material->GetTexture(), { 0.f, 0.f }, { 0.f, 0.f }, Vector2::Zero, 1, { mAnimSize, mAnimSize }, 0.1f);
		mAnimator->Play(L"AfterImage");


		CGameObj::Initialize();
	}

	void CAfterImage::update()
	{
		Vector3 pos = mFrameCaptures.Position;
		pos.z += 0.0001f;
		SetPos(pos);

		CGameObj::update();
	}

	void CAfterImage::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CAfterImage::render()
	{
		CGameObj::render();
	}

}