#include "MonsterScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"
#include "Input.h"

namespace dru
{
	CMonsterScript::CMonsterScript()
		: mState{}
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
		, mHitDir(Vector3::Zero)
		, mbOnWall(false)
		, mbDead(false)
		, mbDeleteOn(false)
		, mHitTimer(0.f)
		, mMonsterName{}
	{

	}

	CMonsterScript::~CMonsterScript()
	{
	}

	void CMonsterScript::Initialize()
	{
		mState[(UINT)eMonsterState::Idle] = true;

		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mTransform = GetOwner()->GetComponent<CTransform>();
		mMonsterName = GetOwner()->GetName();

		mAnimator->GetCompleteEvent(mMonsterName + L"_DeadGround") = std::bind(&CMonsterScript::deadgroundComplete, this);
	}

	void CMonsterScript::update()
	{
		mPos = mTransform->GetPosition();
		mMoveDir = mRigidbody->GetVelocity();
		mMoveDir.Normalize();


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
			Vector3 vel = mRigidbody->GetVelocity();
//			mRigidbody->SetMaxVelocity({ 5.f, 0.f, vel.z });
//			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });

			if (mbDead)
			{
				mState[(UINT)eMonsterState::DieGround] = true;
				mAnimator->Play(mMonsterName+ L"_DeadGround", false);
			}

		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = true;
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!mbDead)
			{
				mState.reset();
				HitAddForce();

				mbDead = true;

				// timeslow
				CTimeMgr::BulletTime(0.25f);

				// CamShake
				ShakeParams sp = {};
				sp.duration = 1.f;
				sp.magnitude = 0.025f;
				renderer::mainCamera->GetCamScript()->Shake(sp);

			}
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

	void CMonsterScript::deadgroundComplete()
	{
		GetOwner()->GetComponent<CCollider2D>()->RenderingOff();
		if (mbDeleteOn)
		{
			GetOwner()->Die();
		}
	}

}