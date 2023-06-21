#include "PlayerAfterImage.h"
#include "AfterImageRenderer.h"
#include "Animator.h"
#include "Player.h"

namespace dru
{
	UINT CAfterImage::midx;

	CAfterImage::CAfterImage()
		: mFrameCaptures{}
		, mMaterial(nullptr)
		, mOwner(nullptr)
		, mIndex(0)
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
		std::wstring idx = std::to_wstring(midx);
		matName += idx;
		OwnerName += matName;
		mMaterial = CResources::Find<CMaterial>(OwnerName);
	
		Renderer->SetMaterial(mMaterial);

		Renderer->SetAfterImageOwner(this);

		++midx;

		if (1000000 < midx)
		{
			midx = 0;
		}

		CGameObj::Initialize();
	}

	void CAfterImage::update()
	{
		Vector3 pos = mFrameCaptures.WorldPosition;
		Vector3 rot = mFrameCaptures.Rotation;
		pos.z += 0.0001f;
		SetPos(pos);
		SetRotation(rot);

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

	void CAfterImage::CreateAnimator(float _AnimSize)
	{
		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"AfterImage", mMaterial->GetTexture(), { 0.f, 0.f }, { 0.f, 0.f }, Vector2::Zero, 1, { _AnimSize, _AnimSize }, 0.1f);
		mAnimator->Play(L"AfterImage");
	}

}