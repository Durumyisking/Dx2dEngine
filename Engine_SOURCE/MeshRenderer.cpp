#include "MeshRenderer.h"
#include "GameObj.h"
#include "Transform.h"

namespace dru
{
	CMeshRenderer::CMeshRenderer()
		: CComponent(eComponentType::Mesh)
		, mMesh(nullptr)
		, mMaterial(nullptr)
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

		mMaterial->Bind();

		mMesh->BindBuffer();
		mMesh->Render();
	}

}