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
		Vector3		mForce;		// ũ��, ����
		Vector3		mAccel;		// ���ӵ�
		float		mMass;		// ����

		Vector3		mVelocity;	// �ӵ� (�ӷ� + ����)
		float		mMaxSpeed;	// �ִ� �ӷ�

		float		mFricCoeff;	// �������

    };

}
