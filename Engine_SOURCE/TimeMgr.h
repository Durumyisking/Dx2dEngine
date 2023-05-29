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
		static __forceinline void BulletTimeOff()
		{
			mFramePass = 0;
			mFramePassCount = 0;
			mbBulletTime = false;
			mbFramePassCheck = true;
		}
		static __forceinline bool IsBulletTimeOn() { return mbBulletTime; }

		static __forceinline void SetFramePass(UINT _Value) { mFramePass = _Value; }
		static __forceinline bool IsFramePass() 
		{
			if (mFramePassCount > 4)
			{
				int i = 0;
			}

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
		static bool				mbBulletTime;
	
		static UINT				mFramePass; // ������ FramePass��ŭ�� Frame�� �������� Ȯ���մϴ�
		static UINT				mFramePassCount;
		static bool				mbFramePassCheck; // ������ FramePass�� ������ true�� �ǰ� ���� �����ӿ� false�� �˴ϴ�.

	};
}