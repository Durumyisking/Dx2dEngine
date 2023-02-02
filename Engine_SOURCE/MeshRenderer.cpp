#include "MeshRenderer.h"
#include "GameObj.h"
#include "Transform.h"

namespace dru
{
	CMeshRenderer::CMeshRenderer()
		: CComponent(eComponentType::Mesh)
		, mMesh(nullptr)
		, mShader(nullptr)
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

		mShader->Bind();
		mShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mMesh->BindBuffer();

		mMesh->Render();
	}

}