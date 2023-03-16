#include "PlayerScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Animator.h"

namespace dru
{
	CPlayerScript::CPlayerScript()
		: mState(ePlayerState::Idle)
		, mAirTime (0.f)
		, mAttackTime(0.f)
		, mAttackCooldown(0.f)
		, mAttackDir(Vector3::Zero)
		, mbFirstAttack(true)
	{
	}

	CPlayerScript::~CPlayerScript()
	{
	}

	void CPlayerScript::Initialize()
	{
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();

		animator->GetCompleteEvent(L"Player_IdleToRun") = std::bind(&CPlayerScript::idletorun, this);
		animator->GetCompleteEvent(L"Player_RunToIdle") = std::bind(&CPlayerScript::runtoidle, this);
		animator->GetCompleteEvent(L"Player_Attack") = std::bind(&CPlayerScript::attacktoidle, this);

	}

	void CPlayerScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();
		Vector3 pos = transform->GetPosition();


#pragma region Run



		if (CInput::GetKeyState(eKeyCode::R) == eKeyState::DOWN)
		{
			Vector3 rot = transform->GetRotation();
			rot.z += 10.0f * CTimeMgr::DeltaTime();
			transform->SetRotation(rot);
		}

		if (CInput::GetKeyTap(eKeyCode::N_7))
			animator->Play(L"Player_Idle");
		if (CInput::GetKeyTap(eKeyCode::N_8))
			animator->Play(L"Player_IdleToRun");
		if (CInput::GetKeyTap(eKeyCode::N_9))
			animator->Play(L"Player_Run");
		if (CInput::GetKeyTap(eKeyCode::N_0))
			animator->Play(L"Player_RunToIdle");


		// idle to run
		if (CInput::GetKeyTap(eKeyCode::A))
		{
			GetOwner()->SetLeft();
			animator->Play(L"Player_IdleToRun", false);
			rigidebody->AddForce(transform->Right() * -500.f);
			mState = ePlayerState::IdleToRun;
		}
		if (CInput::GetKeyTap(eKeyCode::D))
		{
			GetOwner()->SetRight();
			animator->Play(L"Player_IdleToRun", false);
			rigidebody->AddForce(transform->Right() * 500.f);
			mState = ePlayerState::IdleToRun;
		}
		if (mState == ePlayerState::IdleToRun)
		{
			if (CInput::GetKeyDown(eKeyCode::A))
				rigidebody->AddForce(transform->Right() * -25.f);
			if (CInput::GetKeyDown(eKeyCode::D))
				rigidebody->AddForce(transform->Right() * 25.f);
		}

		// run
		if (mState == ePlayerState::Run)
		{
			if (CInput::GetKeyDown(eKeyCode::A))
				rigidebody->AddForce(transform->Right() * -30.f);

			if (CInput::GetKeyDown(eKeyCode::D))
				rigidebody->AddForce(transform->Right() * 30.f);
		}


		if (CInput::GetKeyUp(eKeyCode::D) || CInput::GetKeyUp(eKeyCode::A))
		{
			if (mState == ePlayerState::Idle)
				animator->Play(L"Player_Idle");

			if (mState == ePlayerState::Run || mState == ePlayerState::IdleToRun)
				animator->Play(L"Player_RunToIdle", false);
		}


#pragma endregion

#pragma region Jump

		// 지상일때
		if(!GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			if (CInput::GetKeyTap(eKeyCode::W))
			{
				// 점프
				rigidebody->AddVelocity(transform->Up() * 10.f);
				mState = ePlayerState::Jump;
			}
		}
		else
		{
			// 점프중에 키 일찍떼면 fall
			if (CInput::GetKeyUp(eKeyCode::W))
			{
				mState = ePlayerState::Fall;
			}
		}

		if (mState == ePlayerState::Jump)
		{
			mAirTime += CTimeMgr::DeltaTime();
			// 점프 시간 끝나면 Fall
			if (0.15f <= mAirTime)
			{
				mState = ePlayerState::Fall;
				mAirTime = 0.f;
			}
			else
			{
				if (CInput::GetKeyDown(eKeyCode::W))
				{
					rigidebody->AddVelocity(transform->Up() * 10.f);
				}
			}
		}



#pragma endregion


#pragma region Attack
		
		Vector3 MousePos = CInput::GetMousePosition();
		mAttackCooldown += CTimeMgr::DeltaTime();

		if (0.2f <= mAttackCooldown)
		{

			if (CInput::GetKeyTap(eKeyCode::LBTN) || CInput::GetKeyTap(eKeyCode::RBTN))
			{
				MousePos /= 100.f;

				if (MousePos.x < pos.x)
					GetOwner()->SetLeft();
				else
					GetOwner()->SetRight();

				if (CInput::GetKeyTap(eKeyCode::LBTN))
				{
					Vector3 vect;
					vect.x = MousePos.x - pos.x;
					vect.y = MousePos.y - pos.y;

					vect.Normalize();
					mAttackDir = vect;
					rigidebody->AddForce(vect * 200000.f);

					mState = ePlayerState::Attack;
					animator->Play(L"Player_Attack", false);
				}

				mAttackCooldown = 0.f;
			}
		}

		if (mState == ePlayerState::Attack)
		{
			mAttackTime += CTimeMgr::DeltaTime();

			if (0.3f <= mAttackTime)
			{
				mAttackTime = 0.f;
				mbFirstAttack = false;

			}
			else
			{
				if (mbFirstAttack)
					rigidebody->AddForce(mAttackDir * 200000.f);

			}
		}

#pragma endregion


		transform->SetPosition(pos);
		GetOwner()->Flip();


		//CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		//animator->GetCompleteEvent(L"idletorun")  = std::bind(&CPlayerScript::idletorun, this);



	}

	void CPlayerScript::fixedUpdate()
	{
	}

	void CPlayerScript::render()
	{
	}

	void CPlayerScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mbFirstAttack = true;

			if (mState == ePlayerState::Fall || mState == ePlayerState::Attack)
				mState = ePlayerState::Idle;

			GetOwner()->GetComponent<CRigidBody>()->SetGround();
			CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();
			Vector3 vel = rigidebody->GetVelocity();
			rigidebody->SetVelocity({ vel.x, 0.f, vel.z });
		}
	}

	void CPlayerScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CPlayerScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}

	}

	void CPlayerScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CPlayerScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CPlayerScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

	void CPlayerScript::idletorun()
	{
		mState = ePlayerState::Run;
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		animator->Play(L"Player_Run");

		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();
		if(GetOwner()->IsLeft())
			rigidebody->AddForce(transform->Right() * -100.f);
		else
			rigidebody->AddForce(transform->Right() * + 100.f);

	}

	void CPlayerScript::runtoidle()
	{
		mState = ePlayerState::Idle;
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		animator->Play(L"Player_Idle");
	}

	void CPlayerScript::attacktoidle()
	{
		if (GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			mState = ePlayerState::Idle;
			CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
			animator->Play(L"Player_Idle");
		}
		else
		{
			mState = ePlayerState::Idle;
			CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
			animator->Play(L"Player_Idle");
		}
	}

}