#include "PostProcessRenderer.h"
#include "PostProcess.h"

namespace dru
{
	CPostProcessRenderer::CPostProcessRenderer()
		: CBaseRenderer(eComponentType::Renderer)
	{
	}

	CPostProcessRenderer::~CPostProcessRenderer()
	{
	}

	void CPostProcessRenderer::Initialize()
	{
		CBaseRenderer::Initialize();
	}

	void CPostProcessRenderer::update()
	{
		CBaseRenderer::update();
	}

	void CPostProcessRenderer::fixedUpdate()
	{
		CBaseRenderer::fixedUpdate();
	}

	void CPostProcessRenderer::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();

		GetMesh()->BindBuffer();

		mPostProcess->Bind();
		GetMaterial()->Bind();

		GetMesh()->Render();

		mPostProcess->Clear();
		GetMaterial()->Clear();

		CBaseRenderer::render();
	}

	void CPostProcessRenderer::SetPostProcessOwner(CPostProcess* _PostProcess)
	{
		mPostProcess = _PostProcess;
	}


}