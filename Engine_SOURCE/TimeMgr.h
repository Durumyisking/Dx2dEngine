#pragma once
#include "CommonInclude.h"


namespace dru
{
	class CTimeMgr
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static float DeltaTime() { return mDeltaTime; }

	private:
		//CPU ���� ������ ( 1�ʴ� ��� ) 1�� 12000�� �����ϴ� CPU
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
		static float mTime;
	};
}