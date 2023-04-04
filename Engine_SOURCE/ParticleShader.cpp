#include "ParticleShader.h"
#include "Renderer.h"
#include "ConstantBuffer.h"
#include "TimeMgr.h"

namespace dru::graphics
{
	CParticleShader::CParticleShader()
		: CComputeShader(128, 1, 1)
		, mBuffer(nullptr)
		, mSharedBuffer(nullptr) 
	{
	}
	CParticleShader::~CParticleShader()
	{
	}
	void CParticleShader::Bind()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);
		mSharedBuffer->BindUAV(eShaderStage::CS, 1);
		mGroupX = mBuffer->GetStrideSize() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void CParticleShader::Clear()
	{
		mBuffer->Clear();
		mSharedBuffer->Clear();
	}

}
