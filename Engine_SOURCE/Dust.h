#pragma once
#include "GameObj.h"

namespace dru
{
    class CDust :
        public CGameObj
    {
	public:
		CDust();
		virtual ~CDust();

		virtual void Initialize();
		virtual void update();	
		virtual void fixedUpdate();
		virtual void render();

		void SetVelocity(Vector3 _vel);

	private:
		void rundustComplete();

		CRigidBody* mRigidbody;
    };
}

