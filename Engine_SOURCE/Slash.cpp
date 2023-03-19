#include "Slash.h"
#include "Animator.h"

namespace dru
{
	CSlash::CSlash()
	{
		SetLayerType(eLayerType::FX);

		CGameObj* playerObj = dynamic_cast<CGameObj*>(this);

		CCollider2D* coll = playerObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_" + GetName() + L"_slash");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.3f, 0.3f));

		CSpriteRenderer* SpriteRenderer = playerObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = playerObj->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Player_Idle", Material->GetTexture(), { 2718.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Run", Material->GetTexture(), { 4954.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_IdleToRun", Material->GetTexture(), { 3342.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_RunToIdle", Material->GetTexture(), { 5578.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 5, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_PreCrouch", Material->GetTexture(), { 6696.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Crouch", Material->GetTexture(), { 2602.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_PostCrouch", Material->GetTexture(), { 6572.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Roll", Material->GetTexture(), { 6138.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Jump", Material->GetTexture(), { 3584.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Fall", Material->GetTexture(), { 1108.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Attack", Material->GetTexture(), { 0.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Play(L"Player_Idle");

		this->AddComponent<CPlayerScript>(eComponentType::Script);
	}

	CSlash::~CSlash()
	{
	}

	void CSlash::Initialize()
	{
	}

	void CSlash::update()
	{
	}

	void CSlash::fixedUpdate()
	{
	}

	void CSlash::render()
	{
	}


}