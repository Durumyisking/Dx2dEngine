#pragma once
#include "Engine.h"


namespace dru
{
	class CTimeMgr
	{
	public:
		static __forceinline float DeltaTime() { return mDeltaTime; }
		static __forceinline float DeltaTimeConstant() { return mDeltaTimeConstant; }
		static __forceinline float AccumulatedTime() { return mAccumulatedTime; }
		static __forceinline void BulletTimeOn() 
		{
			mFramePass = 3;
			mFramePassCount = 0;
			mbBulletTime = true;
			mbFramePassCheck = false;
		}
		static __forceinline void PlayerBulletTimeOn()
		{
			mbPlayerBulletTime = true;
		}
		static __forceinline void BulletTimeOff()
		{
			mFramePass = 0;
			mFramePassCount = 0;
			mbBulletTime = false;
			mbFramePassCheck = true;
		}
		static __forceinline void PlayerBulletTimeOff()
		{
			mbPlayerBulletTime = false;
		}
		static __forceinline bool IsBulletTimeOn() { return mbBulletTime; }
		static __forceinline bool IsPlayerBulletTimeOn() { return mbPlayerBulletTime; }

		static __forceinline void SetFramePass(UINT _Value) { mFramePass = _Value; }
		static __forceinline bool IsFramePass() 
		{
			return mbFramePassCheck; 
		}


		static void Initialize();
		static void update();
		static void Render(HDC hdc);
		static void BulletTime(float _Time);



	private:
		static LARGE_INTEGER	mCpuFrequency;
		static LARGE_INTEGER	mPrevFrequency;
		static LARGE_INTEGER	mCurFrequency;

		static float			mDeltaTime;
		static float			mDeltaTimeConstant;
		static float			mOneSecond;
		static float			mAccumulatedTime;

		static float			mbBulletTimeTimer;
		static float			mbBulletTimeTimerMax;
		static bool				mbBulletTime;// 설정한 FramePass가 지나면 true가 되고 다음 프레임에 false가 됩니다
		static bool				mbPlayerBulletTime; // shift를 눌러서 킨 bullettime일때만 true가 됩니다.

		static UINT				mFramePass; // 설정한 FramePass만큼의 Frame이 지났는지 확인합니다
		static UINT				mFramePassCount;
		static bool				mbFramePassCheck; // 설정한 FramePass가 지나면 true가 되고 다음 프레임에 false가 됩니다.

	};
}