#include "ParticleSystem.h"
#include "Mesh.h"

#include "GameObj.h"
#include "Transform.h"
#include "Mesh.h"
#include "Resources.h"
#include "StructedBuffer.h"
#include "Texture.h"
#include "TimeMgr.h"


namespace dru
{
	CParticleSystem::CParticleSystem()
		: CBaseRenderer(eComponentType::Particle)
		, mParticle{}
		, mBuffer{}
		, mSharedBuffer{}
		, mCBData{}
		, mSimulationSpace(eSimulationSpace::World)
		, mCS(nullptr)
		, mMaxParticles(1)
		, mStartPosition(Vector4(0.f, 0.f, 0.f, 1.f))
		, mStartScale(Vector4(0.1f, 0.1f, 1.f, 1.f))
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mMaxLifeTime(1.f)
		, mMinLifeTime(0.5f)
		, mStartAngle(0.f)
		, mEndAngle(360.f)
		, mElapsedTime(0.f)
		, mGravity(-1000.f)
		, mRadius(10.f)
		, mStartSpeed(5.f)
		, mEndSpeed(2.f)
		, mForce(0.f)
		, mRadian(0.f)
		, mFrequency(0.25f)
		, mMaxElapsedTime(5.f)
		, mbUseSwitch(false)
		, mParticleCountInFrame(1)
	{
	}

	CParticleSystem::~CParticleSystem()
	{
		delete mParticle;
		mParticle = nullptr;
		delete mBuffer;
		mBuffer = nullptr;
		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void CParticleSystem::Initialize()
	{
		std::shared_ptr<CMesh> point = CResources::Find<CMesh>(L"Pointmesh");

		SetMesh(point);

//		mParticle = new Particle[mMaxParticles];

		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, mParticle, true);
		mSharedBuffer = new CStructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void CParticleSystem::update()
	{
	}

	void CParticleSystem::fixedUpdate()
	{
		float aliveTime = 0.1f / mFrequency;  // 프리퀀시가 높을수록 빨리생성 한번에 생성하는거
		//누적시간
		mElapsedTime += CTimeMgr::DeltaTime();
		if (aliveTime < mElapsedTime)
		{
			float f = (mElapsedTime / aliveTime);
			mElapsedTime = f - std::floor(f);

			ParticleShared shared = { mParticleCountInFrame }; // 20을 computeShader에 보내겠다
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  }; // if아닐때는 0을 보내네
			mSharedBuffer->SetData(&shared, 1);
		}

		mCBData.worldPosition = mStartPosition;
		mCBData.startSize = mStartScale;
		mCBData.startColor = mStartColor;
		mCBData.endColor = mEndColor;

		mCBData.maxParticles = mMaxParticles;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.radius = mRadius;
		mCBData.deltaTime = CTimeMgr::DeltaTime();

		mCBData.startSpeed = mStartSpeed;
		mCBData.endSpeed = mEndSpeed;
		mCBData.maxLifeTime = mMaxLifeTime;
		mCBData.minLifeTime = mMinLifeTime;

		mCBData.startAngle = mStartAngle;
		mCBData.endAngle = mEndAngle;
		mCBData.elapsedTime += CTimeMgr::DeltaTime();
		mCBData.gravity += CTimeMgr::DeltaTime();

		mCBData.force = mStartSpeed;
		mCBData.radian = mRadian;

		if (mCBData.elapsedTime > mMaxElapsedTime)
		{
			if (mbUseSwitch)
			{
				mParticleCountInFrame = 0;
			}
			mCBData.elapsedTime = 0.f;
		}

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::All);

		mCS->SetSharedStrutedBuffer(mSharedBuffer);
		mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
		
	}

	void CParticleSystem::render() 
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}

	// 밑으로 180도
	/*
	Vector4(cosf((float)i * (XM_PI / (float)mMaxParticles))
					, sin((float)i * -(XM_PI / (float)mMaxParticles)), 0.f, 1.f);
	*/

	void CParticleSystem::MakeParticleBufferData(Vector4 _StartPosition, UINT _MaxParticleCount, float _MinLifeTime, float _MaxLifeTime, float _Speed, float _Radian, UINT _Active)
	{
		mParticle = new Particle[_MaxParticleCount];
		mStartPosition = _StartPosition;
		mMaxParticles = _MaxParticleCount;
		for (size_t i = 0; i < mMaxParticles; i++)
		{
			mParticle[i].position = _StartPosition;
			mParticle[i].direction.Normalize();
			mParticle[i].lifeTime = _MaxLifeTime;
			mParticle[i].speed = _Speed;
			mParticle[i].radian = _Radian;
			mParticle[i].active = 0;
		}
	}


	void CParticleSystem::SetParticleDirection(const Vector3& _Dir)
	{
		float fAngle = atan2(_Dir.y, _Dir.x) * 180.f / XM_PI;

		mStartAngle = fAngle - 0.15f;
		mEndAngle = fAngle + 0.15f;

		mStartSpeed = _Dir.Length() - 2.f;
		mEndSpeed = _Dir.Length() + 2.f;
	}


}