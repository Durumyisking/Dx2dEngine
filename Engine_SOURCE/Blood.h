#pragma once
#include "LiveGameObj.h"

namespace dru
{
    class CBlood :
        public CLiveGameObj
    {
	public:
		CBlood();
		virtual ~CBlood();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();


		void SetBloodPosition_Direction(Vector3 _Standard, Vector3 _Direction);
		void SetBloodPosition_Round(Vector3 _Standard);

		void AnimCompleteEvent();

	private:
		Vector3 mMoveDirection;
		CTransform* mTransform;
		CRigidBody* mRigidbody;
		float	mSpeed;


		bool	mbBloodDead;
    };
}
