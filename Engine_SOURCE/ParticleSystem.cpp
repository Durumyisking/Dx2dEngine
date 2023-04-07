//#include "ParticleSystem.h"
//#include "Mesh.h"
//
//#include "GameObj.h"
//#include "Transform.h"
//#include "Mesh.h"
//#include "Resources.h"
//#include "StructedBuffer.h"
//#include "Texture.h"
//#include "TimeMgr.h"
//
//
//namespace dru
//{
//	CParticleSystem::CParticleSystem()
//		: CBaseRenderer(eComponentType::Particle)
//		, mMaxParticles(100)
//		, mStartSize(Vector4(20.0f, 20.0f, 1.0f, 1.0f))
//		, mStartColor(Vector4(1.0f, 1.f, 1.f, 1.0f))
//		, mStartLifeTime(10.0f)
//		, mFrequency(1.0f)
//		, mTime(0.0f)
//		, mCBData{}
//		, mSimulationSpace(eSimulationSpace::World)
//		, mRadius(500.0f)
//		, mStartSpeed(10.0f)
//		, mElapsedTime(0.0f)
//	{
//		
//	}
//
//	CParticleSystem::~CParticleSystem()
//	{
//		delete mBuffer;
//		mBuffer = nullptr;
//		delete mSharedBuffer;
//		mSharedBuffer = nullptr;
//	}
//
//	void CParticleSystem::Initialize()
//	{
//		mCS = CResources::Find<CParticleShader>(L"ParticleCS");
//
//		std::shared_ptr<CMesh> point = CResources::Find<CMesh>(L"Pointmesh");
//		SetMesh(point);
//
//		// Material 세팅
//		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"ParticleMaterial");
//		SetMaterial(material);
//
//		std::shared_ptr<CTexture> tex = CResources::Find<CTexture>(L"particle_spark");
//		material->SetTexture(eTextureSlot::T0, tex);
//
//
//		Particle particles[100] = {};
//		Vector4 startPos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
//
//		for (size_t i = 0; i < mMaxParticles; i++)
//		{
//			particles[i].position = Vector4(0.0f, 0.0f, 10.0f, 1.0f);
//			particles[i].active = 0;
//			particles[i].direction =
//				Vector4(cosf((float)i * (XM_2PI / (float)mMaxParticles))
//					, sin((float)i * (XM_2PI / (float)mMaxParticles)), 0.0f, 1.0f);
//
//			particles[i].speed = 10.f; 
//		}
//		//for (size_t i = 50; i < mCount; i++)
//		//{
//		//	particles[i].active = 0;
//		//}
//
//		mBuffer = new CStructedBuffer();
//		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, particles);
//		mSharedBuffer = new CStructedBuffer();
//		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
//	}
//
//	void CParticleSystem::update()
//	{
//	}
//
//	void CParticleSystem::fixedUpdate()
//	{
//		float aliveTime = 0.1f / mFrequency;  // 프리퀀시가 높을수록 빨리생성
//		//누적시간
//		mTime += CTimeMgr::DeltaTime();
//		if (aliveTime < mTime) 
//		{
//			float f = (mTime / aliveTime); 
//			UINT iAliveCount = (UINT)f;
//			mTime = f - std::floor(f);
//
//			ParticleShared shared = { 5 ,}; // 20을 computeShader에 보내겠다
//			mSharedBuffer->SetData(&shared, 1);
//		}
//		else
//		{
//			ParticleShared shared = {  }; // if아닐때는 0을 보내네
//			mSharedBuffer->SetData(&shared, 1);
//		}
//	
//		mMaxParticles = mBuffer->GetStride();
//		Vector3 pos = GetOwner()->GetComponent<CTransform>()->GetPosition();
//		mCBData.worldPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
//		mCBData.maxParticles = mMaxParticles;
//		mCBData.radius = mRadius;
//		mCBData.simulationSpace = (UINT)mSimulationSpace;
//		mCBData.startSpeed = mStartSpeed;
//		mCBData.startSize = mStartSize;
//		mCBData.startColor = mStartColor;
//		mCBData.startLifeTime = mStartLifeTime;
//		mCBData.deltaTime = CTimeMgr::DeltaTime();
//		mCBData.elapsedTime += CTimeMgr::DeltaTime();
//
//		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
//		cb->SetData(&mCBData);
//		cb->Bind(eShaderStage::All);
//
//		mCS->SetSharedStrutedBuffer(mSharedBuffer); 
//		mCS->SetStrcutedBuffer(mBuffer);
//		mCS->OnExcute();
//	}
//
//	void CParticleSystem::render() // cs는 fixedupdate에서 근데 왜?
//	{
//		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
//		mBuffer->BindSRV(eShaderStage::GS, 15);
//
//		GetMaterial()->Bind();
//		GetMesh()->RenderInstanced(mMaxParticles);
//
//		mBuffer->Clear();
//	}
//
//}

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
		, mCount(100)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mStartLifeTime(0.f)
		, mBuffer(nullptr)
		, mFrequency(1.0f)
		, mTime(0.0f)
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
		mCS = CResources::Find<CParticleShader>(L"ParticleCS");

		std::shared_ptr<CMesh> point = CResources::Find<CMesh>(L"Pointmesh");
		SetMesh(point);

		// Material ¼¼Æ?
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<CTexture> tex = CResources::Find<CTexture>(L"particle_spark");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[i].active = 0;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)mCount))
					, sin((float)i * (XM_2PI / (float)mCount)), 0.0f, 1.0f);

			particles[i].speed = 50.f;
		}
		//for (size_t i = 50; i < mCount; i++)
		//{
		//	particles[i].active = 0;
		//}

		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);
		mSharedBuffer = new CStructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void CParticleSystem::update()
	{
	}

	void CParticleSystem::fixedUpdate()
	{
		float aliveTime = 1.0f / mFrequency;
		mTime += CTimeMgr::DeltaTime();
		if (aliveTime < mTime)
		{
			float f = (mTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5, };
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  };
			mSharedBuffer->SetData(&shared, 1);
		}

		renderer::ParticleSystemCB info = {};
		info.elementCount = mBuffer->GetStrideSize();
		info.deltaTime = CTimeMgr::DeltaTime();

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&info);
		cb->Bind(eShaderStage::CS);

		mCS->SetSharedStrutedBuffer(mSharedBuffer); mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void CParticleSystem::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 15);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}

}