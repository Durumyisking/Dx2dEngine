#include "RigidBody.h"
#include "TimeMgr.h"
#include "GameObj.h"

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
		, mGravity(Vector3(0.f, -20.f, 0.f))
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
		float fForce = mForce.Length();

		if (0.f != fForce)
		{
			mForce.Normalize();

			float Accel = fForce / mMass;

			mAccel = mForce * Accel;
		}

		if (mbOnAir && mbAffectedGravity)
		{
			mAccel += mGravity;
		}
		else
		{
			// 땅위에 있을때
			Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = mVelocity.Dot(gravity);
			mVelocity.x -= gravity.x * dot;
		}

		mVelocity += mAccel * CTimeMgr::DeltaTime();


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


		objMove();

		mForce = Vector3(0.f, 0.f, 0.f);
		mAccel = Vector3(0.f, 0.f, 0.f);
		mGravity = Vector3(0.f, -25.f, 0.f);
	}

	void CRigidBody::fixedUpdate()
	{
	}

	void CRigidBody::render()
	{
	}

	void CRigidBody::objMove()
	{
		float Speed = mVelocity.Length();

		if (0.f != Speed)
		{
			// 이동방향
			Vector3 Dir = mVelocity;

			Dir.Normalize();

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
