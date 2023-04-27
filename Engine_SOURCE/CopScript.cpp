#include "CopScript.h"
#include "Bullet.h"

namespace dru
{
	CCopScript::CCopScript()
		:mCopGun(nullptr)
		, mGunMuzzle(nullptr)
		, mGunFire(nullptr)
		, mGunSmoke(nullptr)
		, mBulletReflect(nullptr)
		, mAngle(0.f)

	{
	}
	CCopScript::~CCopScript()
	{
	}
	void CCopScript::Initialize()
	{
		mAttackRadius = 5.f;
		CreateGun();

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
			mCopGun->RenderingBlockOff();

			CreateBullet(mCopGun->GetPos());

			CMonsterScript::attack();
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
		mCopGun = object::Instantiate<CGameObj>(eLayerType::MonsterGun,  GetOwner(), L"copgun");
		CSpriteRenderer* SpriteRenderer = mCopGun->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop_gun", L"SpriteShader");
		CResources::Insert<CMaterial>(L"cop_gunMat", Material);
		SpriteRenderer->SetMaterial(Material);
		mCopGun->SetPos(Vector3(0.2f, 0.2f, 0.f));
		mCopGun->SetScale(Vector3(0.06f, 0.06f, 1.f));
		mCopGun->RenderingBlockOn();

		// 총구
		mGunMuzzle = object::Instantiate<CGameObj>(eLayerType::MonsterGun, mCopGun, L"gunMuzzle");
//		mGunMuzzle->SetPos({0.5f, -3.f, 3.f});
		CCollider2D* coll = mGunMuzzle->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_mullze");
		coll->SetType(eColliderType::Rect);
		coll->SetScale({ 0.1f, 0.1f });

	}
	void CCopScript::CreateBullet(Vector3 _StartPos)
	{
		CBullet* bullet = object::Instantiate<CBullet>(eLayerType::Bullet, L"Bullet");
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

	}

	void CCopScript::GunFlip()
	{
		Vector3 CopGunPos = mCopGun->GetPos();
		if (GetOwner()->IsLeft())
		{
			CopGunPos.x = -0.2f;
			mCopGun->SetPos(CopGunPos);
			mCopGun->SetLeft();
		}
		else
		{
			CopGunPos.x = 0.2f;
			mCopGun->SetPos(CopGunPos);
			mCopGun->SetRight();
		}
		mCopGun->Flip();
	}

	void CCopScript::RotateBullet(Vector3 _Dir, CBullet* _Bullet)
	{
		_Bullet->GetComponent<CTransform>()->SetRotationZ(mAngle);
		_Bullet->SetDir(_Dir);

		Vector3 pos = mGunMuzzle->GetPos();
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
		if (GetOwner()->IsLeft())
		{
			angleTemp *= -1.f;
		}

		if (35.f < fabs(angleTemp))
			return;

		mCopGun->GetComponent<CTransform>()->SetRotationZ(angleTemp);

		// 총구도 돌려준다.
		//Vector3 newMuzzlePos =  RotateZ(mGunMuzzle->GetPos(), mAngle);
		//mGunMuzzle->SetPos(newMuzzlePos);

	}
}
