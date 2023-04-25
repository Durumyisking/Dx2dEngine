#include "PlayerScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "LiveGameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Object.h"
#include "SlashScript.h"

#include "SceneMain.h"

#include "Dust.h"


namespace dru
{
	CPlayerScript::CPlayerScript()
		: mState{}
		, mAirTime(0.f)
		, mAttackTime(0.f)
		, mRollTime(0.f)
		, mWallSlideUpTime(0.f)
		, mAttackCooldown(0.f)
		, mAttackDir(Vector3::Zero)
		, mbFirstAttack(false)
		, mLRKeyupTime(0.f)
		, mSlideDustCount(0.f)
		, mBulletTimeGauge(10.f)
		, mbBulletTimeStun(false)
		, mBulletTimeCooldown(0.f)
		, mHitTimer(0.f)
		, mHitDir(Vector3::Zero)
		, mbLRKeyupTimerOn(false)
		, mbInputBlock(false)
		, mbOnWall(false)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mJumpdust(nullptr)
		, mLanddust(nullptr)
		, mbOnFloor2(false)
	{
	}
	CPlayerScript::~CPlayerScript()
	{
	}
	void CPlayerScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mTransform = GetOwner()->GetComponent<CTransform>();

		mState[(UINT)ePlayerState::Idle] = true;

		InputBlocking();

		mAnimator->GetFrameEvent(L"Player_IdleToRun", 1) = std::bind(&CPlayerScript::idletorunFrame, this);
		mAnimator->GetCompleteEvent(L"Player_IdleToRun") = std::bind(&CPlayerScript::idletorunEnd, this);
		mAnimator->GetCompleteEvent(L"Player_RunToIdle") = std::bind(&CPlayerScript::runtoidleEnd, this);
		mAnimator->GetCompleteEvent(L"Player_Attack") = std::bind(&CPlayerScript::attacktoidleEnd, this);
		mAnimator->GetCompleteEvent(L"Player_PreCrouch") = std::bind(&CPlayerScript::precrouch, this);
		mAnimator->GetCompleteEvent(L"Player_PostCrouch") = std::bind(&CPlayerScript::postcrouch, this);

