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
		:mbJump(false)
		, mAirTime (0.f)
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

#pragma region Run

		CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();

		Vector3 pos = transform->GetPosition();

		if (CInput::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = transform->GetRotation();
			rot.z += 10.0f * CTimeMgr::DeltaTime();
			transform->SetRotation(rot);
		}

		//if (CInput::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		//{
		//	pos += 2.5f * transform->Up() * CTimeMgr::DeltaTime();
		//}
		//if (CInput::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		//{
		//	pos -= 2.5f * transform->Up() * CTimeMgr::DeltaTime();
		//}


		if (CInput::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			rigidebody->AddForce(transform->Right() * -50.f);
			GetOwner()->SetLeft();
		}
		if (CInput::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			rigidebody->AddForce(transform->Right() * 50.f);
			GetOwner()->SetRight();
		}


#pragma endregion

#pragma region Jump


		if(!GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			if (CInput::GetKeyDown(eKeyCode::SPACE))
			{
				mbJump = true;
//				rigidebody->AddForce(transform->Up() * 20.f);

			}

		}
		if (mbJump)
		{
			mAirTime += CTimeMgr::DeltaTime();
			if (0.3f <= mAirTime)
			{
				mbJump = false;
				mAirTime = 0.f;
			}
			else
			{
				rigidebody->AddVelocity(transform->Up() * 10.f);
			}
		}



#pragma endregion


#pragma region Attack
		
		Vector3 MousePos = CInput::GetMousePosition();

		if (CInput::GetKeyDown(eKeyCode::LBTN) || CInput::GetKeyDown(eKeyCode::RBTN))
		{
				MousePos /= 100.f;
	
			if (MousePos.x < pos.x)
				GetOwner()->SetLeft(); 
			else
				GetOwner()->SetRight();

			if (CInput::GetKeyDown(eKeyCode::LBTN))
			{
				Vector3 vect;
				vect.x = MousePos.x - pos.x;
				vect.y = MousePos.y - pos.y;

				vect.Normalize();

				rigidebody->AddForce(vect * 200000.f);

				CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
				animator->Play(L"Player_Attack", false);
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
	}

	void CPlayerScript::runtoidle()
	{
	}

	void CPlayerScript::attacktoidle()
	{
		if (!GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			CAnimator* animator = GetOwner()->GetComponent<CAnimator>();
			animator->Play(L"Player_Idle");
		}
	}

}