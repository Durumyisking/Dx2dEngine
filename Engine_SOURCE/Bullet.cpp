#include "Bullet.h"
#include "Object.h"
#include "TimeMgr.h"
#include "BulletScript.h"


namespace dru
{
	CBullet::CBullet()
		: mbReflected(false)
		, mDir(Vector3::Zero)
		, mBulletSpeed(20.f)
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
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		SetScale({ 0.025f, 0.025f, 1.f }); //  / 17.f

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"Bullet");
		SpriteRenderer->SetMaterial(Material);

		CAudioSource* audioSource = AddComponent<CAudioSource>(eComponentType::AudioSource);
		audioSource->AddClipByKey(L"bullethit1");
		audioSource->AddClipByKey(L"bullethit2");
		audioSource->AddClipByKey(L"bullethit3");
		audioSource->AddClipByKey(L"bullet_die");
		audioSource->AddClipByKey(L"bullet_slash");


		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_bullet");
		coll->SetType(eColliderType::Rect);
		float collScaleX = 1.f / 17.f;
		coll->SetScale(Vector2(collScaleX, 1.f));

		CBulletScript* script = AddComponent<CBulletScript>(eComponentType::Script);
		script->Initialize();

		RenderingBlockOn();

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

	void CBullet::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

	void CBullet::SetGunfired(bool _flag)
	{
		GetScript<CBulletScript>()->SetGunfired(_flag);
	}

	void CBullet::RotateBullet(Vector3 _Dir, Vector3 _Pos, float _Angle)
	{
		GetScript<CBulletScript>()->RotateBullet(_Dir, _Pos, _Angle);
	}

	void CBullet::RotateBulletCollider(float _Angle)
	{
		GetScript<CBulletScript>()->RotateBulletCollider(_Angle);
	}

}