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
		coll->SetScale(Vector2(1.f, 1.f));

		CSpriteRenderer* SpriteRenderer = playerObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* animator = playerObj->AddComponent<CAnimator>(eComponentType::Animator);
		animator->Create(L"Player_Idle", Material->GetTexture(), { 0.f, 0.f }, { 40.f, 40.f }, Vector2::Zero, 10, 0.1f);
		animator->Create(L"Player_Run", Material->GetTexture(), { 10.f, 11.f }, { 36.f, 35.f }, Vector2::Zero, 10, 0.1f);
		animator->Create(L"Player_IdleToRun", Material->GetTexture(), { 396.f, 0.f }, { 44.f, 36.f }, Vector2::Zero, 4, 0.1f);
		animator->Create(L"Player_RunToIdle", Material->GetTexture(), { 622.f, 0.f }, { 52.f, 39.f }, Vector2::Zero, 4, 0.1f);
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