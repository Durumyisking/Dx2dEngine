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

		void MakeParticleBufferData(Vector4 _StartPosition, UINT _MaxParticleCount, float _MinLifeTime, float _MaxLifeTime, float _Speed, float _Radian, UINT _Active);

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
		void SetStartSpeed(float _StartSpeed) { mStartSpeed = _StartSpeed; }
		void SetEndSpeed(float _EndSpeed) { mEndSpeed = _EndSpeed; }
		void SetMaxLifeTime(float _MaxLifeTime) { mMaxLifeTime = _MaxLifeTime; }
		void SetMinLifeTime(float _MinLifeTime) { mMinLifeTime = _MinLifeTime; }
		void SetRadius(float _Radius) { mRadius = _Radius; }

		void SetParticleDirection(const Vector3& _Dir);
		void SetParticleCountInFrame(UINT _Count) { mParticleCountInFrame = _Count; }

		void SetFrequency(float _Frequency) { mFrequency = _Frequency; }

		void UseSwitchOn() { mbUseSwitch = true; }
		void UseSwitchOff() { mbUseSwitch = false; }
		void SwitchReset() { mbTimerSwitch = false; }

	private:
		Particle* mParticle;

	
		class CStructedBuffer* mBuffer;
		class CStructedBuffer* mSharedBuffer;
		std::shared_ptr<graphics::CParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		Vector4 mStartPosition;
		Vector4 mStartScale;
		Vector4 mStartColor;
		Vector4 mEndColor;

		UINT mMaxParticles;
		eSimulationSpace mSimulationSpace;
		float mRadius;

		float mStartSpeed;
		float mEndSpeed;
		float mMaxLifeTime;
		float mMinLifeTime;

		float mStartAngle;
		float mEndAngle;
		float mElapsedTime;
		float mGravity;

		float mForce;
		float mRadian;

		float mFrequency;

		float mMaxElapsedTime;

		bool mbUseSwitch;
		bool mbTimerSwitch;
		UINT mParticleCountInFrame;

	};

}

