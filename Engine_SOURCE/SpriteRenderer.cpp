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
	}

	void CSpriteRenderer::update()
	{
	}

	void CSpriteRenderer::fixedupdate()
	{
	}

	void CSpriteRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		GetMesh()->BindBuffer();
		GetMesh()->Render();

		GetMaterial()->Clear();
	}

}