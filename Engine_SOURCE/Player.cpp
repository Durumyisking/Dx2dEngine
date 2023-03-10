#include "Player.h"
#include "PlayerScript.h"
#include "RigidBody.h"

namespace dru
{
	CPlayer::CPlayer()
	{
		SetLayerType(eLayerType::Player);
		this->AddComponent<CPlayerScript>(eComponentType::Script);

		CGameObj* playerObj = dynamic_cast<CGameObj*>(this);

		CRigidBody* rigidbody = playerObj->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = playerObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 1.f));

		CSpriteRenderer* SpriteRenderer = playerObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		SpriteRenderer->SetMaterial(Material);
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