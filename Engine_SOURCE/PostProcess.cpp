#include "PostProcess.h"
#include "TimeMgr.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	CPostProcess::CPostProcess()
		: mPostProcessMaterial(nullptr)
		, mConstantBuffer{}
	{
		mConstantBuffer.Resolution = application.WinResolution();
	}

	CPostProcess::~CPostProcess()
	{
	}

	void CPostProcess::Initialize()
	{
		CGameObj::Initialize();
	}

	void CPostProcess::update()
	{
		mConstantBuffer.ElapsedTime += CTimeMgr::DeltaTime();

		CGameObj::update();
	}

	void CPostProcess::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CPostProcess::render()
	{
		CGameObj::render();
	}

	void CPostProcess::Bind()
	{
		CConstantBuffer* cb2 = renderer::constantBuffers[(UINT)eCBType::PostProcess];
		cb2->SetData(&mConstantBuffer);
		cb2->Bind(eShaderStage::VS);
		cb2->Bind(eShaderStage::PS);


	}

	void CPostProcess::Clear()
	{
		CConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::PostProcess];
		pCB->Clear();
	}

}