#include "Player.h"
#include "PlayerScript.h"
#include "RigidBody.h"
#include "Animator.h"
#include "CameraScript.h"

namespace dru
{
	CPlayer::CPlayer()
	{
		SetLayerType(eLayerType::Player);

		renderer::mainCamera->GetCamScript()->SetPlayer(this);

		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_player");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));


		CSpriteRenderer* SpriteRenderer = this->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
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
		mAnimator->Play(L"Player_Idle");

		this->AddComponent<CPlayerScript>(eComponentType::Script);

	}

	CPlayer::~CPlayer()
	{
	}

	void CPlayer::Initialize()
	{
		CGameObj::Initialize();
	}

	void CPlayer::update()
	{
		CGameObj::update();
	}

	void CPlayer::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CPlayer::render()
	{
		CGameObj::render();
	}

}