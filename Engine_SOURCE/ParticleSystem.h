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

		void MakeParticleBufferData(Vector4 startPosition, Vector4 direction, UINT maxParticleCount, float speed, float radian, UINT active);
		void MakeConstantBufferData(std::wstring _ShaderName, renderer::ParticleSystemCB _CB)
		{
			mCS = CResources::Find<CParticleShader>(_ShaderName);
			mCBData = _CB; 
		}
		void SetMaxElapsedTime(float _Value) { mMaxElapsedTime = _Value; }

	private:
		Particle mParticle[256];

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

		float mElapsedTime; //누적시간
		float mGravity;
		float mForce;

		float mMaxElapsedTime;
	};

}

