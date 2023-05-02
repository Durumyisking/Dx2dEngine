#include "PostProcessWave.h"

namespace dru
{
	CPostProcessWave::CPostProcessWave()
		: mAmount(35.f)
		, mSpeed(10.f)
		, mDistortion(40.f)

	{
	}

	CPostProcessWave::~CPostProcessWave()
	{
	}

	void CPostProcessWave::Initialize()
	{
		CPostProcess::Initialize();
	}

	void CPostProcessWave::update()
	{
		CPostProcess::update();
	}

	void CPostProcessWave::fixedUpdate()
	{
		CPostProcess::fixedUpdate();
	}

	void CPostProcessWave::render()
	{
		CPostProcess::render();
	}

	void CPostProcessWave::Bind()
	{
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::PostProcess];
		mConstantBuffer.wave_amount = mAmount;
		mConstantBuffer.wave_speed = mSpeed;
		mConstantBuffer.wave_distortion = mDistortion;

		CPostProcess::Bind();
	}

}