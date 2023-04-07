#pragma once
#include "BaseRenderer.h"
#include "ParticleShader.h"

namespace dru
{
    class CParticleSystem : public CBaseRenderer
    {
		enum class eSimulationSpace
		{
			Local,
			World,
		};
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

		Vector4 mStartSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mTime;
		float mFrequency;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;
		
		float mRadius;
		float mStartSpeed;

		float mMaxLifeTime;
		float mMinLifeTime;

		float mElapsedTime; //�����ð�
		float mGravity;
		float mForce;
	};

}

