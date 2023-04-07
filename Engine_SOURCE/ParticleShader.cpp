#include "ParticleShader.h"
#include "Renderer.h"
#include "ConstantBuffer.h"
#include "TimeMgr.h"

namespace dru::graphics
{
	CParticleShader::CParticleShader() // 얘는 컴퓨트세이더 상속받은애
		: CComputeShader(128, 1, 1) // 쓰레드 128개 쓸거임
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
		mGroupX = mBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void CParticleShader::Clear()
	{
		mBuffer->Clear();
		mSharedBuffer->Clear();
	}

}