		mAnimator->GetEndEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollEnd, this);

		mAnimator->GetFrameEvent(L"Player_Roll", 0) = std::bind(&CPlayerScript::rollFrame1, this);
		mAnimator->GetFrameEvent(L"Player_Roll", 1) = std::bind(&CPlayerScript::rollFrame2, this);
		mAnimator->GetFrameEvent(L"Player_Roll", 2) = std::bind(&CPlayerScript::rollFrame3, this);
		mAnimator->GetFrameEvent(L"Player_Roll", 3) = std::bind(&CPlayerScript::rollFrame4, this); 
		mAnimator->GetFrameEvent(L"Player_Roll", 4) = std::bind(&CPlayerScript::rollFrame5, this);
		mAnimator->GetFrameEvent(L"Player_Roll", 5) = std::bind(&CPlayerScript::rollFrame6, this);
		mAnimator->GetFrameEvent(L"Player_Roll", 6) = std::bind(&CPlayerScript::rollFrame7, this);
		mAnimator->GetCompleteEvent(L"Player_Roll") = std::bind(&CPlayerScript::rollComplete, this);

		mAnimator->GetCompleteEvent(L"Player_WallKick") = std::bind(&CPlayerScript::wallkickComplete, this);
		mAnimator->GetCompleteEvent(L"Player_Dead") = std::bind(&CPlayerScript::deadComplete, this);
	}
	void CPlayerScript::update()
	{
		CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
		if (mState[(UINT)ePlayerState::Dead] == true)
		{
			dead();
		}


		if (!mbInputBlock)
		{

			mPos = mTransform->GetPosition();

			if (CInput::GetKeyTap(eKeyCode::A) || CInput::GetKeyTap(eKeyCode::D))
			{
				mbLRKeyupTimerOn = false;
				mLRKeyupTime = 0.f;
			}

			if (CInput::GetKeyUp(eKeyCode::A) || CInput::GetKeyUp(eKeyCode::D))
				mbLRKeyupTimerOn = true;

			if (mbLRKeyupTimerOn)
				mLRKeyupTime += CTimeMgr::DeltaTime();

			bulletTime();
			if (mState[(UINT)ePlayerState::Idle] == true)
			{
				SetAfterImageCount(20);
			}

			// set left right
			if (mState[(UINT)ePlayerState::Attack] == false)
			{
				if (mState[(UINT)ePlayerState::WallKick] == false)
				{
					if (mState[(UINT)ePlayerState::Roll] == false)
					{
						if (CInput::GetKeyDown(eKeyCode::A))
							GetOwner()->SetLeft();
						if (CInput::GetKeyDown(eKeyCode::D))
							GetOwner()->SetRight();
					}
					if (!mRigidbody->IsOnAir())
					{
						if (mState[(UINT)ePlayerState::Roll] == false)
						{
							idleToRun();
							run();
						}

						crouch();
						rollTrigger();
						roll();
					}
					jump();


					if (mRigidbody->IsOnAir())
					{
						mWallSlideUpTime += CTimeMgr::DeltaTime();
						fall();
					}

					if (mbOnWall)
					{
						wallSlide();
					}

					wallKickTrigger();
				}
				wallKick();

			}

			attack();

			if(CSceneMgr::mActiveScene)
			mTransform->SetPosition(mPos);
			GetOwner()->Flip();

		}
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
			collEnter_Floor();
		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			collEnter_Floor2(_oppo);
			GetOwner()->SetFloorOn();
		}
		else if (L"col_stair" == _oppo->GetName())
		{
			collEnter_Floor();

			float degree = dynamic_cast<CStair*>(_oppo->GetOwner())->GetDegree();
			GetOwner_LiveObject()->SetStairOn(degree);
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			collEnter_Wall(_oppo);
			GetOwner()->SetFloorOn();

		}
		else if (L"col_ceiling" == _oppo->GetName())
		{
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });
		}
		else if (L"col_outWallside" == _oppo->GetName())
		{
			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
				mbWallIsLeft = -1;
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
				mbWallIsLeft = 1;

			wallLRCheck();
		}
		else if (L"col_readyTrigger" == _oppo->GetName())
		{
			CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
			if (eStageState::NotReady == scene->GetCurrentStage()->GetReadyState())
			{
				CStage* st = scene->GetCurrentStage();
				st->SetReady(eStageState::Ready);
				_oppo->GetOwner()->Die();

				mAnimator->Play(L"Player_RunToIdle");
				mRigidbody->SetVelocity(Vector3::Zero);
			}
		}
		else if (L"col_Monster_Slash" == _oppo->GetName())
		{
			collEnter_MonsterSlash(_oppo);
		}

	}
	void CPlayerScript::OnCollision(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mbFirstAttack = true;
			mRigidbody->SetGround();
			GetOwner()->SetFloorOn();

		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			if (mbOnFloor2)
			{
				if (CInput::GetKeyDown(eKeyCode::S))
				{
					if ( !(CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D)))
					{
						mRigidbody->SetAir();
						fallStart();
						mbOnFloor2 = false;
					}
				}
			}
		}
		else if (L"col_stair" == _oppo->GetName())
		{
			float degree = dynamic_cast<CStair*>(_oppo->GetOwner())->GetDegree();
			GetOwner_LiveObject()->SetStairOn(degree);
		}

		else if (L"col_wall" == _oppo->GetName())
		{
			coll_Wall();
		}
		else if (L"col_ceiling" == _oppo->GetName())
		{
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });
		}
		else if (L"col_outWallside" == _oppo->GetName())
		{
			wallLRCheck();
		}

	}
	void CPlayerScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
			GetOwner()->SetFloorOff();
		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
			GetOwner()->SetFloorOff();
		}
		else if (L"col_stair" == _oppo->GetName())
		{
			if (!GetOwner()->IsOnFloor())
			{
				GetOwner()->GetComponent<CRigidBody>()->SetAir();
			}

			GetOwner_LiveObject()->SetStairOff();
		}

		else if (L"col_wall" == _oppo->GetName())
		{
			mbOnWall = false;

			if (mState[(UINT)ePlayerState::WallSlideUp] == true || mState[(UINT)ePlayerState::WallSlideDown] == true)
			{
				//if ((CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft == -1))
				//	|| ((CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft == 1))))
				{
					fallStart();
				}
			}
			mbWallIsLeft = 0;
		}
		else if (L"col_outWallside" == _oppo->GetName())
		{
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

	void CPlayerScript::SetPlayerSingleState(ePlayerState _state)
	{
		mState.reset();
		mState[(UINT)_state] = true;

		switch (_state)
		{
		case dru::ePlayerState::Idle:
			SetAfterImageCount(20);
			mAnimator->Play(L"Player_Idle");
			break;
		case dru::ePlayerState::IdleToRun:
			SetAfterImageCount(20);
			mAnimator->Play(L"Player_IdleToRun", false);
			break;
		case dru::ePlayerState::Run:
			SetAfterImageCount(20);
			mAnimator->Play(L"Player_Run");
			break;
		case dru::ePlayerState::RunToIdle:
			SetAfterImageCount(20);
			mAnimator->Play(L"Player_RunToIdle", false);
			break;
		case dru::ePlayerState::Jump:
			SetAfterImageCount(20); 
			break;
		case dru::ePlayerState::Attack:
			SetAfterImageCount(50);
			mAnimator->Play(L"Player_Attack", false); 
			break;
		case dru::ePlayerState::Crouch:
			mAnimator->Play(L"Player_PreCrouch", false);
			break;
		case dru::ePlayerState::Roll:
			SetAfterImageCount(100);
			mAnimator->Play(L"Player_Roll", false);
			break;
		case dru::ePlayerState::WallKick:
			SetAfterImageCount(50);
			mAnimator->Play(L"Player_WallKick", false); 
			break;
		case dru::ePlayerState::Fall:
			mAnimator->Play(L"Player_Fall");
			break;
		case dru::ePlayerState::Dead:
			mAnimator->Play(L"Player_Dead", false);
			break;
		case dru::ePlayerState::End:
			break;
		default:
			break;
		}
	}

	void CPlayerScript::PlayerDead()
	{
		SetPlayerSingleState(ePlayerState::Dead);
		mbInputBlock = true;
	}

	void CPlayerScript::Reset()
	{
		SetAfterImageCount(20);

		mHitTimer = 0.f;

		mBulletTimeCooldown = 0.f;
		mBulletTimeGauge = 10.f;
		mbBulletTimeStun = false;

		SetPlayerSingleState(ePlayerState::Idle);

		UnInputBlocking();
	}

	void CPlayerScript::idletorunFrame()
	{
		SetPlayerSingleState(ePlayerState::Run);
	}
	void CPlayerScript::idletorunEnd()
	{
		mAnimator->Play(L"Player_Run");
		createRolldust(5);
	}
	void CPlayerScript::runtoidleEnd()
	{
		SetPlayerSingleState(ePlayerState::Idle);
	}
	void CPlayerScript::attacktoidleEnd()
	{
		if (GetOwner()->GetComponent<CRigidBody>()->IsOnAir())
		{
			SetPlayerSingleState(ePlayerState::Fall);
		}
		else
		{
			SetPlayerSingleState(ePlayerState::Idle);
		}
	}
	void CPlayerScript::precrouch()
	{
		mAnimator->Play(L"Player_Crouch");
	}
	void CPlayerScript::postcrouch()
	{
		SetPlayerSingleState(ePlayerState::Idle);
	}
	void CPlayerScript::rollEnd()
	{
		mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
	}
	void CPlayerScript::rollComplete()
	{
		mState.reset();
		if (CInput::GetKeyDown(eKeyCode::A))
		{
			GetOwner()->SetLeft();
			SetPlayerSingleState(ePlayerState::IdleToRun);
		}
		else if (CInput::GetKeyDown(eKeyCode::D))
		{
			SetPlayerSingleState(ePlayerState::IdleToRun);
			GetOwner()->SetRight();
		}
		else
		{
			SetPlayerSingleState(ePlayerState::RunToIdle);
		}
		mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
	}

	void CPlayerScript::wallkickComplete()
	{
		fallStart();
		mLRKeyupTime = 0.f;
	}

	void CPlayerScript::rollFrame1()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame2()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame3()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame4()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame5()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame6()
	{
		createRolldust(3);
	}

	void CPlayerScript::rollFrame7()
	{
		createRolldust(3);
	}

	void CPlayerScript::JumpdustComplete()
	{
		mJumpdust->RenderingBlockOn();
	}

	void CPlayerScript::LanddustComplete()
	{
		mLanddust->RenderingBlockOn();
	}

	void CPlayerScript::deadComplete()
	{
		//GetOwner()->GetComponent<CCollider2D>()->RenderingOff();
	}

	void CPlayerScript::idleToRun()
	{
		if (CInput::GetKeyTap(eKeyCode::A) && (mbWallIsLeft != -1))
		{
			mRigidbody->AddForce(mTransform->Right() * -500.f);
			SetPlayerSingleState(ePlayerState::IdleToRun);
		}
		if (CInput::GetKeyTap(eKeyCode::D) && (mbWallIsLeft != 1))
		{
			mRigidbody->AddForce(mTransform->Right() * 500.f);
			SetPlayerSingleState(ePlayerState::IdleToRun);
		}
	}

	void CPlayerScript::run()
	{
		if (mState[(UINT)ePlayerState::Run] == true)
		{
			if (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1))
			{
				mRigidbody->AddForce(mTransform->Right() * -50.f);
			}
			if (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1))
			{
				mRigidbody->AddForce(mTransform->Right() * 50.f);
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
	}

	void CPlayerScript::crouch()
	{
		if (CInput::GetKeyDown(eKeyCode::S))
		{
			if (mState[(UINT)ePlayerState::Idle] == true)
			{
				SetPlayerSingleState(ePlayerState::Crouch);
			}
		}
		if (mState[(UINT)ePlayerState::Crouch] == true && !mState[(UINT)ePlayerState::Run] == true && CInput::GetKeyUp(eKeyCode::S))
		{
			mAnimator->Play(L"Player_PostCrouch", false);
		}
	}

	void CPlayerScript::fall()
	{
		if (mState[(UINT)ePlayerState::Fall] == true)
		{
			if (CInput::GetKeyTap(eKeyCode::S))
			{
				mRigidbody->SetMaxVelocity({ 5.f, 10.f, 0.f });
			}
			if (CInput::GetKeyDown(eKeyCode::S))
			{
				mRigidbody->AddForce({ 0.f, -100.f, 0.f });
			}

			if (CInput::GetKeyUp(eKeyCode::S))
			{
				mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
			}
		}
	}

	void CPlayerScript::fallStart()
	{
		mState.reset();
		mState[(UINT)ePlayerState::Fall] = true;
		mAnimator->Play(L"Player_Fall");
		mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
	}

	void CPlayerScript::rollTrigger()
	{
		if (mState[(UINT)ePlayerState::Roll] == false)
		{
			if (CInput::GetKeyDown(eKeyCode::S))
			{
				if (NotowardToWallCheck_KeyTap())
				{
					if (CInput::GetKeyTap(eKeyCode::A))
						GetOwner()->SetLeft();
					if (CInput::GetKeyTap(eKeyCode::D))
						GetOwner()->SetRight();

					rollStart();
				}
			}
			else if (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D))
			{
				if (NotowardToWallCheck_KeyDown())
				{
					if (CInput::GetKeyTap(eKeyCode::S))
					{
						rollStart();
					}
				}
			}
		}

	}
	void CPlayerScript::rollStart()
	{
		Vector3 vel = mRigidbody->GetMaxVelocity();
		mRigidbody->SetMaxVelocity(Vector3(vel.x + 3.f, vel.y, vel.z));
		SetPlayerSingleState(ePlayerState::Roll);

	}
	void CPlayerScript::roll()
	{
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
				{
					mRigidbody->AddForce(mTransform->Right() * -50.f);
				}
				else
				{
					mRigidbody->AddForce(mTransform->Right() * 50.f);
				}

			}
		}
	}
	void CPlayerScript::jump()
	{
		// 지상일때
		if (!mRigidbody->IsOnAir())
		{
			if (CInput::GetKeyTap(eKeyCode::W))
			{
				mRigidbody->SetVelocity(Vector3::Zero);
				SetPlayerSingleState(ePlayerState::Jump);
				mAnimator->Play(L"Player_Jump", false);

				PlayJumpdust();
				jumpdustRotate(0.f);

				SetAfterImageCount(20);
			}
		}
		else
		{
			// 공중에서도 이동 가능
			if (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1))
				mRigidbody->AddForce(mTransform->Right() * -25.f);
			if (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1))
				mRigidbody->AddForce(mTransform->Right() * 25.f);


		}
		if (mState[(UINT)ePlayerState::Jump] == true)
		{
			mAirTime += CTimeMgr::DeltaTime();
			// 점프 시간 끝나면 Fall
			if (0.15f <= mAirTime)
			{
				mState[(UINT)ePlayerState::Jump] = false;
				if (mState[(UINT)ePlayerState::WallSlideUp] == false)
				{
					mState[(UINT)ePlayerState::Fall] = true;
					mAnimator->Play(L"Player_Fall", true);
				}
				mAirTime = 0.f;
			}
			else
			{
				if (CInput::GetKeyDown(eKeyCode::W))
				{
					mRigidbody->AddForce(mTransform->Up() * 70.f);
				}
			}

			// 공중에서 점프 키 일찍떼면 fall
			if (CInput::GetKeyUp(eKeyCode::W))
			{
				if (mState[(UINT)ePlayerState::WallSlideUp] == false)
				{
					fallStart();
				}
			}

		}
	}
	void CPlayerScript::wallSlide()
	{
		if (mRigidbody->IsOnAir())
		{
			if (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D))
			{
				if (CInput::GetKeyDown(eKeyCode::W))
				{
					mState[(UINT)ePlayerState::WallSlideUp] = true;
					mAnimator->Play(L"Player_WallSlide");
				}

			}

		}

		if (mState[(UINT)ePlayerState::WallSlideUp] == true)
		{

			if (0.4f <= mWallSlideUpTime && 0.5f > mWallSlideUpTime)
			{
				mRigidbody->SetVelocity(Vector3::Zero);
			}
			else if (0.6f <= mWallSlideUpTime)
			{
				mState[(UINT)ePlayerState::WallSlideUp] = false;
				mState[(UINT)ePlayerState::WallSlideDown] = true;
			}
			else
			{
				if (CInput::GetKeyDown(eKeyCode::W))
				{
					mRigidbody->AddForce(mTransform->Up() * 15.f);
					mSlideDustCount += CTimeMgr::DeltaTime();
					if (mSlideDustCount > (1.f / 15.f))
					{
						createRolldust(1);
						mSlideDustCount = 0.f;
					}
				}
			}
		}
		if (mState[(UINT)ePlayerState::WallSlideDown] == true)
		{
			mRigidbody->SetMaxVelocity({ 5.f, 3.f, 0.f });

			if (CInput::GetKeyDown(eKeyCode::S))
			{
				mRigidbody->SetMaxVelocity({ 5.f, 5.f, 0.f });
			}

			mSlideDustCount += CTimeMgr::DeltaTime();
			if (mSlideDustCount > (1.f / 15.f))
			{
				createRolldust(1);
				mSlideDustCount = 0.f;
			}
		}
	}
	void CPlayerScript::wallKickTrigger()
	{
		if (mState[(UINT)ePlayerState::WallSlideDown] == true || mState[(UINT)ePlayerState::WallSlideUp] == true)
		{
			if (CInput::GetKeyTap(eKeyCode::W))
			{
				SetPlayerSingleState(ePlayerState::WallKick);

				mRigidbody->SetVelocity({ 0.f, 0.f, 0.f });

				mRigidbody->SetMaxVelocity({ 6.f, 3.f, 0.f });

				if (GetOwner()->IsLeft())
				{
					PlayJumpdust();
					jumpdustRotate(-90.f);
					GetOwner()->SetRight();
				}
				else
				{
					PlayJumpdust();
					jumpdustRotate(90.f);
					GetOwner()->SetLeft();
				}
			}
		}

	}
	void CPlayerScript::wallKick()
	{
		if (mState[(UINT)ePlayerState::WallKick] == true)
		{
			{
				if (GetOwner()->IsLeft())
					mRigidbody->SetVelocity({ -6.f, 2.f, 0.f });
				else
					mRigidbody->SetVelocity({ 6.f, 2.f, 0.f });
			}
		}

	}

	void CPlayerScript::attack()
	{
		Vector3 MousePos = CInput::GetMousePosition();
		mAttackCooldown += CTimeMgr::DeltaTime();

		if (0.4f <= mAttackCooldown)
		{
			if (CInput::GetKeyTap(eKeyCode::LBTN) || CInput::GetKeyTap(eKeyCode::RBTN))
			{				
				makeSlash();

				Vector3 MousePos = CInput::GetMousePosition_world();
				mRigidbody->SetVelocity(Vector3::Zero);

				if (MousePos.x < mPos.x)
					GetOwner()->SetLeft();
				else
					GetOwner()->SetRight();
				if (CInput::GetKeyTap(eKeyCode::LBTN))
				{
					Vector3 vect;
					vect.x = MousePos.x - mPos.x;
					vect.y = MousePos.y - mPos.y;
					vect.Normalize();
					mAttackDir = vect;
					mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
					mRigidbody->AddVelocity(mAttackDir * 5.f);

					SetPlayerSingleState(ePlayerState::Attack);
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
	}

	void CPlayerScript::bulletTime()
	{
		if (CInput::GetKeyUp(eKeyCode::LSHIFT))
		{
			if (CTimeMgr::IsBulletTimeOn())
				CTimeMgr::BulletTimeOff();
		}

		if (mbBulletTimeStun)
		{
			bulletTimeStunOperate();
		}
		else
		{
			if (CInput::GetKeyNone(eKeyCode::LSHIFT))
			{
				mBulletTimeGauge += CTimeMgr::DeltaTime() / 2.f;
				if (mBulletTimeGauge > 10.f)
				{
					mBulletTimeGauge = 10.f;
				}
			}
			if (CInput::GetKeyDown(eKeyCode::LSHIFT))
			{
				if(!CTimeMgr::IsBulletTimeOn())
					CTimeMgr::BulletTimeOn();
				mBulletTimeGauge -= (CTimeMgr::DeltaTime() * 3.f);
				if (mBulletTimeGauge < 0.f)
				{
					mBulletTimeGauge = 0.f;
				}
			}

		}
	}

	void CPlayerScript::dead()
	{
		mHitTimer += CTimeMgr::DeltaTime();

		if (mHitTimer <= 0.25f)
		{
			mRigidbody->AddVelocity({ mHitDir.x * 0.5f, mHitDir.y * 0.5f, 0.f });
		}

	}


	void CPlayerScript::initializeJumpdustComponent()
	{

		CGameObj* JumpDustObject = GetOrCreateJumpdustObject();
		if (JumpDustObject)
		{
			std::shared_ptr<CTexture> JumpdustTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = JumpDustObject->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"dustMat");
				if (Material)
				{
					JumpdustTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}


			if (JumpdustTexture)
			{
				CAnimator* JumpDustAnimator = JumpDustObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (JumpDustAnimator)
				{
					JumpDustAnimator->Create(L"jumpdust", JumpdustTexture, { 222.f, 0.f }, { 32.f, 51.f }, Vector2::Zero, 4, { 60.f, 60.f }, 0.05f);
					JumpDustAnimator->GetCompleteEvent(L"jumpdust") = std::bind(&CPlayerScript::JumpdustComplete, this);
				}
				else
				{
					assert(false);
				}
			}
		}
	}

	void CPlayerScript::jumpdustSlideCheck()
	{
		Vector3 playerPos = GetOwnerPos();
		if (mState[(UINT)ePlayerState::WallKick] == true)
		{
			if (GetOwner()->IsLeft())
			{
				playerPos.x += 0.3f;
				mJumpdust->SetPos(playerPos);
			}
			else
			{
				playerPos.x -= 0.3f;
				mJumpdust->SetPos(playerPos);
			}
		}
		else
		{
			mJumpdust->SetPos(playerPos);
		}
	}

	void CPlayerScript::jumpdustRotate(float _Radian)
	{
		mJumpdust->GetComponent<CTransform>()->SetRotationZ( _Radian );
	}

	void CPlayerScript::PlayLanddust()
	{
		CGameObj* LandDustObject = GetOrCreateLanddustObject();
		if (LandDustObject)
		{
			Vector3 playerPos = GetOwner()->GetPos();
			playerPos.y -= 0.6f;
			LandDustObject->SetPos(playerPos);

			CAnimator* LandDustAnimator = LandDustObject->GetComponent<CAnimator>();
			if (LandDustAnimator)
			{
				LandDustObject->RenderingBlockOff();
				LandDustAnimator->Play(L"landdust", false);
			}
			else
			{
				assert(false);
			}
		}
	}

	void CPlayerScript::PlayJumpdust()
	{
		CGameObj* JumpDustObject = GetOrCreateJumpdustObject();
		jumpdustSlideCheck();

		if (JumpDustObject)
		{
			CAnimator* JumpDustAnimator = JumpDustObject->GetComponent<CAnimator>();
			if (JumpDustAnimator)
			{
				JumpDustObject->RenderingBlockOff();
				JumpDustAnimator->Play(L"jumpdust", false);
			}
			else
			{
				assert(false);
			}
		}
	}

	CGameObj* CPlayerScript::GetOrCreateJumpdustObject()
	{
		if (!mJumpdust)
		{
			// create
			mJumpdust = object::Instantiate<CGameObj>(eLayerType::FX, L"jumpdust");
			if (mJumpdust)
			{
				// intialize
				initializeJumpdustComponent();
			}
		}

		return mJumpdust;
	}

	CGameObj* CPlayerScript::GetOrCreateLanddustObject()
	{
		if (!mLanddust)
		{
			// create
			mLanddust = object::Instantiate<CGameObj>(eLayerType::FX, L"landdust");
			if (mLanddust)
			{
				// intialize
				initializeLanddustComponent();
			}
		}

		return mLanddust;
	}


	// 함수 이름으로 구라치지말자!!! -> create 생성한다. 근데? 함수를 보니까 애니메이션 Play하고 있어???
	// 함수는 하나의 동작만 하자 <- 중요!!!
	void CPlayerScript::initializeLanddustComponent()
	{
		CGameObj* LandDustObject = GetOrCreateLanddustObject();
		if (LandDustObject)
		{
			std::shared_ptr<CTexture> LanddustTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = LandDustObject->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"landdustMat");
				if (Material)
				{
					LanddustTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			// #todo Lambda 공부
			// #todo LanddustOffset -> 매직넘버는 변수로 정의를 해라 (클린코드)
			Vector3 playerPos = GetOwner()->GetPos();
			LandDustObject->SetPos({ playerPos.x, playerPos.y - 0.55f, playerPos.z - 0.001f });

			if (LanddustTexture)
			{
				CAnimator* LandDustAnimator = LandDustObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (LandDustAnimator)
				{
					// #todo bind도 lambda로 변환이 가능하다.
					LandDustAnimator->Create(L"landdust", LanddustTexture, { 0.f, 0.f }, { 50.f, 14.f }, Vector2::Zero, 7, { 60.f, 60.f }, 0.05f);
					LandDustAnimator->GetCompleteEvent(L"landdust") = std::bind(&CPlayerScript::LanddustComplete, this);
					//LandDustAnimator->Play(L"landdust", false);
					//LandDustAnimator->GetCompleteEvent(L"landdust") = std::bind(&CPlayerScript::landdustComplete, this);
				}
				else
				{
					assert(false);
				}
			}
		}
	}

	void CPlayerScript::bulletTimeStunOperate()
	{
		// bullet타임 스턴상태면 3초간 쿨타임 있음
		CTimeMgr::BulletTimeOff();
		mBulletTimeCooldown += CTimeMgr::DeltaTimeConstant();

		if (mBulletTimeCooldown >= 3.f)
		{
			mbBulletTimeStun = false;
			mBulletTimeGauge = 1.f;	
			mBulletTimeCooldown = 0.f;
		}
	}

	void CPlayerScript::createRolldust(UINT _Count)
	{
		for (UINT i = 0; i < _Count; i++)
		{
			CDust* dust = object::Instantiate<CDust>(eLayerType::FX, L"dust");
			Vector3 playerPos = GetOwner()->GetPos();
			playerPos.y -= 0.5f;
			playerPos.z -= 0.001f;
			dust->SetPos(playerPos);

			float x =  static_cast<float>(GetRandomNumber(30) / 10.f); 
			float y = static_cast<float>(GetRandomNumber(20) / 10.f); 

			if (0 < mRigidbody->GetVelocity().x)
			{
				dust->SetVelocity({ -x, y, 0.f });
			}
			else
			{
				dust->SetVelocity({ x, y, 0.f });
			}
		}
	}

	void CPlayerScript::makeSlash()
	{
		CGameObj* SlashObj = object::Instantiate<CGameObj>(eLayerType::FX, L"Player_Slash");

		CCollider2D* coll = SlashObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_Player_Slash");
		coll->Initialize();
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(1.f, 0.15f));


		Vector3 MousePos = CInput::GetMousePosition_world();

		Vector3 dir = MousePos - GetOwnerPos();
		dir.Normalize();

		SlashObj->SetScale({ 2.25f, 2.75f, 1.f });
		SlashObj->SetPos(GetOwnerPos() + dir);

		if (MousePos.x < GetOwner()->GetPos().x)
			GetOwner()->SetLeft();
		else
			GetOwner()->SetRight();

		GetOwner()->Flip();


		Vector3 rotation = SlashObj->GetRotation();

		// x축과 mousepos <-> slashobj 각도 받음 라디안
		rotation.z = atan2(MousePos.y - SlashObj->GetPos().y, MousePos.x - SlashObj->GetPos().x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;
		// 인자로 degree 넣음
		SlashObj->SetRotation(rotation);


		CSpriteRenderer* SpriteRenderer = SlashObj->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PlayerSlashMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = SlashObj->AddComponent<CAnimator>(eComponentType::Animator);
		std::wstring animname = L"Player_SlashAnim";
		mAnimator->Create(animname, Material->GetTexture(), { 0.f, 0.f }, { 100.f, 100.f }, Vector2::Zero, 5, {100.f, 100.f}, 0.025f);
		mAnimator->Play(animname, false);

		SlashObj->AddComponent<CSlashScript>(eComponentType::Script)->Initialize();
	}

	void CPlayerScript::wallLRCheck()
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

	void CPlayerScript::collEnter_Floor()
	{
		mbFirstAttack = true;
		mWallSlideUpTime = 0.f;

		if (mState[(UINT)ePlayerState::Dead] == false)
		{

			if (mState[(UINT)ePlayerState::Fall] == true || mState[(UINT)ePlayerState::WallSlideDown] == true || mState[(UINT)ePlayerState::WallSlideUp] == true)
			{
				mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
				SetPlayerSingleState(ePlayerState::RunToIdle);
			}
			if (NotowardToWallCheck_KeyDown())
			{
				SetPlayerSingleState(ePlayerState::Run);
			}

			if (CInput::GetKeyDown(eKeyCode::A))
				GetOwner()->SetLeft();
			if (CInput::GetKeyDown(eKeyCode::D))
				GetOwner()->SetRight();

			if (CInput::GetKeyDown(eKeyCode::S) && (CInput::GetKeyDown(eKeyCode::A) || CInput::GetKeyDown(eKeyCode::D)))
			{
				rollStart();
			}
			else
			{
				Vector3 vel = mRigidbody->GetVelocity();
				mRigidbody->SetVelocity({ vel.x, 0.f, vel.z });
			}

			// 처음 호출됐다면? LanddustObject Create
			// 그 이후부터는? LanddustObject Get
			if (GetOrCreateLanddustObject()) // 객체 있으면
			{
				PlayLanddust();
			}
		}
		mRigidbody->SetGround();
	}

	void CPlayerScript::collEnter_Floor2(CCollider2D* _oppo)
	{
		CCollider2D* playerCollier = GetOwner()->GetComponent<CCollider2D>();
		float PosCheckPlayer = playerCollier->GetColliderPos().y - playerCollier->GetScale().y / 2.f;
		float PosCheckFloor = _oppo->GetColliderPos().y + _oppo->GetScale().y / 2.f;
		if (PosCheckPlayer >= PosCheckFloor)
		{
			collEnter_Floor();
			mbOnFloor2 = true;
		}
	}

	void CPlayerScript::collEnter_Wall(CCollider2D* _oppo)
	{
		if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
			mbWallIsLeft = -1;
		else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
			mbWallIsLeft = 1;

		wallLRCheck();

		if (mState[(UINT)ePlayerState::Dead] == false)
		{
			if (mLRKeyupTime < 0.2f)
			{
				if (mState[(UINT)ePlayerState::WallKick] == false)
				{
					if (mRigidbody->GetVelocity().y > 0.f)
						mState[(UINT)ePlayerState::WallSlideUp] = true;
					else
					{
						mState[(UINT)ePlayerState::WallSlideDown] = true;
						mRigidbody->SetVelocity(Vector3::Zero);
					}
					mAnimator->Play(L"Player_WallSlide");
				}
			}

			if (mState[(UINT)ePlayerState::WallKick] == true)
			{
				mRigidbody->SetVelocity(Vector3::Zero);
				mState[(UINT)ePlayerState::WallKick] = false;
				mState[(UINT)ePlayerState::WallSlideDown] = true;
				mAnimator->Play(L"Player_WallSlide");
			}

			if (!mRigidbody->IsOnAir())
			{
				SetPlayerSingleState(ePlayerState::Idle);
			}
		}

		mbOnWall = true;
	}

	void CPlayerScript::collEnter_MonsterSlash(CCollider2D* _oppo)
	{
		if (mState[(UINT)ePlayerState::Dead] == false)
		{
			Vector3 pos = _oppo->GetOwnerPos();
			hit(pos);
		}
	}

	void CPlayerScript::coll_Wall()
	{
		wallLRCheck();

		if (mRigidbody->IsOnAir())
		{
			if (towardToWallCheck_KeyDown())
			{
				if (mState[(UINT)ePlayerState::WallKick] == false)
				{
					if (mRigidbody->GetVelocity().y > 0.f)
						mState[(UINT)ePlayerState::WallSlideUp] = true;
					else
					{
						mState[(UINT)ePlayerState::WallSlideDown] = true;
					}
					mAnimator->Play(L"Player_WallSlide");
				}
			}
		}
	}

	void CPlayerScript::hit(Vector3& _enemyPos)
	{
		SetAfterImageCount(0);

		if (mState[(UINT)ePlayerState::Roll] == false)
		{
			mState.reset();
			mState[(UINT)ePlayerState::Dead] = true;
			mAnimator->Play(L"Player_Dead", false);
			mbInputBlock = true;
			mRigidbody->SetMaxVelocity({ 5.f, 5.f, 0.f });
			mHitDir = GetOwnerPos() - _enemyPos;
			mHitDir.Normalize();

			// timeslow
			CTimeMgr::BulletTime(0.5f);

			// CamShake
			ShakeParams sp = {};
			sp.duration = 0.5f;
			sp.magnitude = 0.0125f;
			renderer::mainCamera->GetCamScript()->Shake(sp);

			CreateSlashShade(_enemyPos);

		}
	}

	bool CPlayerScript::towardToWallCheck_KeyTap()
	{
		return (CInput::GetKeyTap(eKeyCode::A) && (mbWallIsLeft == -1)) || (CInput::GetKeyTap(eKeyCode::D) && (mbWallIsLeft == 1));
	}

	bool CPlayerScript::towardToWallCheck_KeyDown()
	{
		return (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft == -1)) || (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft == 1));

	}

	bool CPlayerScript::NotowardToWallCheck_KeyTap()
	{
		return (CInput::GetKeyTap(eKeyCode::A) && (mbWallIsLeft != -1)) || (CInput::GetKeyTap(eKeyCode::D) && (mbWallIsLeft != 1));
	}

	bool CPlayerScript::NotowardToWallCheck_KeyDown()
	{
		return (CInput::GetKeyDown(eKeyCode::A) && (mbWallIsLeft != -1)) || (CInput::GetKeyDown(eKeyCode::D) && (mbWallIsLeft != 1));
	}

	void CPlayerScript::SetAfterImageCount(int _Count)
	{
		dynamic_cast<CPlayer*>(GetOwner())->SetAfterImageCount(_Count);
	}

}