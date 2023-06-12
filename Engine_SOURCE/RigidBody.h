#pragma once
#include "Component.h"

using namespace dru::math;

namespace dru
{
    class CRigidBody :
        public CComponent
    {
		// 오른쪽 기준
#define DEGREE_90 dru::math::Vector3(0.f, 1.f, 0.f)
#define DEGREE_45 dru::math::Vector3(0.707f, 0.707f, 0.f)
#define DEGREE_30 dru::math::Vector3(0.866f, 0.5f, 0.f)
#define DEGREE_15 dru::math::Vector3(0.966f, 0.259f, 0.f)
#define DEGREE_0 dru::math::Vector3(1.f, 0.f, 0.f)


    public:
        CRigidBody();
        ~CRigidBody();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();


	public:
		void AddForce(Vector3 _Value) { mForce += _Value; }
		void AddForceX(float _Value) { mForce.x += _Value; }
		void AddForceY(float _Value) { mForce.y += _Value; }

		void SetMass(float _Value) { mMass = _Value; }
		float GetMass() const { return mMass; }

		void SetForce(Vector3 _Value) { mForce = _Value; }
		Vector3 GetForce() const { return mForce; }

		void SetVelocity(Vector3 _Value) { mVelocity = _Value; }
		void SetVelocityX(float _Value) { mVelocity.x = _Value; }
		void SetVelocityY(float _Value) { mVelocity.y = _Value; }

		Vector3 GetVelocity() const { return mVelocity; }

		void AddVelocity(Vector3 _Value) { mVelocity += _Value; }
		void AddVelocityX(float _Value) { mVelocity.x += _Value; }
		void AddVelocityY(float _Value) { mVelocity.y += _Value; }

		void SetMaxVelocity(Vector3 _Value) { mMaxSpeed = _Value; }
		Vector3 GetMaxVelocity() const { return  mMaxSpeed; }

		void SetFricCoeff(float _Value) { mFricCoeff = _Value; }
		float GetFricCoeff() const { return mFricCoeff; }

		void SetGround() { mbOnAir = false; }
		void SetAir() { mbOnAir = true; }

		bool IsOnAir() { return mbOnAir; }

		void AffectedGravityOn() { mbAffectedGravity = true; }
		void AffectedGravityOff() { mbAffectedGravity = false; }

		bool ObjOnStair();

		void SetAccelFromForce();
		void CalculateFriction();
		void MaxVelocityCheck();

		void SetGravity(float _Value) { mOriginGravity.y = _Value; }

		void SwitchOn() { mbSwitch = true; }
		void SwitchOff() { mbSwitch = false; }

	private:
		void objMove();

	private:
		Vector3		mForce;		// 크기, 방향
		Vector3		mAccel;		// 가속도
		float		mMass;		// 질량

		Vector3		mVelocity;	// 속도 (속력 + 방향)
		Vector3		mMaxSpeed;	// 최대 속력

		Vector3		mCurrentGravity;
		Vector3		mOriginGravity;

		float		mFricCoeff;	// 마찰계수

		bool		mbOnAir;

		bool		mbAffectedGravity;

		bool		mbSwitch;
    };

}
