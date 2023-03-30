#include "ParticleShader.h"
#include "Renderer.h"
#include "ConstantBuffer.h"
#include "TimeMgr.h"

namespace dru::graphics
{
	CParticleShader::CParticleShader()
		: CComputeShader(128, 1, 1)
		, mBuffer(nullptr)
	{
	}
	CParticleShader::~CParticleShader()
	{
	}
	void CParticleShader::Bind()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);

		mGroupX = mBuffer->GetStrideSize() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void CParticleShader::Clear()
	{
		mBuffer->Clear();
	}
	void CParticleShader::SetStrcutedBuffer(CStructedBuffer* buffer)
	{
		mBuffer = buffer;

		renderer::ParticleSystemCB info = {};
		info.elementCount = mBuffer->GetStrideSize();
		info.deltaTime = CTimeMgr::DeltaTime();

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&info);
		cb->Bind(eShaderStage::CS);
	}
}
