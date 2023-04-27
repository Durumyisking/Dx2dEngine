#include "CopScript.h"
#include "Bullet.h"

namespace dru
{
	CCopScript::CCopScript()
		:mCopGun(nullptr)
		, mGunMuzzle(nullptr)
		, mGunFire(nullptr)

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
		if (GetOwner()->IsLeft())
		{
			mCopGun->SetLeft();
		}
		else
		{
			mCopGun->SetRight();
		}
		mCopGun->Flip();


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
		mCopGun = object::Instantiate<CGameObj>(eLayerType::MonsterGun,  GetOwner(), L"copgun");
		CSpriteRenderer* SpriteRenderer = mCopGun->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop_gun", L"SpriteShader");
		CResources::Insert<CMaterial>(L"cop_gunMat", Material);
		SpriteRenderer->SetMaterial(Material);
		mCopGun->SetPos(Vector3(0.2f, 0.2f, 0.f));
		mCopGun->SetScale(Vector3(0.06f, 0.06f, 1.f));
		mCopGun->RenderingBlockOn();

		mGunMuzzle = object::Instantiate<CGameObj>(eLayerType::MonsterGun, mCopGun, L"gunMuzzle");
		CCollider2D* coll = mGunMuzzle->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_mullze");
		coll->SetType(eColliderType::Rect);
		coll->SetScale({ 0.1f, 0.1f });
		mGunMuzzle->SetPos(mCopGun->GetPos());

	}
	void CCopScript::CreateBullet(Vector3 _StartPos)
	{

		CBullet* bullet = object::Instantiate<CBullet>(eLayerType::Bullet, L"Bullet");
		bullet->Initialize();
		bullet->SetTarget(mTarget);
		bullet->SetPos(_StartPos);

		CCollider2D* coll = bullet->GetComponent<CCollider2D>();
		coll->SetCenter({ bullet->GetCollPosX(), 0.f });
		Vector3 dir = mTarget->GetPos() - bullet->GetPos();
		dir.Normalize();
		dir.z = 0.f;

		// bullet의 진행방향으로 head를 돌린다.
		float angle = RotateToHead(dir);
		bullet->GetComponent<CTransform>()->SetRotationZ(angle);


		// collider의 위치도 변경해줘야한다.
		Vector3 collPos = { coll->GetCenter().x, coll->GetCenter().y, 0.f };
		collPos = RotateZ(collPos, angle);
		coll->SetCenter({ collPos.x, collPos.y });

		bullet->SetDir(dir);


		Vector3 pos = mGunMuzzle->GetPos();
		pos += (dir * 0.2325f);

		bullet->SetPos(pos);

	}
}
