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
		, mCBData{}
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


		Particle particles[100] = {};
		Vector4 startPos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			particles[i].active = 0;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)mCount))
					, sin((float)i * (XM_2PI / (float)mCount)), 0.0f, 1.0f);

			particles[i].speed = 10.f; 
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

	void CParticleSystem::fixedUpdate()//이해 안댐
	{
		float aliveTime = 0.1f / mFrequency;  // 프리퀀시가 머임?
		//누적시간
		mTime += CTimeMgr::DeltaTime();
		if (aliveTime < mTime) 
		{
			float f = (mTime / aliveTime); // 이게 뭐시어
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 20 }; // 20을 computeShader에 보내겠다
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  }; // if아닐때는 0을 보내네
			mSharedBuffer->SetData(&shared, 1);
		}

		mCBData.elementCount = mBuffer->GetStrideSize();
		mCBData.deltaTime = CTimeMgr::DeltaTime();
		mCBData.elapsedTime += CTimeMgr::DeltaTime();

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::CS);

		mCS->SetSharedStrutedBuffer(mSharedBuffer); mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void CParticleSystem::render() // cs는 fixedupdate에서 근데 왜?
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		//mBuffer->BindSRV(eShaderStage::VS, 15);
		//mBuffer->BindUAV(eShaderStage::VS, 0);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		//mBuffer->BindUAV(eShaderStage::GS, 0);
		//mBuffer->BindSRV(eShaderStage::PS, 15);
		//mBuffer->BindUAV(eShaderStage::PS, 0);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}

}