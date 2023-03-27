#include "ParticleSystem.h"
#include "Mesh.h"

#include "GameObj.h"
#include "Transform.h"
#include "Mesh.h"
#include "Resources.h"
#include "StructedBuffer.h"

namespace dru
{
	CParticleSystem::CParticleSystem()
		: CBaseRenderer(eComponentType::Particle)
		, mCount(0)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.f)
	{
		std::shared_ptr<CMesh> rect = CResources::Find<CMesh>(L"Rectmesh");
		SetMesh(rect);

		// Material ¼¼ÆÃ
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"ParticleMaterial");
		SetMaterial(material);

		Particle particles[1000] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 16; x++)
			{
				particles[16 * y + x].position = startPos
					+ Vector4(x * 100.0f, y * 100.0f, 0.0f, 0.0f);
			}
		}

		mCount = 144;
		mBuffer = new CStructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::None, particles);
	}

	CParticleSystem::~CParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}

	void CParticleSystem::Initialize()
	{
	}

	void CParticleSystem::update()
	{
	}

	void CParticleSystem::fixedUpdate()
	{
	}

	void CParticleSystem::render()
	{
		GetOwner()->GetComponent<CTransform>()->SetConstantBuffer();
		mBuffer->SetPipeline(eShaderStage::VS, 15);
		mBuffer->SetPipeline(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);
	}

}