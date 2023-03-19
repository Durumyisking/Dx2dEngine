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
		, mRollTime(0.f)
		, mAttackCooldown(0.f)
		, mAttackDir(Vector3::Zero)
		, mbFirstAttack(true)
		, animator(nullptr)
		, rigidbody(nullptr)
	{
	}

	CPlayerScript::~CPlayerScript()
	{
	}

	void CPlayerScript::Initialize()
	{
		animator = GetOwner()->GetComponent<CAnimator>();
		rigidbody = GetOwner()->GetComponent<CRigidBody>();

		animator->GetFrameEvent(L"Player_IdleToRun", 1) = std::bind(&CPlayerScript::idletorunFrame, this);
		animator->GetCompleteEvent(L"Player_IdleToRun") = std::bind(&CPlayerScript::idletorunEnd, this);
		animator->GetCompleteEvent(L"Player_RunToIdle") = std::bind(&CPlayerScript::runtoidleEnd, this);
		animator->GetCompleteEvent(L"Player_Attack") = std::bind(&CPlayerScript::attacktoidleEnd, this);
		animator->GetCompleteEvent(L"Player_PreCrouch") = std::bind(&CPlayerScript::precrouch, this);
		animator->GetCompleteEvent(L"Player_PostCrouch") = std::bind(&CPlayerScript::postcrouch, this);
		animator->GetEndEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollEnd, this);
		animator->GetCompleteEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollComplete, this);

	}

	void CPlayerScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = transform->GetPosition();



		if (CInput::GetKeyState(eKeyCode::R) == eKeyState::DOWN)
		{
			Vector3 rot = transform->GetRotation();
			rot.z += 10.0f * CTimeMgr::DeltaTime();
			transform->SetRotation(rot);
		}

		if (CInput::GetKeyTap(eKeyCode::N_7))
			animator->Play(L"Player_Roll", false);
		if (CInput::GetKeyTap(eKeyCode::N_8))
			animator->Play(L"Player_IdleToRun");
		if (CInput::GetKeyTap(eKeyCode::N_9))
			animator->Play(L"Player_Run");
		if (CInput::GetKeyTap(eKeyCode::N_0))
			animator->Play(L"Player_RunToIdle");

		if (mState[(UINT)ePlayerState::Attack] == false)
		{
			if (mState[(UINT)ePlayerState::Roll] == false)
			{
				if (CInput::GetKeyTap(eKeyCode::A))
					GetOwner()->SetLeft();
				if (CInput::GetKeyTap(eKeyCode::D))
					GetOwner()->SetRight();
			}

			if (!rigidbody->IsOnAir())
			{


				if (mState[(UINT)ePlayerState::Roll] == false)
				{
#pragma region IdleToRun

					if (CInput::GetKeyTap(eKeyCode::A))
					{
						animator->Play(L"Player_IdleToRun", false);
						rigidbody->AddForce(transform->Right() * -500.f);
						mState[(UINT)ePlayerState::IdleToRun] = true;
						mState[(UINT)ePlayerState::Idle] = false;
					}
					if (CInput::GetKeyTap(eKeyCode::D))
					{
						animator->Play(L"Player_IdleToRun", false);
						rigidbody->AddForce(transform->Right() * 500.f);
						mState[(UINT)ePlayerState::IdleToRun] = true;
						mState[(UINT)ePlayerState::Idle] = false;
					}

#pragma endregion

#pragma region Run
					if (mState[(UINT)ePlayerState::Run] == true)
					{
						if (CInput::GetKeyDown(eKeyCode::A))
						{
							rigidbody->AddForce(transform->Right() * -50.f);
							if (CInput::GetKeyTap(eKeyCode::S))
								Roll();
						}

						if (CInput::GetKeyDown(eKeyCode::D))
						{
							rigidbody->AddForce(transform->Right() * 50.f);
							if (CInput::GetKeyTap(eKeyCode::S))
								Roll();

						}
						
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
#pragma endregion

				}

#pragma region Crouch


				if (CInput::GetKeyDown(eKeyCode::S))
				{
					if (mState[(UINT)ePlayerState::Idle] == true)
					{
						mState.reset();
						mState[(UINT)ePlayerState::Crouch] = true;
						animator->Play(L"Player_PreCrouch", false);
					}
				}

				if (mState[(UINT)ePlayerState::Crouch] == true && !mState[(UINT)ePlayerState::Run] == true && CInput::GetKeyUp(eKeyCode::S))
				{
					animator->Play(L"Player_PostCrouch", false);
				}
#pragma endregion

#pragma region Roll

				if (CInput::GetKeyDown(eKeyCode::S) && mState[(UINT)ePlayerState::Roll] == false)
					if (CInput::GetKeyTap(eKeyCode::A) || CInput::GetKeyTap(eKeyCode::D))
						Roll();

				if (mState[(UINT)ePlayerState::Roll] == true)
				{
					mRollTime += CTimeMgr::DeltaTime();

					if (0.35f <= mRollTime)
					{
						mRollTime = 0.f;
					}
					else
					{
						if(GetOwner()->IsLeft())
							rigidbody->AddForce(transform->Right() * -50.f);
						else
							rigidbody->AddForce(transform->Right() * 50.f);
					}
				}


#pragma endregion

			}


#pragma region Jump

			// 지상일때
			if (!GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
			{
				if (CInput::GetKeyTap(eKeyCode::W))
				{
					rigidbody->SetVelocity(Vector3::Zero);
					mState.reset();
					mState[(UINT)ePlayerState::Jump] = true;
					animator->Play(L"Player_Jump", false);
				}
			}
			else
			{
				// 공중에서도 이동 가능
				if (CInput::GetKeyDown(eKeyCode::A))
					rigidbody->AddForce(transform->Right() * -50.f);

				if (CInput::GetKeyDown(eKeyCode::D))
					rigidbody->AddForce(transform->Right() * 50.f);

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
						rigidbody->AddForce(transform->Up() * 70.f);
					}
				}
			}

#pragma endregion


		}

