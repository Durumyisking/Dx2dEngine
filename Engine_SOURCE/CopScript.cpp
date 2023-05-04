#include "CopScript.h"
#include "Bullet.h"
#include "Object.h"

using namespace dru::object;
namespace dru
{
	CCopScript::CCopScript()
		:mCopGun(nullptr)
		, mGunMuzzle(nullptr)
		, mGunFire(nullptr)
		, mGunSmoke(nullptr)
		, mAngle(0.f)

	{
	}
	CCopScript::~CCopScript()
	{
	}
	void CCopScript::Initialize()
	{
		mAttackRadius = 8.f;
		CreateGun();
		GetOrCreateGunFireObject();
		GetOrCreateGunSmokeObject();
		CMonsterScript::Initialize();
	}
	void CCopScript::update()
	{
		if (mState[(UINT)eMonsterState::Attack] == false)
		{
			mCopGun->RenderingBlockOn();
		}
		if(mTarget)
		{
			if (GetPlayerDistance() < mAttackRadius)
			{
				Vector3 dir = GetPlayerTowardDir(GetOwner());
				RotateGun(dir);
			}
		}
		GunFlip();

		CMonsterScript::update();
	}
	void CCopScript::fixedUpdate()
	{
		CMonsterScript::fixedUpdate();
	}
	void CCopScript::render()
	{
		CMonsterScript::render();
	}
	void CCopScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			if (35.f >= fabs(mAngle))
			{
				mCopGun->RenderingBlockOff();
				Vector3 pos = mCopGun->GetComponent<CTransform>()->GetWorldPosition();
				CreateBullet(pos);
				CMonsterScript::attack();
			}
			else
			{
				SetSingleState(eMonsterState::Idle);
			}
		}
	}
	void CCopScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}
	void CCopScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}
	void CCopScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}
	void CCopScript::SetMonsterAttack()
	{
		if (mAttackTimer >= 1.f)
		{
			SetSingleState(eMonsterState::Attack);
			attack();
		}
		else
		{
			runTrigger();
		}
	}
	void CCopScript::CreateGun()
	{
		// 총
		mCopGun = Instantiate<CGameObj>(eLayerType::MonsterGun,  GetOwner(), L"copgun");
		CSpriteRenderer* SpriteRenderer = mCopGun->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop_gun", L"SpriteShader");
		CResources::Insert<CMaterial>(L"cop_gunMat", Material);
		SpriteRenderer->SetMaterial(Material);
		mCopGun->SetPos(Vector3(0.2f, 0.2f, 0.f));
		mCopGun->SetScale(Vector3(0.06f, 0.06f, 1.f));
		mCopGun->RenderingBlockOn();

		// 총구
		mGunMuzzle = Instantiate<CGameObj>(eLayerType::MonsterGun, mCopGun ,L"gunMuzzle");

	}
	void CCopScript::CreateBullet(Vector3 _StartPos)
	{
		CBullet* bullet = Instantiate<CBullet>(eLayerType::Bullet, L"Bullet");
		bullet->Initialize();
		bullet->SetTarget(mTarget);
		bullet->SetPos(_StartPos);

		Vector3 dir = GetPlayerTowardDir(bullet);

		// bullet의 진행방향으로 head를 돌린다.
		Vector3 Right = { 1.f, 0.f, 0.f };
		mAngle = RotateToHead(dir, Right);

		RotateBullet(dir, bullet);

		// collider의 위치도 변경해줘야한다.
		RotateBulletCollider(bullet);

		PlayGunFire();
		PlayGunSmoke();
	}

	void CCopScript::GunFlip()
	{
		Vector3 CopGunPos = mCopGun->GetPos();
		if (GetOwner()->IsLeft())
		{
			CopGunPos.x = -0.2f;
			mCopGun->SetPos(CopGunPos);
			mCopGun->SetLeft();
			mGunFire->SetLeft();
			mGunSmoke->SetLeft();
		}
		else
		{
			CopGunPos.x = 0.2f;
			mCopGun->SetPos(CopGunPos);
			mCopGun->SetRight();
			mGunFire->SetRight();
			mGunSmoke->SetRight();
		}
		mCopGun->Flip();
		//mGunFire->Flip();
		//mGunSmoke->Flip();
	}

	void CCopScript::RotateBullet(Vector3 _Dir, CBullet* _Bullet)
	{
		_Bullet->GetComponent<CTransform>()->SetRotationZ(mAngle);
		_Bullet->SetDir(_Dir);

		Vector3 pos = mGunMuzzle->GetWorldPos();
		pos += (_Dir * 0.2325f); // 총구 위치 에서 미사일 나가게

		_Bullet->SetPos(pos);
	}
	void CCopScript::RotateBulletCollider(CBullet* _Bullet)
	{
		CCollider2D* coll = _Bullet->GetComponent<CCollider2D>();
		coll->SetCenter({ _Bullet->GetCollPosX(), 0.f });
		Vector3 collPos = { coll->GetCenter().x, coll->GetCenter().y, 0.f };
		collPos = RotateZ(collPos, mAngle);
		coll->SetCenter({ collPos.x, collPos.y });
	}
	void CCopScript::RotateGun(Vector3 _Dir)
	{
		float angleTemp = 0.f;
		Vector3 Right = { 1.f, 0.f, 0.f };

		if (GetOwner()->IsLeft())
		{
			Right.x = -1.f;
		}
		angleTemp = RotateToHead(_Dir, Right);
		mAngle = RotateToHead(_Dir, Right);
		if (GetOwner()->IsLeft())
		{
			angleTemp *= -1.f;
		}

		if (35.f <= fabs(angleTemp))
			return;

		mCopGun->GetComponent<CTransform>()->SetRotationZ(angleTemp);

		// 총구도 돌려준다.
		Vector3 newMuzzlePos = RotateZ(mGunMuzzle->GetPos(), angleTemp);
		mGunMuzzle->SetPos(newMuzzlePos);
	}
	void CCopScript::InitializeGunFireComponent()
	{
		CGameObj* GunFireObject = GetOrCreateGunFireObject();
		if (GunFireObject)
		{
			GunFireObject->SetScale({ 0.5f, 0.5f, 1.f });

			std::shared_ptr<CTexture> GunFireObjectTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = GunFireObject->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"GunFireMat");
				if (Material)
				{
					GunFireObjectTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			if (GunFireObjectTexture)
			{
				CAnimator* GunFireObjectAnimator = GunFireObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (GunFireObjectAnimator)
				{
					GunFireObjectAnimator->Create(L"gunfire", GunFireObjectTexture, { 0.f, 0.f }, { 50.f, 42.f }, Vector2::Zero, 8, { 50.f, 42.f }, 0.05f);
					GunFireObjectAnimator->GetCompleteEvent(L"gunfire") = std::bind(&CCopScript::GunFireComplete, this);
				}
				else
				{
					assert(false);
				}
			}
			GunFireObject->RenderingBlockOn();

		}
	}
	void CCopScript::InitializemGunSmokeComponent()
	{
		CGameObj* GunSmokeObject = GetOrCreateGunSmokeObject();
		if (GunSmokeObject)
		{
			GunSmokeObject->SetScale({ 0.5f, 0.5f, 1.f });

			std::shared_ptr<CTexture> GunSmokeObjectTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = GunSmokeObject->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"GunSmokeMat");
				if (Material)
				{
					GunSmokeObjectTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			if (GunSmokeObjectTexture)
			{
				CAnimator* GunSmokeObjectAnimator = GunSmokeObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (GunSmokeObjectAnimator)
				{
					GunSmokeObjectAnimator->Create(L"gunsmoke", GunSmokeObjectTexture, { 0.f, 0.f }, { 30.f, 22.f }, Vector2::Zero, 10, { 30.f, 22.f }, 0.05f);
					GunSmokeObjectAnimator->GetCompleteEvent(L"gunsmoke") = std::bind(&CCopScript::GunSmokeComplete, this);
				}
				else
				{
					assert(false);
				}
			}
			GunSmokeObject->RenderingBlockOn();
		}
	}

	void CCopScript::GunFireComplete()
	{
		mGunFire->RenderingBlockOn();
	}
	void CCopScript::GunSmokeComplete()
	{
		mGunSmoke->RenderingBlockOn();
	}
	void CCopScript::PlayGunFire()
	{
		CGameObj* GunFireObject = GetOrCreateGunFireObject();
		if (GunFireObject)
		{
			GunFireSmokePositioning(GunFireObject);

			CAnimator* GunFireObjectAnimator = GunFireObject->GetComponent<CAnimator>();
			if (GunFireObjectAnimator)
			{
				GunFireObject->RenderingBlockOff();
				GunFireObjectAnimator->Play(L"gunfire", false);
			}
			else
			{
				assert(false);
			}
		}
	}
	void CCopScript::PlayGunSmoke()
	{
		CGameObj* GunSmokeObject= GetOrCreateGunSmokeObject();
		if (GunSmokeObject)
		{
			GunFireSmokePositioning(GunSmokeObject);

			CAnimator* GunSmokeObjectAnimator = GunSmokeObject->GetComponent<CAnimator>();
			if (GunSmokeObjectAnimator)
			{
				GunSmokeObject->RenderingBlockOff();
				GunSmokeObjectAnimator->Play(L"gunsmoke", false);
			}
			else
			{
				assert(false);
			}
		}
	}
	void CCopScript::GunFireSmokePositioning(CGameObj* GunFireOrSmoke)
	{
		Vector3 gunPos = mGunMuzzle->GetWorldPos();
		float angle = mAngle;
		if (mCopGun->IsLeft())
		{
			gunPos.x -= 0.5f;
		}
		else
		{
			gunPos.x += 0.5f;
			angle *= -0.1f;
		}
		gunPos.y += 0.05f;

		GunFireOrSmoke->GetComponent<CTransform>()->SetRotationZ(mAngle);
		GunFireOrSmoke->SetPos(gunPos);
	}
	CGameObj* CCopScript::GetOrCreateGunFireObject()
	{
		if (!mGunFire)
		{
			// create
			mGunFire = Instantiate<CGameObj>(eLayerType::FX, L"gunfire");
			if (mGunFire)
			{
				// intialize
				InitializeGunFireComponent();
			}
		}

		return mGunFire;
	}
	CGameObj* CCopScript::GetOrCreateGunSmokeObject()
	{
		if (!mGunSmoke)
		{
			// create
			mGunSmoke = Instantiate<CGameObj>(eLayerType::FX, L"gunsmoke");
			if (mGunSmoke)
			{
				// intialize
				InitializemGunSmokeComponent();
			}
		}

		return mGunSmoke;
	}
}
