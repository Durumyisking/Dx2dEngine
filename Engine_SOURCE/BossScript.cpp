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
		, mPatternCount(0)
		, mbDead(false)
		, mbIsPlayerLeft(false)
		, mbFlipWhilePattern(false)
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
	}

	void CBossScript::update()
	{
		eStageState stagestate = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState();
		if (stagestate == eStageState::LoadEnd)
		{
			if (!mbDead)
			{
				CheckPlayerLeft();
				IdleOperate();
				PatternOperate();
				
				mMoveDir = mRigidbody->GetVelocity();
				mMoveDir.Normalize();

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

	void CBossScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mRigidbody->SetVelocityY(0.f);
			mRigidbody->SetGround();
			GetOwner()->SetFloorOn();

		}
		else if (L"col_wall" == _oppo->GetName())
		{
			mRigidbody->SetVelocityX(0.f);
			if (GetOwner()->IsLeft())
			{
				GetOwner()->SetRight();
			}
			else
			{
				GetOwner()->SetLeft();
			}
		}
		else if (L"col_outWallside" == _oppo->GetName() || L"col_outWall" == _oppo->GetName())
		{
			mRigidbody->SetVelocityX(0.f);
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

	void CBossScript::CheckPlayerLeft()
	{
		float BossPosX = GetOwnerWorldPos().x;
		float PlayerPosX = mPlayer->GetWorldPos().x;
		if (PlayerPosX < BossPosX)
		{
			mbIsPlayerLeft = true;
		}
		else
		{
			mbIsPlayerLeft = false;
		}
	}

	void CBossScript::ChoosePattern()
	{
		int pattern = GetRandomNumber(mPatternCount, 1);
	//	int pattern = 1;

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
		case 6:
			SetSingleState(eBossState::Pattern6);
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
		else if (GetState(eBossState::Pattern6))
		{
			Pattern6();
		}
	}

	bool CBossScript::Patterning()
	{
		if (GetState(eBossState::Pattern1) || GetState(eBossState::Pattern2) || GetState(eBossState::Pattern3)
			|| GetState(eBossState::Pattern4) || GetState(eBossState::Pattern5) || GetState(eBossState::Pattern6))
		{
			return true;
		}
		return false;
	}

	bool CBossScript::FlipTest()
	{

		if (GetState(eBossState::Hurt) || GetState(eBossState::Dodge) || GetState(eBossState::Dead) || GetState(eBossState::Block))
		{
			return false;
		}

		if(Patterning())
		{
			return mbFlipWhilePattern;
		}

		return true;
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
				if (FlipTest())
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
	}
	void CBossScript::Reset()
	{
		SetSingleState(eBossState::Idle);
		mAttackCooldown = 1.f;
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
			case dru::eBossState::Hurt:
				break;
			case dru::eBossState::Block:
				mAnimator->Play(GetOwner()->GetName() + L"_Block", false);
				break;
			case dru::eBossState::End:
				break;
			default:
				break;
			}
			mState[(UINT)_Type] = true;
		}
	}

	float CBossScript::GetDistanceOfPlayer()
	{
		Vector2 vec2Boss = {GetOwnerWorldPos().x, GetOwnerWorldPos().y};
		Vector2 vec2Player = { mPlayer->GetWorldPos().x, mPlayer->GetWorldPos().y };

		float dist = Vector2::Distance(vec2Player, vec2Boss);

		return dist;
	}

	void CBossScript::SetHitDir()
	{
		Vector3 MousePos = CInput::GetMousePosition_world();

		Vector3 monsterPos = GetOwner()->GetPos();

		mMoveDir = MousePos - monsterPos;
		mMoveDir.Normalize();
	}

}