#include "PaintShader.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "TimeMgr.h"

namespace dru::graphics
{
	CPaintShader::CPaintShader()
		: mTarget(nullptr)
	{
	}

	CPaintShader::~CPaintShader()
	{
	}

	void CPaintShader::Bind()
	{
		mTarget->BindUnorderedAccessview(0);
		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Material];
		renderer::MaterialCB data = {};

		data.fData2 = CTimeMgr::DeltaTime();

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);
	}

	void CPaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessview(0);
	}


}