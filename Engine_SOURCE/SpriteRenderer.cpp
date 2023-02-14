#include "SpriteRenderer.h"
#include "GameObj.h"
#include "Transform.h"

namespace dru
{
	CSpriteRenderer::CSpriteRenderer()
		: CComponent(eComponentType::SpriteRenderer)
		, mMesh(nullptr)
		, mMaterial(nullptr)

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

		mMaterial->Bind();

		mMesh->BindBuffer();
		mMesh->Render();

		mMaterial->Clear();
	}

}