#pragma region Attack
		
		Vector3 MousePos = CInput::GetMousePosition();
		mAttackCooldown += CTimeMgr::DeltaTime();

		if (0.4f <= mAttackCooldown)
		{

			if (CInput::GetKeyTap(eKeyCode::LBTN) || CInput::GetKeyTap(eKeyCode::RBTN))
			{
				rigidbody->SetVelocity(Vector3::Zero);
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
					rigidbody->AddVelocity(mAttackDir * 5.f);

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
					rigidbody->AddForce(mAttackDir * 40.f);

			}
		}

#pragma endregion


		transform->SetPosition(pos);
		GetOwner()->Flip();



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
				animator->Play(L"Player_RunToIdle");

			}

			if (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D))
			{
				mState[(UINT)ePlayerState::RunToIdle] = false;
				mState[(UINT)ePlayerState::Run] = true;
				animator->Play(L"Player_Run");
			}

			if (CInput::GetKeyDown(eKeyCode::A))
				GetOwner()->SetLeft();
			if (CInput::GetKeyDown(eKeyCode::D))
				GetOwner()->SetRight();


			GetOwner()->GetComponent<CRigidBody>()->SetGround();
			Vector3 vel = rigidbody->GetVelocity();
			rigidbody->SetVelocity({ vel.x, 0.f, vel.z });
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

	void CPlayerScript::Roll()
	{
		Vector3 vel = rigidbody->GetMaxVelocity();
		rigidbody->SetMaxVelocity(Vector3(vel.x + 3.f, vel.y, vel.z));
		mState.reset();
		mState[(UINT)ePlayerState::Roll] = true;
		animator->Play(L"Player_Roll", false);
	}

	void CPlayerScript::idletorunFrame()
	{
		mState[(UINT)ePlayerState::IdleToRun] = false;
		mState[(UINT)ePlayerState::Run] = true;
	}


	void CPlayerScript::idletorunEnd()
	{
		animator->Play(L"Player_Run");
	}

	void CPlayerScript::runtoidleEnd()
	{
		
		mState.reset();
		mState[(UINT)ePlayerState::Idle] = true;
		
		animator->Play(L"Player_Idle");
	}

	void CPlayerScript::attacktoidleEnd()
	{

		if (GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			mState[(UINT)ePlayerState::Fall] = true;
			animator->Play(L"Player_Fall");
		}
		else
		{
			mState[(UINT)ePlayerState::Idle] = true;
			animator->Play(L"Player_Idle");
		}
	}

	void CPlayerScript::precrouch()
	{
		animator->Play(L"Player_Crouch");

	}

	void CPlayerScript::postcrouch()
	{
		mState.reset();
		mState[(UINT)ePlayerState::Idle] = true;
		animator->Play(L"Player_Idle");
	}

	void CPlayerScript::rollEnd()
	{
		rigidbody->SetMaxVelocity(Vector3(5.f, 7.f, 0.f));
	}

	void CPlayerScript::rollComplete()
	{
		mState.reset();
		if (CInput::GetKeyDown(eKeyCode::A))
		{
			GetOwner()->SetLeft();
			mState[(UINT)ePlayerState::IdleToRun] = true;
			animator->Play(L"Player_IdleToRun", false);
		}
		else if (CInput::GetKeyDown(eKeyCode::D))
		{
				GetOwner()->SetRight();
				mState[(UINT)ePlayerState::IdleToRun] = true;
				animator->Play(L"Player_IdleToRun", false);
		}
		else
		{
			mState[(UINT)ePlayerState::RunToIdle] = true;
			animator->Play(L"Player_RunToIdle", false);
		}	

		rigidbody->SetMaxVelocity(Vector3(5.f, 7.f, 0.f));
	}


}