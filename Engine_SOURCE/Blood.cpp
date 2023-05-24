#include "Blood.h"

namespace dru
{
	CBlood::CBlood()
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BloodMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Blood1", Material->GetTexture(), { 0.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Blood2", Material->GetTexture(), { 300.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Blood3", Material->GetTexture(), { 600.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);

//		RenderingBlockOn();

		int randomNumber = GetRandomNumber(3);

		switch (randomNumber)
		{
		case 0:
			mAnimator->Play(L"Blood1");
			break;
		case 1:
			mAnimator->Play(L"Blood2");
			break;
		case 2:
			mAnimator->Play(L"Blood3");
			break;
		default:
			break;
		}

		if (mAnimator)
		{
			mAnimator->GetCompleteEvent(L"Blood1") = [this]
			{
				RenderingBlockOn();
			};
			mAnimator->GetCompleteEvent(L"Blood2") = [this]
			{
				RenderingBlockOn();
			};
			mAnimator->GetCompleteEvent(L"Blood3") = [this]
			{
				RenderingBlockOn();
			};
		}

	}
	CBlood::~CBlood()
	{
	}
	void CBlood::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CBlood::update()
	{
		CLiveGameObj::update();
	}

	void CBlood::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBlood::render()
	{
		CLiveGameObj::render();
	}

	void CBlood::SetBloodPosition(Vector3 _Standard, Vector3 _Direction)
	{
		Vector3 newPos = {};
		newPos.z = _Standard.z;

		Vector2 Standard2D = { _Standard.x, _Standard.y };

		Vector2 Range = {};
		Range.x = _Standard.x + _Direction.x * 2.5f;
		Range.y = _Standard.y + _Direction.y * 2.5f;

		// standard, range 사이의 랜덤한 점을 구한다
		float RandomRatio = static_cast<float>(GetRandomNumber(100, 1)) * 0.01f;
		Vector2 RandomStandard = {};
		RandomStandard.x = Standard2D.x + RandomRatio * (Range.x - Standard2D.x);
		RandomStandard.x = Standard2D.y + RandomRatio * (Range.y - Standard2D.y);

		// 해당 점에서 랜덤한 위치로 이동시킨다. direction 비율로 해야함 ㅇㅇ
		Vector2 RandomOffset = {};
		RandomOffset.x = static_cast<float>(GetRandomNumber(100, -50)) * 0.01f;
		RandomOffset.y = static_cast<float>(GetRandomNumber(100, -50)) * 0.01f;

		RandomStandard += RandomOffset;
		newPos.x = RandomStandard.x;
		newPos.y = RandomStandard.y;

		SetPos(newPos);
	}

}