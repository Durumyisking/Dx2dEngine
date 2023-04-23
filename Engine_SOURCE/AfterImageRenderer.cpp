#include "AfterImageRenderer.h"
#include "GameObj.h"
#include "Transform.h"
#include "Animator.h"
#include "PlayerAfterImage.h"

namespace dru
{
	CAfterImageRenderer::CAfterImageRenderer()
		: CBaseRenderer(eComponentType::AfterImageRenderer)
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

}