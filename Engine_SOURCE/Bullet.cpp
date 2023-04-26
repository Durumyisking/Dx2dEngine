#include "Bullet.h"
#include "Object.h"
#include "TimeMgr.h"
#include "BulletScript.h"


namespace dru
{
	CBullet::CBullet()
		:mTarget(nullptr)
		, mbReflected(false)
		, mDir(Vector3::Zero)
		, mBulletSpeed(1.f)
	{
	}

	CBullet::~CBullet()
	{
	}

	void CBullet::Initialize()
	{
		SetLayerType(eLayerType::Bullet);
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		SetScale({ 0.1f, 0.05f, 1.f });

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"Bullet");
		SpriteRenderer->SetMaterial(Material);

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_bullet");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.05f, 0.05f));

		CBulletScript* script = AddComponent<CBulletScript>(eComponentType::Script);
		script->Initialize();

		CLiveGameObj::Initialize();
	}

	void CBullet::update()
	{
		CLiveGameObj::update();
	}

	void CBullet::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBullet::render()
	{
		CLiveGameObj::render();
	}

}