#include "SpriteRenderer.h"
#include "GameObj.h"
#include "Transform.h"
#include "Animator.h"
#include "LiveGameObj.h"

namespace dru
{
	CSpriteRenderer::CSpriteRenderer()
		: CBaseRenderer(eComponentType::Renderer)
	{
	}

	CSpriteRenderer::~CSpriteRenderer()
	{
	}

	void CSpriteRenderer::Initialize()
	{
		CBaseRenderer::Initialize();
	}

	void CSpriteRenderer::update()
	{
		CBaseRenderer::update();
	}

	void CSpriteRenderer::fixedUpdate()
	{
		CBaseRenderer::fixedUpdate();
	}

	void CSpriteRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();

		GetMesh()->BindBuffer();
		GetMaterial()->Bind();


		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();

		if (animator)
		{
			if (CGameObj::eObjectType::None == GetOwner()->GetObjectType())
			{
				animator->Binds();
			}
			else if (CGameObj::eObjectType::Live == GetOwner()->GetObjectType())
			{
				CLiveGameObj* liveObj = dynamic_cast<CLiveGameObj*>(GetOwner());
				if (liveObj->IsRewinding() || liveObj->IsReplaying())
				{
					renderer::AnimationCB data = liveObj->GetCurrentAnimData();
					animator->BindSprite(data);
				}
				else
				{
					animator->Binds();
				}
			}
		}	

		GetMesh()->Render();

		GetMaterial()->Clear();
			
		if (animator)
			animator->Clear();

		CBaseRenderer::render();
	}


}