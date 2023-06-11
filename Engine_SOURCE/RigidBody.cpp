#include "RigidBody.h"
#include "TimeMgr.h"
#include "GameObj.h"
#include "LiveGameObj.h"
#include "Player.h"
#include "PlayerScript.h"

namespace dru
{
	CRigidBody::CRigidBody()
		: CComponent(eComponentType::RigidBody)
		, mForce(Vector3::Zero)
		, mAccel(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mMass(1.f)
		, mMaxSpeed(Vector3(5.f, 7.f, 0.f))
		, mFricCoeff(20.f)
		, mbOnAir(true)
		, mbAffectedGravity(true)
		, mbSwitch(true)
		, mCurrentGravity(Vector3(0.f, -25.f, 0.f))
		, mOriginGravity(Vector3(0.f, -25.f, 0.f))
	{
	}

	CRigidBody::~CRigidBody()
	{
	}

	void CRigidBody::Initialize()
	{
	}

	void CRigidBody::update()
	{
		if (mbSwitch)
		{
			SetAccelFromForce();

			if (ObjOnStair())
			{
				mCurrentGravity = Vector3::Zero;
			}
			if (mbOnAir && mbAffectedGravity)
			{
				mAccel += mCurrentGravity;
			}

			mVelocity += mAccel * CTimeMgr::DeltaTime();

			CalculateFriction();

			MaxVelocityCheck();

			objMove();

			mForce = Vector3(0.f, 0.f, 0.f);
			mAccel = Vector3(0.f, 0.f, 0.f);
			mCurrentGravity = mOriginGravity;
		}
	}

	void CRigidBody::fixedUpdate()
	{
	}

	void CRigidBody::render()
	{
	}

	bool CRigidBody::ObjOnStair()
	{
		if (GetOwner()->GetObjectType() == CGameObj::eObjectType::Live)
		{
			if (GetOwner_LiveObject()->IsOnStair())
			{
				return true;
			}
		}
		return false;
	}

	void CRigidBody::SetAccelFromForce()
	{
		float fForce = mForce.Length();

		if (0.f != fForce)
		{
			mForce.Normalize();

			float Accel = fForce / mMass;

			mAccel = mForce * Accel;
		}
	}

	void CRigidBody::CalculateFriction()
	{
		if (mVelocity != Vector3::Zero && !mbOnAir)
		{
			Vector3 FricDir = -mVelocity;
			FricDir.Normalize();

			Vector3 Friction = FricDir * mFricCoeff * CTimeMgr::DeltaTime();

			mAccel += Friction;

			if (mVelocity.Length() <= Friction.Length())
			{
				mVelocity = Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				mVelocity += Friction;
			}
		}
	}

	void CRigidBody::MaxVelocityCheck()
	{
		if (mMaxSpeed.x < fabs(mVelocity.x))
		{
			mVelocity.x /= fabs(mVelocity.x);
			mVelocity.x *= mMaxSpeed.x;
		}
		if (mMaxSpeed.y < fabs(mVelocity.y))
		{
			mVelocity.y /= fabs(mVelocity.y);
			mVelocity.y *= mMaxSpeed.y;
		}
	}

	void CRigidBody::objMove()
	{
		float Speed = mVelocity.Length();

		if (0.f != Speed)
		{
			// 이동방향
			Vector3 Dir = mVelocity;
			
			Dir.Normalize();

			//// 계단위에 있으면 계단 각도만큼 이동방향 수정한다.
			if(ObjOnStair())
			{
				if (eLayerType::Player == GetOwner()->GetLayerType())
				{
					CPlayer* player = dynamic_cast<CPlayer*>(GetOwner());
					CPlayerScript* script = player->GetScript<CPlayerScript>();

					if (script->GetPlayerState(ePlayerState::Run) || script->GetPlayerState(ePlayerState::IdleToRun) || script->GetPlayerState(ePlayerState::RunToIdle))
					{
						float slope = GetOwner_LiveObject()->GetSlope() * -1.f;

						Vector3 Plane = { 1.f, 0.f, 0.f };
						Plane = RotateZ(Plane, slope);

						//				mVelocity = RotateZ(mVelocity, slope);
						mVelocity = AdjustDirectionToSlope(mVelocity, Plane);
					}
				}
			}
			Vector3 Pos = GetOwner()->GetPos();
			
			Pos.x += mVelocity.x * CTimeMgr::DeltaTime();

			if (!(!mbOnAir && mVelocity.y < 0.f))
			{
				Pos.y += mVelocity.y * CTimeMgr::DeltaTime();
			}

			GetOwner()->SetPos(Pos);
		}
	}

}
