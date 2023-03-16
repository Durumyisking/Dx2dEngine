#include "TimeMgr.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
    LARGE_INTEGER	CTimeMgr::mCpuFrequency = {};
    LARGE_INTEGER   CTimeMgr::mPrevFrequency = {};
    LARGE_INTEGER	CTimeMgr::mCurFrequency = {};
    float			CTimeMgr::mDeltaTime = 0.0f;
    float			CTimeMgr::mOneSecond = 0.0f;
    float			CTimeMgr::mAccumulatedTime = 0.0f;

    void CTimeMgr::Initialize()
    {
        //CPU 의 초당 반복되는 주파수를 얻어온다.
        QueryPerformanceFrequency(&mCpuFrequency);

        //프로그램을 시작했을때의 CPU 클럭 수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void CTimeMgr::update()
    {
        QueryPerformanceCounter(&mCurFrequency);

        float differenceInFrequancy
            = static_cast<float>((mCurFrequency.QuadPart - mPrevFrequency.QuadPart));

        mDeltaTime = differenceInFrequancy / static_cast<float>(mCpuFrequency.QuadPart);
        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

        mAccumulatedTime += mDeltaTime;

#ifdef _DEBUG
        if (mDeltaTime > (1. / 60.))
            mDeltaTime = (1. / 60.);
#endif

    }

    void CTimeMgr::Render(HDC hdc)
    {
        static int iCount = 0;
        ++iCount;


        // 1 초에 한번
        mOneSecond += mDeltaTime;
        if (1.0f < mOneSecond)
        {
            HWND hWnd = application.GetHwnd();

            wchar_t szFloat[50] = {};
            float FPS = 1.f / mDeltaTime;
//            swprintf_s(szFloat, 50, L"DeltaTime : %d", iCount);
            int iLen = wcsnlen_s(szFloat, 50);
            //TextOut(_dc, 10, 10, szFloat, iLen);

            SetWindowText(hWnd, szFloat);

            // 누적시간, 카운트 초기화
            mOneSecond = 0.f;
            iCount = 0;
        }


    }

}