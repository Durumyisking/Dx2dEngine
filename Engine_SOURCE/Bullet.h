#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CBullet :
		public CLiveGameObj
	{
	public:
		CBullet();
		virtual ~CBullet();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	private:
		CLiveGameObj* mTarget;
		bool mbReflected;
		Vector3 mDir;
		float mBulletSpeed;
		float collScaleX;
		float collPosX;

	public:
		void SetTarget(CLiveGameObj* _Target) { mTarget = _Target; }
		CLiveGameObj* GetTarget() const { return mTarget; }

		void SetDir(Vector3 _Dir) { mDir = _Dir; }
		Vector3 GetDir() const { return mDir; }

		void SetSpeed(float _Speed) { mBulletSpeed = _Speed; }
		float GetSpeed() const { return mBulletSpeed ; }

		float GetCollPosX() const { return collPosX; }
	};
}
