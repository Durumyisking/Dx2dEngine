#include "Player.h"
#include "PlayerScript.h"
#include "CameraScript.h"
#include "PlayerAfterImage.h"
#include "GameObj.h"
#include "Object.h"
#include "ParticleSystem.h"

namespace dru
{
	CPlayer::CPlayer()
		: mbPlayerDead(false)
		, mParticle(nullptr)

	{
		SetLayerType(eLayerType::Player);
		SetScale(Vector3(1.25f, 1.25f, 1.f));

		renderer::mainCamera->GetCamScript()->SetPlayer(this);


		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_player");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));


		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PlayerMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Player_Idle", Material->GetTexture(), { 2718.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Run", Material->GetTexture(), { 4954.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_IdleToRun", Material->GetTexture(), { 3342.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_RunToIdle", Material->GetTexture(), { 5578.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 5, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_PreCrouch", Material->GetTexture(), { 6696.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Crouch", Material->GetTexture(), { 2602.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_PostCrouch", Material->GetTexture(), { 6572.f, 0.f }, { 62.f, 50.f },Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Roll", Material->GetTexture(), { 6138.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_WallSlide", Material->GetTexture(), { 5952.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_WallSlideFast", Material->GetTexture(), { 6076.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_WallKick", Material->GetTexture(), { 6820.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 11, { 50.f, 50.f }, 0.02f);
		mAnimator->Create(L"Player_Jump", Material->GetTexture(), { 3584.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Fall", Material->GetTexture(), { 1108.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Attack", Material->GetTexture(), { 0.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Dead", Material->GetTexture(), { 1364.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 12, { 50.f, 50.f }, 0.05f);
		//mAnimator->Create(L"Player_DeadStart", Material->GetTexture(), { 1364.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 2, { 50.f, 50.f }, 0.5f);
		//mAnimator->Create(L"Player_DeadAir", Material->GetTexture(), { 1488.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		//mAnimator->Create(L"Player_DeadEnd", Material->GetTexture(), { 1736.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.05f);
		mAnimator->Play(L"Player_Idle");

		AddComponent<CPlayerScript>(eComponentType::Script);

		{
			mParticle = object::Instantiate<CGameObj>(eLayerType::Particle, L"PlayerParticle");
			mParticle->SetName(L"PlayerParticleSystem");
			mParticle->SetPos(GetWorldPos());
			CParticleSystem* particleSystem = mParticle->AddComponent<CParticleSystem>(eComponentType::Particle);

			// Material ����
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PlayerParticleMat");
			particleSystem->SetMaterial(Material);

			Vector3 pos = mParticle->GetWorldPos();
			Vector4 startPos = Vector4(pos.x, pos.y, pos.z, 1.f);
			Vector4 direction = Vector4{ 0.f,-1.f,0.f,1.f };
			particleSystem->MakeParticleBufferData(startPos, direction, 100, 5.f, 0.f, 0);
			particleSystem->SetMaxLifeTime(2.f);
			particleSystem->SetStartColor(YELLOW);
			particleSystem->SetEndColor(ORANGE);
			particleSystem->SetStartPosition(GetWorldPos());
			particleSystem->SetStartScale(Vector3(0.1f, 0.1f, 0.f));
			particleSystem->SetmParticleCountInFrame(20);
			renderer::ParticleSystemCB cb = {};
			cb.radian = 0.f;
			particleSystem->MakeConstantBufferData(L"LaserParticleCS", cb);

			particleSystem->SetMaxElapsedTime(5.f);
		}
	}

	CPlayer::~CPlayer()
	{

	}

	void CPlayer::Initialize()
	{
		

		CLiveGameObj::Initialize();
	}

	void CPlayer::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(true, 50);
		}

		CLiveGameObj::update();
	}

	void CPlayer::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CPlayer::render()
	{
		
		CLiveGameObj::render();
	}

}