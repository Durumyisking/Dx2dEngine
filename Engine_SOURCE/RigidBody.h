#pragma once
#include "Component.h"

using namespace dru::math;

namespace dru
{
    class CRigidBody :
        public CComponent
    {
    public:
        CRigidBody();
        ~CRigidBody();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();


	public:
		void AddForce(Vector3 _Value)
		{
			mForce += _Value;
		}

		void SetMass(float _Value) { mMass = _Value; }
		float GetMass() const { return mMass; }

		void SetForce(Vector3 _Value) { mForce = _Value; }
		Vector3 GetForce() const { return mForce; }

		void SetVelocity(Vector3 _Value) { mVelocity = _Value; }
		Vector3 GetVelocity() const { return mVelocity; }

		void AddVelocity(Vector3 _Value) { mVelocity += _Value; }

		void SetMaxVelocity(float _Value) { mMaxSpeed = _Value; }

		void SetFricCoeff(float _Value) { mFricCoeff = _Value; }
		float GetFricCoeff() const { return mFricCoeff; }

	private:
		void objMove();

	private:
		Vector3		mForce;		// 크기, 방향
		Vector3		mAccel;		// 가속도
		float		mMass;		// 질량

		Vector3		mVelocity;	// 속도 (속력 + 방향)
		float		mMaxSpeed;	// 최대 속력

		float		mFricCoeff;	// 마찰계수

    };

}
