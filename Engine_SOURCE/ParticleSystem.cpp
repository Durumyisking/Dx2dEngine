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
		, mStartColor(Vector4(0.4941f, 0.8118f, 0.9765f, 1.f))
		//, mStartColor(Vector4(0.9647f, 0.9843f, 0.698f, 1.f))
		, mEndColor(Vector4(0.9569f, 0.6672f, 0.4588f, 1.f))
		, mMaxLifeTime(1.f)
		, mMinLifeTime(0.5f)
		, mFrequency(0.25f)
		, mTime(0.f)
		, mRadius(10.f)
		, mStartSpeed(50.f)
		, mElapsedTime(0.f)
		, mGravity(0.f)
		, mForce(0.f)
		, mMaxElapsedTime(1.f)	
	{
	}

	CParticleSystem::~CParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void CParticleSystem::Initialize()
	{
		std::shared_ptr<CMesh> point = CResources::Find<CMesh>(L"Pointmesh");
		SetMesh(point);

		//for (size_t i = 50; i < mCount; i++)
		//{
		//	mParticle[i].active = 0;
		//}

		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, mParticle);
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
		mTime += CTimeMgr::DeltaTime();
		if (aliveTime < mTime) 
		{
			float f = (mTime / aliveTime); 
			mTime = f - std::floor(f);

			ParticleShared shared = { 1 }; // 20을 computeShader에 보내겠다
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  }; // if아닐때는 0을 보내네
			mSharedBuffer->SetData(&shared, 1);
		}
	
//		mMaxParticles = mBuffer->GetStride();


		mCBData.worldPosition = mStartPosition;
		mCBData.startSize = mStartScale;

		mCBData.maxParticles = mMaxParticles;
		mCBData.radius = mRadius;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.startSpeed = mStartSpeed;
		mCBData.startColor = mStartColor;
		mCBData.endColor = mEndColor;
		mCBData.maxLifeTime = mMaxLifeTime;
		mCBData.minLifeTime = mMinLifeTime;
		mCBData.gravity = mGravity;
		mCBData.force = mForce;


		mCBData.deltaTime = CTimeMgr::DeltaTime();
		mCBData.elapsedTime += CTimeMgr::DeltaTime();

		if (mCBData.elapsedTime > mMaxElapsedTime)
		{
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

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}

	// 밑으로 180도
	/*
	Vector4(cosf((float)i * (XM_PI / (float)mMaxParticles))
					, sin((float)i * -(XM_PI / (float)mMaxParticles)), 0.f, 1.f);
	*/

	void CParticleSystem::MakeParticleBufferData(Vector4 startPosition, Vector4 direction, UINT maxParticleCount ,float speed, float radian, UINT active)
	{
		mMaxParticles = maxParticleCount;
		for (size_t i = 0; i < mMaxParticles; i++)
		{
			mParticle[i].position = Vector4(0.f, 0.f, 0.f, 1.f);
			mParticle[i].direction = direction;
			mParticle[i].direction.Normalize();
			mParticle[i].speed = speed;
			mParticle[i].radian = radian;
			mParticle[i].active = active;
		}
	}


}