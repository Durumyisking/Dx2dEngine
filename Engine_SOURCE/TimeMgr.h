#pragma once
#include "Engine.h"


namespace dru
{
	class CTimeMgr
	{
	public:
		static __forceinline float DeltaTime() { return mDeltaTime; }
		static __forceinline float AccumulatedTime() { return mAccumulatedTime; }
		static __forceinline void BulletTimeOn() { mbBulletTime = true; }
		static __forceinline void BulletTimeOff() { mbBulletTime = false; }

		static void Initialize();
		static void update();
		static void Render(HDC hdc);

	private:
		static LARGE_INTEGER	mCpuFrequency;
		static LARGE_INTEGER	mPrevFrequency;
		static LARGE_INTEGER	mCurFrequency;

		static float			mDeltaTime;
		static float			mOneSecond;
		static float			mAccumulatedTime;

		static bool				mbBulletTime;
	};
}