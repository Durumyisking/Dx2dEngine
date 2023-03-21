#include "PlayerScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"


namespace dru
{
	CPlayerScript::CPlayerScript()
		: mState{}
		, mAirTime(0.f)
		, mAttackTime(0.f)
		, mRollTime(0.f)
		, mAttackCooldown(0.f)
		, mAttackDir(Vector3::Zero)
		, mbFirstAttack(0)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
	{
	}
	CPlayerScript::~CPlayerScript()
	{
	}
	void CPlayerScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mAnimator->GetFrameEvent(L"Player_IdleToRun", 1) = std::bind(&CPlayerScript::idletorunFrame, this);
		mAnimator->GetCompleteEvent(L"Player_IdleToRun") = std::bind(&CPlayerScript::idletorunEnd, this);
		mAnimator->GetCompleteEvent(L"Player_RunToIdle") = std::bind(&CPlayerScript::runtoidleEnd, this);
		mAnimator->GetCompleteEvent(L"Player_Attack") = std::bind(&CPlayerScript::attacktoidleEnd, this);
		mAnimator->GetCompleteEvent(L"Player_PreCrouch") = std::bind(&CPlayerScript::precrouch, this);
		mAnimator->GetCompleteEvent(L"Player_PostCrouch") = std::bind(&CPlayerScript::postcrouch, this);
		mAnimator->GetEndEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollEnd, this);
		mAnimator->GetCompleteEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollComplete, this);
		mAnimator->GetCompleteEvent(L"Player_WallKick") = std::bind(&CPlayerScript::wallkickComplete, this);
	}
	void CPlayerScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = transform->GetPosition();


		// set left right
		if (mState[(UINT)ePlayerState::Attack] == false)
		{
			if (mState[(UINT)ePlayerState::Roll] == false)
			{
				if (CInput::GetKeyTap(eKeyCode::A))
					GetOwner()->SetLeft();
				if (CInput::GetKeyTap(eKeyCode::D))
					GetOwner()->SetRight();
			}
			if (!mRigidbody->IsOnAir())
			{
				if (mState[(UINT)ePlayerState::Roll] == false)
				{
#pragma region IdleToRun
					if (CInput::GetKeyTap(eKeyCode::A) && (mbWallIsLeft != -1))
					{
						mAnimator->Play(L"Player_IdleToRun", false);
						mRigidbody->AddForce(transform->Right() * -500.f);
						mState[(UINT)ePlayerState::IdleToRun] = true;
						mState[(UINT)ePlayerState::Idle] = false;
					}
					if (CInput::GetKeyTap(eKeyCode::D) && (mbWallIsLeft != 1))
					{
						mAnimator->Play(L"Player_IdleToRun", false);
						mRigidbody->AddForce(transform->Right() * 500.f);
						mState[(UINT)ePlayerState::IdleToRun] = true;
						mState[(UINT)ePlayerState::Idle] = false;
					}
#pragma endregion
#pragma region Run
					if (mState[(UINT)ePlayerState::Run] == true)
					{
						if (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1))
						{
							mRigidbody->AddForce(transform->Right() * -50.f);
							if (CInput::GetKeyTap(eKeyCode::S))
								Roll();
						}
						if (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1))
						{
							mRigidbody->AddForce(transform->Right() * 50.f);
							if (CInput::GetKeyTap(eKeyCode::S))
								Roll();
						}

					}
					if (GetOwner()->IsLeft())
					{
						if (CInput::GetKeyUp(eKeyCode::A))
							if (mState[(UINT)ePlayerState::Run] == true || mState[(UINT)ePlayerState::IdleToRun] == true)
								mAnimator->Play(L"Player_RunToIdle", false);
					}
					else
					{
						if (CInput::GetKeyUp(eKeyCode::D))
							if (mState[(UINT)ePlayerState::Run] == true || mState[(UINT)ePlayerState::IdleToRun] == true)
								mAnimator->Play(L"Player_RunToIdle", false);
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
						mAnimator->Play(L"Player_PreCrouch", false);
					}
				}
				if (mState[(UINT)ePlayerState::Crouch] == true && !mState[(UINT)ePlayerState::Run] == true && CInput::GetKeyUp(eKeyCode::S))
				{
					mAnimator->Play(L"Player_PostCrouch", false);
				}
