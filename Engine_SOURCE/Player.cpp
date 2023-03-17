#include "Player.h"
#include "PlayerScript.h"
#include "RigidBody.h"
#include "Animator.h"

namespace dru
{
	CPlayer::CPlayer()
	{
		SetLayerType(eLayerType::Player);
		this->AddComponent<CPlayerScript>(eComponentType::Script);

		CGameObj* playerObj = dynamic_cast<CGameObj*>(this);

		CRigidBody* rigidbody = playerObj->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = playerObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_player");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.3f, 0.6f));

		CSpriteRenderer* SpriteRenderer = playerObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* animator = playerObj->AddComponent<CAnimator>(eComponentType::Animator);
		animator->Create(L"Player_Idle", Material->GetTexture(), { 2718.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		animator->Create(L"Player_Run", Material->GetTexture(), { 4954.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		animator->Create(L"Player_IdleToRun", Material->GetTexture(), { 3342.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		animator->Create(L"Player_RunToIdle", Material->GetTexture(), { 5578.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 5, { 50.f, 50.f }, 0.1f);
		animator->Create(L"Player_Jump", Material->GetTexture(), { 3584.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		animator->Create(L"Player_Fall", Material->GetTexture(), { 1108.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		animator->Create(L"Player_Attack", Material->GetTexture(), { 0.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 7, { 50.f, 50.f }, 0.01f);
		animator->Play(L"Player_Idle");

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