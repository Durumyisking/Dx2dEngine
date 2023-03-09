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
		CBaseRenderer::Initialize();
	}

	void CMeshRenderer::update()
	{
		CBaseRenderer::update();
	}

	void CMeshRenderer::fixedUpdate()
	{
		CBaseRenderer::fixedUpdate();
	}

	void CMeshRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		GetMesh()->BindBuffer();
		GetMesh()->Render();

		GetMaterial()->Clear();

		CBaseRenderer::render();
	}

}