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
		, mMaxParticles(5)
		, mStartSize(Vector4(0.1f, 1.f, 1.f, 1.f))
		, mStartColor(Vector4(0.4941f, 0.8118, 0.9765, 1.f))
		//		, mStartColor(Vector4(0.9647f, 0.9843f, 0.698f, 1.f))
		, mEndColor(Vector4(0.9569f, 0.6672f, 0.4588f, 0.f))
		, mMaxLifeTime(1.f)
		, mMinLifeTime(0.1f)
		, mFrequency(100.f)
		, mTime(0.f)
		, mCBData{}
		, mSimulationSpace(eSimulationSpace::World)
		, mRadius(10.f)
		, mStartSpeed(50.f)
		, mElapsedTime(0.f)
		, mGravity(0.f)
		, mForce(0.f)
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

		// Material 세팅
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<CTexture> tex = CResources::Find<CTexture>(L"particle_spark");
		material->SetTexture(eTextureSlot::T0, tex);


		Particle particles[5] = {};
		Vector4 startPos = Vector4(0.f, 0.f, 0.f, 0.f);

		for (size_t i = 0; i < mMaxParticles; i++)
		{
			particles[i].position = Vector4(0.f, 0.f, 10.f, 1.f);
			particles[i].active = 0;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_PI / (float)mMaxParticles))
					, sin((float)i * -(XM_PI / (float)mMaxParticles)), 0.f, 1.f);

			particles[i].direction.Normalize();

			XMVECTOR upVector = XMVectorSet(0.f, 1.f, 0.f, 0.f); 
			float dotProduct = XMVectorGetX(XMVector3Dot(particles[i].direction, upVector));
			float radian = acosf(dotProduct);
			mCBData.radian = radian;

			particles[i].speed = 10.f; 
		}
		//for (size_t i = 50; i < mCount; i++)
		//{
		//	particles[i].active = 0;
		//}

		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, particles);
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
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5 }; // 20을 computeShader에 보내겠다
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  }; // if아닐때는 0을 보내네
			mSharedBuffer->SetData(&shared, 1);
		}
	
		mMaxParticles = mBuffer->GetStride();
		Vector3 pos = GetOwner()->GetComponent<CTransform>()->GetPosition();
		Vector3 rot = GetOwner()->GetComponent<CTransform>()->GetRotation();

		mCBData.worldPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);

		mCBData.maxParticles = mMaxParticles;
		mCBData.radius = mRadius;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.startSpeed = mStartSpeed;
		mCBData.startSize = mStartSize;
		mCBData.startColor = mStartColor;
		mCBData.endColor = mEndColor;
		mCBData.maxLifeTime = mMaxLifeTime;
		mCBData.minLifeTime = mMinLifeTime;
		mCBData.gravity = mGravity;
		mCBData.force = mForce;


		mCBData.deltaTime = CTimeMgr::DeltaTime();
		mCBData.elapsedTime += CTimeMgr::DeltaTime();

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::All);

		mCS->SetSharedStrutedBuffer(mSharedBuffer); 
		mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void CParticleSystem::render() // cs는 fixedupdate에서 근데 왜?
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}

}