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
		: mState{}
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

		animator->GetFrameEvent(L"Player_IdleToRun", 1) = std::bind(&CPlayerScript::idletorunFrame, this);
		animator->GetCompleteEvent(L"Player_IdleToRun") = std::bind(&CPlayerScript::idletorun, this);
		animator->GetCompleteEvent(L"Player_RunToIdle") = std::bind(&CPlayerScript::runtoidle, this);
		animator->GetCompleteEvent(L"Player_Attack") = std::bind(&CPlayerScript::attacktoidle, this);
		animator->GetFrameEvent(L"Player_Jump", 1) = std::bind(&CPlayerScript::jumpdelay, this);

	}

	void CPlayerScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();
		Vector3 pos = transform->GetPosition();



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

		if (mState[(UINT)ePlayerState::Attack] == false)
		{
			if (CInput::GetKeyTap(eKeyCode::A))
				GetOwner()->SetLeft();
			if (CInput::GetKeyTap(eKeyCode::D))
				GetOwner()->SetRight();


			if (!rigidebody->IsOnAir())
			{



#pragma region IdleToRun
				// idle to run
				if (CInput::GetKeyTap(eKeyCode::A))
				{
					animator->Play(L"Player_IdleToRun", false);
					rigidebody->AddForce(transform->Right() * -500.f);
					mState[(UINT)ePlayerState::IdleToRun] = true;
					mState[(UINT)ePlayerState::Idle] = false;
				}
				if (CInput::GetKeyTap(eKeyCode::D))
				{
					animator->Play(L"Player_IdleToRun", false);
					rigidebody->AddForce(transform->Right() * 500.f);
					mState[(UINT)ePlayerState::IdleToRun] = true;
					mState[(UINT)ePlayerState::Idle] = false;
				}

#pragma endregion

#pragma region Run
				// run
				if (mState[(UINT)ePlayerState::Run] == true)
				{
					if (CInput::GetKeyDown(eKeyCode::A))
						rigidebody->AddForce(transform->Right() * -50.f);

					if (CInput::GetKeyDown(eKeyCode::D))
						rigidebody->AddForce(transform->Right() * 50.f);
				}

				if (GetOwner()->IsLeft())
				{
					if (CInput::GetKeyUp(eKeyCode::A))
						if (mState[(UINT)ePlayerState::Run] == true || mState[(UINT)ePlayerState::IdleToRun] == true)
							animator->Play(L"Player_RunToIdle", false);
				}
				else
				{
					if (CInput::GetKeyUp(eKeyCode::D))
						if (mState[(UINT)ePlayerState::Run] == true || mState[(UINT)ePlayerState::IdleToRun] == true)
							animator->Play(L"Player_RunToIdle", false);
				}
			}


#pragma endregion

#pragma region Jump

			// 지상일때
			if (!GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
			{
				if (CInput::GetKeyTap(eKeyCode::W))
				{
					// 점프
					mState.reset();
					animator->Play(L"Player_Jump", false);
				}
			}
			else
			{
				// 공중에서도 이동 가능
				if (CInput::GetKeyDown(eKeyCode::A))
					rigidebody->AddForce(transform->Right() * -50.f);

				if (CInput::GetKeyDown(eKeyCode::D))
					rigidebody->AddForce(transform->Right() * 50.f);

				// 공중에서 점프 키 일찍떼면 fall
				if (CInput::GetKeyUp(eKeyCode::W))
				{
					mState[(UINT)ePlayerState::Jump] = false;
					mState[(UINT)ePlayerState::Fall] = true;
					animator->Play(L"Player_Fall", true);
				}
			}

			if (mState[(UINT)ePlayerState::Jump] == true)
			{
				mAirTime += CTimeMgr::DeltaTime();
				// 점프 시간 끝나면 Fall
				if (0.15f <= mAirTime)
				{
					mState[(UINT)ePlayerState::Jump] = false;
					mState[(UINT)ePlayerState::Fall] = true;
					animator->Play(L"Player_Fall", true);
					mAirTime = 0.f;
				}
				else
				{
					if (CInput::GetKeyDown(eKeyCode::W))
					{
						rigidebody->AddForce(transform->Up() * 70.f);
					}
				}
			}

#pragma endregion

		}

#pragma region Attack
		
		Vector3 MousePos = CInput::GetMousePosition();
		mAttackCooldown += CTimeMgr::DeltaTime();

		if (0.25f <= mAttackCooldown)
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
					rigidebody->AddVelocity(mAttackDir * 5.f);

					mState.reset();
					mState[(UINT)ePlayerState::Attack] = true;
					animator->Play(L"Player_Attack", false);
				}

				mAttackCooldown = 0.f;
			}
		}

		if (mState[(UINT)ePlayerState::Attack] == true)
		{
			mAttackTime += CTimeMgr::DeltaTime();

			if (0.15f <= mAttackTime)
			{
				mState[(UINT)ePlayerState::Attack] = false;

				mAttackTime = 0.f;
				mbFirstAttack = false;
				mAttackDir = Vector3::Zero;

			}
			else
			{
				if (mbFirstAttack)
					rigidebody->AddForce(mAttackDir * 40.f);

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

			if (mState[(UINT)ePlayerState::Fall] == true)
			{
				mState[(UINT)ePlayerState::Fall] = false;
				mState[(UINT)ePlayerState::RunToIdle] = true;
				CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
				animator->Play(L"Player_RunToIdle");

			}

			if (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D))
			{
				mState[(UINT)ePlayerState::RunToIdle] = false;
				mState[(UINT)ePlayerState::Run] = true;
				CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
				animator->Play(L"Player_Run");
			}

			if (CInput::GetKeyDown(eKeyCode::A))
				GetOwner()->SetLeft();
			if (CInput::GetKeyDown(eKeyCode::D))
				GetOwner()->SetRight();


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

	void CPlayerScript::idletorunFrame()
	{
		mState[(UINT)ePlayerState::IdleToRun] = false;
		mState[(UINT)ePlayerState::Run] = true;
	}

	void CPlayerScript::idletorun()
	{
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		animator->Play(L"Player_Run");
	}

	void CPlayerScript::runtoidle()
	{
		
		mState.reset();
		mState[(UINT)ePlayerState::Idle] = true;
		
		CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
		animator->Play(L"Player_Idle");
	}

	void CPlayerScript::attacktoidle()
	{

		if (GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			mState[(UINT)ePlayerState::Fall] = true;
			CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
			animator->Play(L"Player_Fall");
		}
		else
		{
			mState[(UINT)ePlayerState::Idle] = true;
			CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
			animator->Play(L"Player_Idle");
		}
	}

	void CPlayerScript::jumpdelay()
	{
		mState.reset();
		mState[(UINT)ePlayerState::Jump] = true;

	}


}