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
		, mMaxSpeed(5.f)
		, mFricCoeff(20.f)
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

			mVelocity += mAccel * CTimeMgr::DeltaTime();
		}

		if (mVelocity != Vector3::Zero)
		{
			Vector3 FricDir = -mVelocity;
			FricDir.Normalize();

			Vector3 Friction = FricDir * mFricCoeff * CTimeMgr::DeltaTime();

			if (mVelocity.Length() <= Friction.Length())
			{
				mVelocity = Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				mVelocity += Friction;
			}
		}

		if (mMaxSpeed < mVelocity.Length())
		{
			mVelocity.Normalize();
			mVelocity *= mMaxSpeed;
		}

		objMove();

		mForce = Vector3(0.f, 0.f, 0.f);
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

			Pos += mVelocity * CTimeMgr::DeltaTime();

			GetOwner()->SetPos(Pos);
		}
	}

}
