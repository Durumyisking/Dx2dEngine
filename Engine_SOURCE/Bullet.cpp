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
		, mBulletSpeed(0.1f)
		, collScaleX(1.f / 17.f)
		, collPosX(collScaleX * 3.5f)

	{
	}

	CBullet::~CBullet()
	{
	}

	void CBullet::Initialize()
	{
		SetLayerType(eLayerType::Bullet);
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		SetScale({ 0.025f, 0.025f, 1.f }); //  / 17.f

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"Bullet");
		SpriteRenderer->SetMaterial(Material);

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_bullet");
		coll->SetType(eColliderType::Rect);
		float collScaleX = 1.f / 17.f;
		coll->SetScale(Vector2(collScaleX, 1.f));

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