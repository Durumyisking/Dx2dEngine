#include "MonsterScript.h"
#include "Transform.h"
#include "TimeMgr.h"
#include "Object.h"
#include "SlashScript.h"
#include "BodyShadeScript.h"
#include "Input.h"
#include "Monster.h"

namespace dru
{
	CMonsterScript::CMonsterScript()
		: mState{}
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mTarget(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
		, mHitDir(Vector3::Zero)
		, mbOnWall(false)
		, mbDead(false)
		, mbDeleteOn(false)
		, mHitTimer(0.f)
		, mAttackTimer(1.f)
		, mMonsterName{}
	{

	}

	CMonsterScript::~CMonsterScript()
	{
	}

	void CMonsterScript::Initialize()
	{
		mState[(UINT)eMonsterState::Idle] = true;


		mAnimator->GetCompleteEvent(mMonsterName + L"_DeadGround") = std::bind(&CMonsterScript::deadgroundComplete, this);

	}

	void CMonsterScript::update()
	{
		mPos = mTransform->GetPosition();
		mAttackTimer += CTimeMgr::DeltaTime();

		if (mState[(UINT)eMonsterState::Run] == true)
		{
			run();
		}
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			// attack();
		}
		mMoveDir = mRigidbody->GetVelocity();
		mMoveDir.Normalize();

		dead();


		mTransform->SetPosition(mPos);
		if (mMoveDir.x > 0.f)
		{
			GetOwner()->SetRight();
		}
		else if (mMoveDir.x < 0.f)
		{
			GetOwner()->SetLeft();
		}
		
		GetOwner()->Flip();
	}

	void CMonsterScript::fixedUpdate()
	{
	}

	void CMonsterScript::render()
	{
	}

	void CMonsterScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mRigidbody->SetGround();

			if (mbDead)
			{
				mState[(UINT)eMonsterState::DieAirUp] = false;
				mState[(UINT)eMonsterState::DieGround] = true;
				mAnimator->Play(mMonsterName+ L"_DeadGround", false);
			}

		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = true;

