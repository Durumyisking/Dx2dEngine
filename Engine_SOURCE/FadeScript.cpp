#include "FadeScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Application.h"
#include "ConstantBuffer.h"
#include "TimeMgr.h"


namespace dru
{
	CFadeScript::CFadeScript()
	{
	}

	CFadeScript::~CFadeScript()
	{
	}

	void CFadeScript::Initialize()
	{
	}

	void CFadeScript::update()
	{
	
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data = {};


		data.world = GetOwner()->GetComponent<CTransform>()->GetWorldPos();
		data.view = CCamera::GetViewMatrix();
		data.projection = CCamera::GetProjectionMatrix();

		data.fValue = 2.f * CTimeMgr::AccumulatedTime();
		data.bFadeType = 0;

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	}

	void CFadeScript::fixedupdate()
	{
	}

	void CFadeScript::render()
	{
	}

}