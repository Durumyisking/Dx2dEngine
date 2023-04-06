#pragma once
#include "BaseRenderer.h"
#include "ParticleShader.h"

namespace dru
{
    class CParticleSystem : public CBaseRenderer
    {
	public:
		CParticleSystem();
		virtual ~CParticleSystem();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;


	private:
		class CStructedBuffer* mBuffer;
		class CStructedBuffer* mSharedBuffer;
		std::shared_ptr<graphics::CParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;
		float mFrequency;
		float mTime;
	};

}


