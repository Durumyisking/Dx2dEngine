#include "PostProcess.h"
#include "TimeMgr.h"
#include "Application.h"
#include "PostProcessRenderer.h"

extern dru::CApplication application;

namespace dru
{
	CPostProcess::CPostProcess()
		: mPostProcessMaterial(nullptr)
		, mConstantBuffer{}
		, mRenderer(nullptr)
	{
		mConstantBuffer.Resolution = application.WinResolution();

		mRenderer = AddComponent<CPostProcessRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> mateiral = CResources::Find<CMaterial>(L"PostProcessMaterial");
		mRenderer->SetMaterial(mateiral);
		mRenderer->SetPostProcessOwner(this);

		SetPos(Vector3(0.f, 0.f, 0.f));
		SetScale(Vector3(16.0f, 9.0f, 1.0f));
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
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::PostProcess];
		cb->SetData(&mConstantBuffer);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);


	}

	void CPostProcess::Clear()
	{
		CConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::PostProcess];
		pCB->Clear();
	}

	void CPostProcess::SetMaterial(std::wstring _Key)
	{
		std::shared_ptr<CMaterial> mateiral = CResources::Find<CMaterial>(_Key);
		mRenderer->SetMaterial(mateiral);
	}

}