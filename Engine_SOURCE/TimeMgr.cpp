#include "TimeMgr.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	LARGE_INTEGER CTimeMgr::mCpuFrequency;
	LARGE_INTEGER CTimeMgr::mPrevFrequency;
	LARGE_INTEGER CTimeMgr::mCurFrequency;
	float CTimeMgr::mDeltaTime = 0.0f;
	float CTimeMgr::mTime = 0.0f;

	void CTimeMgr::Initialize()
	{
		// Sleep();
		// CPU �ʴ� �ݺ��Ǵ� �������� ������ �Լ�
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷� ���� ������ cpu�� Ŭ�� ��
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void CTimeMgr::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		// �ٽ� ������ ���� ���ο� ���� ������ ����
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void CTimeMgr::Render(HDC hdc)
	{
		mTime += CTimeMgr::DeltaTime();
		if (mTime > 1.0f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;
			swprintf_s(szFloat, 50, L"fps : %f", fps);

			HWND hWnd = application.GetHwnd();

			SetWindowText(hWnd, szFloat);
			mTime = 0.0f;
		}
	}

}