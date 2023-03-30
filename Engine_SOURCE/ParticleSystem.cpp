#include "ParticleSystem.h"
#include "Mesh.h"

#include "GameObj.h"
#include "Transform.h"
#include "Mesh.h"
#include "Resources.h"
#include "StructedBuffer.h"
#include "Texture.h"


namespace dru
{
	CParticleSystem::CParticleSystem()
		: CBaseRenderer(eComponentType::Particle)
		, mCount(100)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.f)
		, mBuffer(nullptr)
	{
		
	}

	CParticleSystem::~CParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}

	void CParticleSystem::Initialize()
	{
		mCS = CResources::Find<CParticleShader>(L"ParticleCS");

		std::shared_ptr<CMesh> point = CResources::Find<CMesh>(L"Pointmesh");
		SetMesh(point);

		// Material ¼¼ÆÃ
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<CTexture> tex = CResources::Find<CTexture>(L"bloodfx");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(-8.0f, -4.5f, 0.0f, 0.0f);
		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			particles[i].active = 1;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)mCount))
					, sin((float)i * (XM_2PI / (float)mCount)), 0.0f, 1.0f);

			particles[i].speed = 1.f;
		}
		for (size_t i = 50; i < mCount; i++)
		{
			particles[i].active = 0;
		}

		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);
	}

	void CParticleSystem::update()
	{
	}

	void CParticleSystem::fixedUpdate()
	{
		mCS->SetStrcutedBuffer(mBuffer);
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