#pragma endregion
#pragma region Roll
				if (CInput::GetKeyDown(eKeyCode::S) && mState[(UINT)ePlayerState::Roll] == false)
					if ((CInput::GetKeyTap(eKeyCode::A) && (mbWallIsLeft != -1)) || (CInput::GetKeyTap(eKeyCode::D) && (mbWallIsLeft != 1)))
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
						if (GetOwner()->IsLeft())
							mRigidbody->AddForce(transform->Right() * -50.f);
						else
							mRigidbody->AddForce(transform->Right() * 50.f);
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
					mRigidbody->SetVelocity(Vector3::Zero);
					mState.reset();
					mState[(UINT)ePlayerState::Jump] = true;
					mAnimator->Play(L"Player_Jump", false);
				}
			}
			else
			{
				// 공중에서도 이동 가능
				if (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1))
					mRigidbody->AddForce(transform->Right() * -50.f);
				if (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1))
					mRigidbody->AddForce(transform->Right() * 50.f);
				// 공중에서 점프 키 일찍떼면 fall
				if (CInput::GetKeyUp(eKeyCode::W))
				{
					mState[(UINT)ePlayerState::Jump] = false;
					mState[(UINT)ePlayerState::Fall] = true;
					mAnimator->Play(L"Player_Fall", true);
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
					mAnimator->Play(L"Player_Fall", true);
					mAirTime = 0.f;
				}
				else
				{
					if (CInput::GetKeyDown(eKeyCode::W))
					{
						mRigidbody->AddForce(transform->Up() * 70.f);
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
				MakeSlash(L"fx_slash", GetOwner()->GetPos(), 5, { 100, 100 });

				Vector3 MousePos = CInput::GetMousePosition();
				mRigidbody->SetVelocity(Vector3::Zero);
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
					mRigidbody->AddVelocity(mAttackDir * 5.f);
					mState.reset();
					mState[(UINT)ePlayerState::Attack] = true;
					mAnimator->Play(L"Player_Attack", false);
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
					mRigidbody->AddForce(mAttackDir * 40.f);
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
				mAnimator->Play(L"Player_RunToIdle");
			}
			if ((CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1)) || (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1)))
			{
				mState[(UINT)ePlayerState::RunToIdle] = false;
				mState[(UINT)ePlayerState::Run] = true;
				mAnimator->Play(L"Player_Run");
			}
			if (CInput::GetKeyDown(eKeyCode::A))
				GetOwner()->SetLeft();
			if (CInput::GetKeyDown(eKeyCode::D))
				GetOwner()->SetRight();
			GetOwner()->GetComponent<CRigidBody>()->SetGround();
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
				mbWallIsLeft = -1;
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
				mbWallIsLeft = 1;

			if (mbWallIsLeft == -1)
			{
				if (0.f > mRigidbody->GetVelocity().x)
					mRigidbody->SetVelocity(Vector3(0.f, mRigidbody->GetVelocity().y, mRigidbody->GetVelocity().z));
			}
			else if (mbWallIsLeft == 1)
			{
				if (mRigidbody->GetVelocity().x > 0.f)
					mRigidbody->SetVelocity(Vector3(0.f, mRigidbody->GetVelocity().y, mRigidbody->GetVelocity().z));
			}

			if (!mRigidbody->IsOnAir())
			{
				mState.reset();
				mState[(UINT)ePlayerState::Idle] = true;
				mAnimator->Play(L"Player_Idle");
			}

			mbOnWall = true;
		}
	}
	void CPlayerScript::OnCollision(CCollider2D* _oppo)
	{
		if (L"col_wall" == _oppo->GetName())
		{
			if (mbWallIsLeft == -1)
			{
				if (0.f > mRigidbody->GetVelocity().x)
					mRigidbody->SetVelocity(Vector3(0.f, mRigidbody->GetVelocity().y, mRigidbody->GetVelocity().z));
			}
			else if (mbWallIsLeft == 1)
			{
				if (mRigidbody->GetVelocity().x > 0.f)
					mRigidbody->SetVelocity(Vector3(0.f, mRigidbody->GetVelocity().y, mRigidbody->GetVelocity().z));
			}

		}
	}
	void CPlayerScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = false;
			mbWallIsLeft = 0;
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
		Vector3 vel = mRigidbody->GetMaxVelocity();
		mRigidbody->SetMaxVelocity(Vector3(vel.x + 3.f, vel.y, vel.z));
		mState.reset();
		mState[(UINT)ePlayerState::Roll] = true;
		mAnimator->Play(L"Player_Roll", false);
	}
	void CPlayerScript::idletorunFrame()
	{
		mState[(UINT)ePlayerState::IdleToRun] = false;
		mState[(UINT)ePlayerState::Run] = true;
	}
	void CPlayerScript::idletorunEnd()
	{
		mAnimator->Play(L"Player_Run");
	}
	void CPlayerScript::runtoidleEnd()
	{

		mState.reset();
		mState[(UINT)ePlayerState::Idle] = true;

		mAnimator->Play(L"Player_Idle");
	}
	void CPlayerScript::attacktoidleEnd()
	{
		if (GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			mState[(UINT)ePlayerState::Fall] = true;
			mAnimator->Play(L"Player_Fall");
		}
		else
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mAnimator->Play(L"Player_Idle");
		}
	}
	void CPlayerScript::precrouch()
	{
		mAnimator->Play(L"Player_Crouch");
	}
	void CPlayerScript::postcrouch()
	{
		mState.reset();
		mState[(UINT)ePlayerState::Idle] = true;
		mAnimator->Play(L"Player_Idle");
	}
	void CPlayerScript::rollEnd()
	{
		mRigidbody->SetMaxVelocity(Vector3(5.f, 7.f, 0.f));
	}
	void CPlayerScript::rollComplete()
	{
		mState.reset();
		if (CInput::GetKeyDown(eKeyCode::A))
		{
			GetOwner()->SetLeft();
			mState[(UINT)ePlayerState::IdleToRun] = true;
			mAnimator->Play(L"Player_IdleToRun", false);
		}
		else if (CInput::GetKeyDown(eKeyCode::D))
		{
			GetOwner()->SetRight();
			mState[(UINT)ePlayerState::IdleToRun] = true;
			mAnimator->Play(L"Player_IdleToRun", false);
		}
		else
		{
			mState[(UINT)ePlayerState::RunToIdle] = true;
			mAnimator->Play(L"Player_RunToIdle", false);
		}
		mRigidbody->SetMaxVelocity(Vector3(5.f, 7.f, 0.f));
	}

	void CPlayerScript::wallkickComplete()
	{

	}

}