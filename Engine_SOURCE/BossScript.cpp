#include "BossScript.h"

#include "Stage.h"
#include "SceneMain.h"
#include "SceneMgr.h"

namespace dru
{
	CBossScript::CBossScript()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mPlayer(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
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
			case dru::eBossState::Attack:
				mAnimator->Play(GetOwner()->GetName() + L"_Attack");
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