			wallBound(_oppo);
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			hitSlash();
		}

		else if (L"col_outWallside" == _oppo->GetName() || L"col_outWall" == _oppo->GetName())
		{
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ 0.f, vel.y, 0.f });
		}
	}

	void CMonsterScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = false;

			Vector3 vel = mRigidbody->GetVelocity();
			Vector3 Mvel = mRigidbody->GetMaxVelocity();
			mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);

		}
	}

	void CMonsterScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::HitAddForce()
	{
		Vector3 MousePos = CInput::GetMousePosition();
		MousePos /= 100.f;

		Vector3 monsterPos = GetOwner()->GetPos();

		mHitDir = MousePos - monsterPos;
		mHitDir.Normalize();

		mRigidbody->SetMaxVelocity({ 5.f, 5.f, 0.f });
	}



	void CMonsterScript::CreateBodySlash()
	{
		CGameObj* bodySlash = object::Instantiate<CGameObj>(eLayerType::FX, L"BodySlash");
		CSpriteRenderer* SpriteRenderer = bodySlash->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		bodySlash->SetPos(GetOwner()->GetPos());

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BodySlashMat");
		SpriteRenderer->SetMaterial(Material);
		SpriteRenderer->MulColor(Vector4(0.917f, 0.796f, 0.403f, 1.f));

		CAnimator* mAnimator = bodySlash->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"BodySlash", Material->GetTexture(), { 500.f, 0.f }, { 100.f, 100.f }, Vector2::Zero, 5, { 80.f, 80.f }, 0.05f);
		mAnimator->Play(L"BodySlash", false);

		CBodyShadeScript* script = bodySlash->AddComponent<CBodyShadeScript>(eComponentType::Script);
		script->Initialize();
		script->SetMonster(GetOwner());
	}

	void CMonsterScript::run()
	{

		if (mTarget && !mbDead)
		{
			Vector3 vPos = GetOwner()->GetPos();
			Vector3 vTargetPos = mTarget->GetPos();
			Vector3 vDir = Vector3(vTargetPos.x - vPos.x, 0.f, 0.f);
			vDir.Normalize();
			GetOwner()->GetComponent<CRigidBody>()->AddForce(vDir * 50.f);
		}
		
	}

	void CMonsterScript::attack()
	{

		mAnimator->Play(GetOwner()->GetName() + L"_Attack", false);
		mAttackTimer = 0.f;
	}

	void CMonsterScript::hitSlash()
	{
		if (!mbDead)
		{
			mState.reset();
			HitAddForce();

			mbDead = true;
			mState.reset();
			mState[(UINT)eMonsterState::DieAirUp] = true;


			// timeslow
			CTimeMgr::BulletTime(0.25f);

			// CamShake
			ShakeParams sp = {};
			sp.duration = 0.5f;
			sp.magnitude = 0.0125f;
			renderer::mainCamera->GetCamScript()->Shake(sp);

			GetOwnerType<CMonster>()->SetRayDie();

			CreateSlashShade();
			CreateBodySlash();
		}
	}

	void CMonsterScript::wallBound(CCollider2D* _oppo)
	{

			Vector3 vel = mRigidbody->GetVelocity();
			Vector3 Mvel = mRigidbody->GetMaxVelocity();
			mRigidbody->SetMaxVelocity({ 1.f, Mvel.y, Mvel.z });

			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
			{
				mRigidbody->SetVelocity({ 1.f, vel.y, vel.z });
			}
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
			{
				mRigidbody->SetVelocity({ -1.f, vel.y, vel.z });
			}
	}

	void CMonsterScript::dead()
	{
		if (mbDead)
		{
			if (mState[(UINT)eMonsterState::DieGround] == false)
			{
				mHitTimer += CTimeMgr::DeltaTime();

				if (mHitTimer <= 0.25f)
				{
					mRigidbody->AddVelocity({ mHitDir.x * 0.5f, mHitDir.y * 0.5f, 0.f });
				}
				mMoveDir = mRigidbody->GetVelocity();
				mMoveDir.Normalize();

				if (mMoveDir.y > 0.f)
				{
					mState[(UINT)eMonsterState::DieAirUp] = true;
					mAnimator->Play(mMonsterName + L"_DeadAirUp");
				}
				else if (mMoveDir.y < 0.f)
				{
					mState[(UINT)eMonsterState::DieAirDown] = true;
					mAnimator->Play(mMonsterName + L"_DeadAirDown");
				}
				else if (mMoveDir.y == 0.f)
				{
					mState[(UINT)eMonsterState::DieGround] = true;
					mAnimator->Play(mMonsterName + L"_DeadGround", false);
				}

			}
		}
	}

	void CMonsterScript::deadgroundComplete()
	{
		GetOwner()->GetComponent<CCollider2D>()->RenderingOff();

		if (mbDeleteOn)
		{
			dynamic_cast<CMonster*>(GetOwner())->Die();
		}
	}

	void CMonsterScript::makeSlash(Vector2 _vLT, Vector2 _FrameSize, UINT _AnimSize, Vector2 _Ratio)
	{
		CGameObj* SlashObj = object::Instantiate<CGameObj>(eLayerType::FX, GetOwner()->GetName() + L"_Slash");
		SlashObj->SetScale({ 1.f, 1.f, 1.f });

		CCollider2D* coll = SlashObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_Monster_Slash");
		coll->Initialize();
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.5f, 0.5f));


		Vector3 slashpos = {}; 
		if (mTarget->GetPos().x < GetOwnerPos().x)
		{
			SlashObj->SetLeft();
			GetOwner()->SetLeft();
			slashpos = Vector3{ GetOwner()->GetPos().x - 0.5f, GetOwner()->GetPos().y, 0.f };
		}
		else
		{
			SlashObj->SetRight();
			GetOwner()->SetRight();
			slashpos = Vector3{ GetOwner()->GetPos().x + 0.5f, GetOwner()->GetPos().y, 0.f };
		}
		SlashObj->SetPos(slashpos);

		GetOwner()->Flip();
		SlashObj->Flip();




		CSpriteRenderer* SpriteRenderer = SlashObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(GetOwner()->GetName() + L"Mat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = SlashObj->AddComponent<CAnimator>(eComponentType::Animator);
		std::wstring animname = GetOwner()->GetName() + L"_SlashAnim";
		mAnimator->Create(animname, Material->GetTexture(), _vLT, _FrameSize, Vector2::Zero, _AnimSize, _Ratio, 0.025f);
		mAnimator->Play(animname, false);

		SlashObj->AddComponent<CSlashScript>(eComponentType::Script)->Initialize();
	}

}