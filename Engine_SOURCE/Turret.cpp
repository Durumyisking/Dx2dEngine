#include "Turret.h"
#include "Object.h"
#include "ParticleSystem.h"
#include "Floor.h"

namespace dru
{
	CTurret::CTurret()
		:mBeam(nullptr)
		, mParticle(nullptr)
		, mDestinationFloor(nullptr)
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
	void CTurret::AdjustLaserTransform()
	{
		Vector3 TurretPos = mBeam->GetWorldPos();
		float Gap = GapBetweenFloorAndTurret();
		TurretPos.y -= Gap / 2.f;
		TurretPos.z += 0.1f;
		ChangeBeamSize(Gap);
		ChangeBeamPos(TurretPos);
	}

	void CTurret::AdjustAimParticle()
	{
		UINT newCount = 0;
		float Gap = GapBetweenFloorAndTurret();
		newCount = static_cast<UINT>(Gap / SINGLE_LASER_GAP);

		float newLiefTime = 0.f;
		newLiefTime = Gap / SINGLE_LASER_LIFETIME_GAP;

		CParticleSystem* particleSystem = mParticle->GetComponent<CParticleSystem>();
		particleSystem->SetMaxParticleCount(newCount);
		particleSystem->SetMaxLifeTime(newLiefTime);
	}

	float CTurret::GapBetweenFloorAndTurret()
	{
		float floorPos = mDestinationFloor->GetWorldPos().y;
		Vector3 TurretPos = GetWorldPos();
		float Gap = fabs(floorPos - TurretPos.y);
		return Gap;
	}


	void CTurret::MakeBeam()
	{
		InitializeParticleSystem();

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
	void CTurret::InitializeParticleSystem()
	{
		mParticle = object::Instantiate<CGameObj>(eLayerType::Particle);
		mParticle->SetName(L"LaserTurretParticleSystem");
		mParticle->SetPos(GetWorldPos());
		CParticleSystem* particleSystem = mParticle->AddComponent<CParticleSystem>(eComponentType::Particle);

		// Material ¼¼ÆÃ
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"LaserTurretParticleMat");
		particleSystem->SetMaterial(Material);

		Vector3 pos = mParticle->GetWorldPos();
		Vector4 startPos = Vector4(pos.x, pos.y, pos.z, 1.f);
		Vector4 direction = Vector4{ 0.f,-1.f,0.f,1.f };
		particleSystem->MakeParticleBufferData(startPos, direction, 12, 1.f, 0.f, 0);
		particleSystem->SetMaxLifeTime(4.5f);
		particleSystem->SetStartColor(RED);
		particleSystem->SetStartPosition(GetWorldPos());
		particleSystem->SetStartScale(Vector3(0.05f, 0.1f, 0.f));

		renderer::ParticleSystemCB cb = {};
		cb.radian = 0.f;	
		particleSystem->MakeConstantBufferData(L"AimParticleCS", cb);

		particleSystem->SetMaxElapsedTime(5.f);
	}
}
