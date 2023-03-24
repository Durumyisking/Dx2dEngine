#include "ParticleSystem.h"
#include "Mesh.h"

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

	}

	CParticleSystem::~CParticleSystem()
	{
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
	}

}