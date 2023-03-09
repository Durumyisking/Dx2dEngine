#include "SpriteRenderer.h"
#include "GameObj.h"
#include "Transform.h"

namespace dru
{
	CSpriteRenderer::CSpriteRenderer()
		: CBaseRenderer(eComponentType::SpriteRenderer)
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

		GetMaterial()->Bind();

		GetMesh()->BindBuffer();
		GetMesh()->Render();

		GetMaterial()->Clear();

		CBaseRenderer::render();
	}


}