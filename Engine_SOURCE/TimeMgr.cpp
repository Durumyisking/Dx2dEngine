#include "TimeMgr.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
    LARGE_INTEGER	CTimeMgr::mCpuFrequency = {};
    LARGE_INTEGER   CTimeMgr::mPrevFrequency = {};
    LARGE_INTEGER	CTimeMgr::mCurFrequency = {};
    float			CTimeMgr::mDeltaTime = 0.0f;
    float			CTimeMgr::mDeltaTimeConstant = 0.0f;
    float			CTimeMgr::mOneSecond = 0.0f;
    float			CTimeMgr::mAccumulatedTime = 0.0f;
    float			CTimeMgr::mbBulletTimeTimer= 0.0f;
    float			CTimeMgr::mbBulletTimeTimerMax = 0.0f;
    bool			CTimeMgr::mbBulletTime = false;
    bool			CTimeMgr::mbPlayerBulletTime = false;
    UINT			CTimeMgr::mFramePass = 0;
    UINT			CTimeMgr::mFramePassCount = 0;
    bool            CTimeMgr::mbFramePassCheck = true;

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
        mDeltaTimeConstant = mDeltaTime;

        if (mbBulletTime)
        {
            if (mbFramePassCheck)
            {
                mFramePassCount = 0;
                mbFramePassCheck = false;
            }

            mbBulletTimeTimer += mDeltaTime;
            mDeltaTime /= 3.f;


            if (0 != mbBulletTimeTimerMax)
            {
                if (mbBulletTimeTimer > mbBulletTimeTimerMax)
                {
                    mbPlayerBulletTime = false;
                    mbBulletTime = false;
                    mbBulletTimeTimerMax = 0.f;
                    mbBulletTimeTimer = 0.f;
                }
            }
        }
        else
        {
            if (0 != mFramePassCount && mbFramePassCheck)
            {
                mFramePassCount = 0;
                mbFramePassCheck = false;
            }
        }

        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

        mAccumulatedTime += mDeltaTime;

        if (mFramePass == mFramePassCount)
        {
            mbFramePassCheck = true;
        }
        if (mFramePass > 0)
        {
            ++mFramePassCount;
        }


#ifdef _DEBUG
        if (mDeltaTime > (1.f / 60.f))
            mDeltaTime = (1.f / 60.f);
        if (mDeltaTimeConstant > (1.f / 60.f))
            mDeltaTimeConstant = (1.f / 60.f);
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
            swprintf_s(szFloat, 50, L"Fps : %d", iCount);
            int iLen = static_cast<int>(wcsnlen_s(szFloat, 50));
            //TextOut(_dc, 10, 10, szFloat, iLen);

            SetWindowText(hWnd, szFloat);

            // 누적시간, 카운트 초기화
            mOneSecond = 0.f;
            iCount = 0;
        }


    }

    void CTimeMgr::BulletTime(float _Time)
    {
        mbBulletTime = true;
        mbBulletTimeTimerMax = _Time;
    }

}