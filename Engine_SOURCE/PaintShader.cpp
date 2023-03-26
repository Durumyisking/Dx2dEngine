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
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Material];
		renderer::MaterialCB data = {};

		int* p = new int;
		srand((unsigned int)p);

		data.fData2 = (float)(rand() % 1001) / 1000.f;
		data.fData3 = (float)(rand() % 1001) / 1000.f;
		data.fData4 = (float)(rand() % 1001) / 1000.f;

		float x = (float)(rand() % 100000001) / 10.f;
		float y = (float)(rand() % 100000001) / 10.f;
		float z = (float)(rand() % 100000001) / 10.f;

		data.xyz = Vector3(x,y,z);

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::CS);

		mTarget->BindUnorderedAccessview(0);
		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}

	void CPaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessview(0);
	}


}