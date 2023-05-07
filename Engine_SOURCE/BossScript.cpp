#include "BossScript.h"

#include "Stage.h"
#include "SceneMain.h"
#include "SceneMgr.h"
#include "TimeMgr.h"

namespace dru
{
	CBossScript::CBossScript()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mPlayer(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
		, mAttackCooldown(1.f)
		, mbDead(false)
		, mBossName{}
		, mState{}

	{
	}

	CBossScript::~CBossScript()
	{
	}

	void CBossScript::Initialize()
	{
		mState[(UINT)eBossState::Idle] = true;

		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mTransform = GetOwner()->GetComponent<CTransform>();
		mBossName = GetOwner()->GetName();

		//mAnimator->GetCompleteEvent(mBossName + L"_DeadGround") = std::bind(&CBossScript::deadgroundComplete, this);
	}

	void CBossScript::update()
	{
		eStageState stagestate = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState();
		if (stagestate == eStageState::LoadEnd)
		{
			mPos = mTransform->GetPosition();

			if (!mbDead)
			{
				IdleOperate();
				PatternOperate();
				

				mMoveDir = mRigidbody->GetVelocity();
				mMoveDir.Normalize();

				mTransform->SetPosition(mPos);
			}
			FlipCheck();
		}
		GetOwner()->Flip();
	}

	void CBossScript::fixedUpdate()
	{
	}

	void CBossScript::render()
	{
	}

	void CBossScript::attack()
	{
	}

	void CBossScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mRigidbody->SetGround();
			GetOwner()->SetFloorOn();

			if (mbDead)
			{
				//mState[(UINT)eBossState::DieAirUp] = false;
				//mState[(UINT)eBossState::DieGround] = true;
				//mAnimator->Play(mBossName + L"_DeadGround", false);
			}

		}
		else if (L"col_wall" == _oppo->GetName())
		{

			if (GetOwner()->IsLeft())
			{
				GetOwner()->SetRight();
			}
			else
			{
				GetOwner()->SetLeft();
			}
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			// hitSlash(0);
		}
		else if (L"col_outWallside" == _oppo->GetName() || L"col_outWall" == _oppo->GetName())
		{
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ 0.f, vel.y, 0.f });
		}
	}

	void CBossScript::OnCollision(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->SetFloorOn();
		}
	}

	void CBossScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_wall" == _oppo->GetName())
		{
			if (mbDead)
			{
				mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
			}
		}
	}

	void CBossScript::ChoosePattern()
	{
		int pattern = GetRandomNumber(1, 0);

		switch (pattern)
		{
		case 1:
			SetSingleState(eBossState::Pattern1);
			break;
		case 2:
			SetSingleState(eBossState::Pattern2);
			break;
		case 3:
			SetSingleState(eBossState::Pattern3);
			break;
		case 4:
			SetSingleState(eBossState::Pattern4);
			break;
		case 5:
			SetSingleState(eBossState::Pattern5);
			break;
		default:
			break;
		}

	}

	void CBossScript::PatternEnd(UINT _PatternNumber)
	{
		SetSingleState(eBossState::Idle);
		mAttackCooldown = 1.f;
	}

	void CBossScript::IdleOperate()
	{
		if (GetState(eBossState::Idle))
		{
			mAttackCooldown -= CTimeMgr::DeltaTime();

			if (0.f >= mAttackCooldown)
			{
				ChoosePattern();
			}
		}
	}

	void CBossScript::PatternOperate()
	{
		if (GetState(eBossState::Pattern1))
		{
			Pattern1();
		}
		else if (GetState(eBossState::Pattern2))
		{
			Pattern2();
		}
		else if (GetState(eBossState::Pattern3))
		{
			Pattern3();
		}
		else if (GetState(eBossState::Pattern4))
		{
			Pattern4();
		}
		else if (GetState(eBossState::Pattern5))
		{
			Pattern5();
		}
	}

	void CBossScript::FlipCheck()
	{
		if (mMoveDir.x > 0.f)
		{
			GetOwner()->SetRight();
		}
		else if (mMoveDir.x < 0.f)
		{
			GetOwner()->SetLeft();
		}
		else if (mMoveDir.x == 0.f)
		{
			if (!mbDead)
			{
				if (mPlayer->GetWorldPos().x > GetOwnerWorldPos().x)
				{
					GetOwner()->SetRight();
				}
				else
				{
					GetOwner()->SetLeft();
				}
			}
		}
	}

	void CBossScript::Reset()
	{


	}

	void CBossScript::SetSingleState(eBossState _Type)
	{
		if (mState[(UINT)_Type] == false)
		{
			mState.reset();
			switch (_Type)
			{
			case dru::eBossState::Idle:
				mAnimator->Play(GetOwner()->GetName() + L"_Idle");
				break;
			case dru::eBossState::Run:
				mAnimator->Play(GetOwner()->GetName() + L"_Run");
				break;
			case dru::eBossState::Fall:
				break;
			case dru::eBossState::DieAirUp:
				break;
			case dru::eBossState::DieAirDown:
				break;
			case dru::eBossState::DieGround:
				break;
			case dru::eBossState::End:
				break;
			default:
				break;
			}
			mState[(UINT)_Type] = true;
		}
	}

}