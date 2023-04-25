#include "AfterImageRenderer.h"
#include "GameObj.h"
#include "Transform.h"
#include "Animator.h"
#include "PlayerAfterImage.h"
#include "Player.h"

namespace dru
{
	CAfterImageRenderer::CAfterImageRenderer()
		: CBaseRenderer(eComponentType::AfterImageRenderer)
		, mAfterImageOwner(nullptr)
	{
	}

	CAfterImageRenderer::~CAfterImageRenderer()
	{
	}

	void CAfterImageRenderer::Initialize()
	{
		CBaseRenderer::Initialize();
	}

	void CAfterImageRenderer::update()
	{
		CBaseRenderer::update();
	}

	void CAfterImageRenderer::fixedUpdate()
	{
		CBaseRenderer::fixedUpdate();
	}

	void CAfterImageRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		GetMesh()->BindBuffer();


		int idx = mAfterImageOwner->GetIndex();
		UINT Size = mAfterImageOwner->GetOwner()->GetAfterImageCount();

		float alpha = GetIndexAlpha(idx, Size);
		ColorSetting();
		GetMaterial()->SetData(eGPUParam::Float_4, &alpha);
		
		GetMaterial()->Bind();


		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();

		if (animator)
		{			
			renderer::AnimationCB data = mAfterImageOwner->GetAnimCB();
			animator->BindSprite(data);
		}


		GetMesh()->Render();
		GetMaterial()->Clear();

		if (animator)
			animator->Clear();

		CBaseRenderer::render();
	}

	float CAfterImageRenderer::GetIndexAlpha(int _Idx, UINT _MaxCount)
	{
		float alpha = 0.1f / _MaxCount;
		float alpharesult = alpha * _Idx; // 플레이어의 전체 잔상 개수 - 잔상 인덱스 (늦은 잔상일수록 작은값)

		return alpharesult;
	}

	void CAfterImageRenderer::ColorSetting()
	{
		int randvalue = GetRandomNumber(1, 0);
		if (0 == randvalue)
		{
			AddColor(Vector4(0.f, 2.f, 2.f, 1.f));
		}
		else if (1 == randvalue)
		{
			AddColor(Vector4(2.f, 0.f, 2.f, 1.f));
		}

	}

}