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

		void SetStartPosition(Vector3 _StartPos) { mStartPosition = Vector4(_StartPos.x, _StartPos.y, _StartPos.z, 1.f); }
		void SetStartScale(Vector3 _StartScale) { mStartScale= Vector4(_StartScale.x, _StartScale.y, _StartScale.z, 1.f); }

		void SetMaxElapsedTime(float _Value) { mMaxElapsedTime = _Value; }

		void SetMaxParticleCount(UINT _MaxParticleCount) { mMaxParticles = _MaxParticleCount; }
		void SetStartColor(Vector4 _Color) { mStartColor = _Color; }
		void SetEndColor(Vector4 _Color) { mEndColor = _Color; }
		void SetMaxLifeTime(float _MaxLifeTime) { mMaxLifeTime = _MaxLifeTime; }
		void SetMinLifeTime(float _MinLifeTime) { mMinLifeTime = _MinLifeTime; }

	private:
		Particle mParticle[256];

	
		class CStructedBuffer* mBuffer;
		class CStructedBuffer* mSharedBuffer;
		std::shared_ptr<graphics::CParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;

		Vector4 mStartPosition;
		Vector4 mStartScale;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mTime;
		float mFrequency;

		
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

