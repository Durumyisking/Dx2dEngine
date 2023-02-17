#include "MeshRenderer.h"
#include "GameObj.h"
#include "Transform.h"

namespace dru
{
	CMeshRenderer::CMeshRenderer()
		: CBaseRenderer(eComponentType::MeshRenderer)
	{
	}

	CMeshRenderer::~CMeshRenderer()
	{
	}

	void CMeshRenderer::Initialize()
	{
	}

	void CMeshRenderer::update()
	{
	}

	void CMeshRenderer::fixedupdate()
	{
	}

	void CMeshRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		GetMesh()->BindBuffer();
		GetMesh()->Render();

		GetMaterial()->Clear();
	}

}