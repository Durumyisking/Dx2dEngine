#include "Turret.h"
#include "Object.h"
#include "ParticleSystem.h"

namespace dru
{
	CTurret::CTurret()
		:mBeam(nullptr)
	{
		SetLayerType(eLayerType::None);

		CSpriteRenderer* renderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		renderer->SetMaterialByKey(L"laserTurretMat");
	}
	CTurret::~CTurret()
	{
	}
	void CTurret::Initialize()
	{
		MakeBeam();

		CLiveGameObj::Initialize(); 
	}
	void CTurret::update()
	{
		CLiveGameObj::update();
	}
	void CTurret::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}
	void CTurret::render()
	{
		CLiveGameObj::render();
	}
	void CTurret::ChangeBeamPos(Vector3 _Pos)
	{
		mBeam->SetPosAbs(_Pos);
	}
	void CTurret::ChangeBeamSize(float _ScaleY)
	{
		mBeam->GetComponent<CTransform>()->SetScaleY(_ScaleY);
	}
	void CTurret::MakeBeam()
	{

		{
			CGameObj* particle = object::Instantiate<CGameObj>(eLayerType::Particle);
			particle->SetName(L"PARTICLE");
			particle->SetPos(GetWorldPos());
			CParticleSystem* particleSystem = particle->AddComponent<CParticleSystem>(eComponentType::Particle);

			// Material ¼¼ÆÃ
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"LaserTurretParticleMat");
			particleSystem->SetMaterial(Material);

			Vector3 pos = particle->GetWorldPos();
			Vector4 startPos = Vector4(pos.x, pos.y, pos.z, 1.f);
			Vector4 direction = Vector4{ 0.f,-1.f,0.f,1.f };
			particleSystem->MakeParticleBufferData(startPos, direction, 7, 1.f, 0.f, 0);
			renderer::ParticleSystemCB cb = {};
			cb.radian = 0.f;
			cb.maxLifeTime = 4.f;
			cb.startColor = RED;
			cb.startSize = Vector4(0.05f, 0.1f, 0.f, 1.f);

			particleSystem->MakeConstantBufferData(L"AimParticleCS", cb);

			particleSystem->SetMaxElapsedTime(5.f);

		}


		mBeam = object::Instantiate<CGameObj>(eLayerType::Bullet, L"LaserBeam");
		mBeam->SetPosAbs(GetWorldPos());

		CSpriteRenderer* renderer = mBeam->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"laserBeamMat");
		renderer->SetMaterial(Material);
		renderer->ChangeColor(RED);

		CCollider2D* collider = mBeam->AddComponent<CCollider2D>(eComponentType::Collider);
		collider->Initialize();
		collider->SetName(L"col_beam");
		collider->SetType(eColliderType::Rect);
	
		mBeam->GetComponent<CTransform>()->SetScaleX(0.125f);
		mBeam->RenderingBlockOn();

	}
}
