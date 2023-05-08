#include "AfterImageRenderer.h"
#include "GameObj.h"
#include "Transform.h"
#include "Animator.h"
#include "PlayerAfterImage.h"
#include "Player.h"
#include "TimeMgr.h"

namespace dru
{
	CAfterImageRenderer::CAfterImageRenderer()
		: CBaseRenderer(eComponentType::Renderer)
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

		CLiveGameObj* Owner = dynamic_cast<CAfterImage*>(GetOwner())->GetOwner();

		if (eLayerType::Player == Owner->GetLayerType())
		{
			if (CTimeMgr::IsBulletTimeOn())
			{
				MulColor(Vector4(0.f, 2.f, 2.f, 1.f));
			}
			else
			{
				int randvalue = GetRandomNumber(1, 0);
					if (0 == randvalue)
					{
						MulColor(Vector4(0.f, 5.f, 5.f, 0.5f));
					}
					else if (1 == randvalue)
					{
						MulColor(Vector4(5.f, 0.f, 5.f, 0.5f));
					}
			}

		}
		else if (eLayerType::Monster == Owner->GetLayerType())
		{
			MulColor({ 1.f, 0.f, 1.f, 0.5f });
		}
		else if (eLayerType::Boss == Owner->GetLayerType())
		{
			MulColor({ 1.f, 0.f, 1.f, 0.5f });
		}

	}

}