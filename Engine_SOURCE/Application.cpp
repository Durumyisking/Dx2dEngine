#include "Application.h"
#include "Renderer.h"
#include "TimeMgr.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Resources.h"

namespace dru
{
	using namespace graphics;

	CApplication::CApplication()
	{
	}
	CApplication::~CApplication()
	{
		CSceneMgr::release();
	}

	void CApplication::Initialize()
	{
		CTimeMgr::Initialize();
		CInput::Initialize();

		renderer::Initialize();
		CSceneMgr::Initialize();
	}
	void CApplication::update()
	{
		CTimeMgr::update();
		CInput::update();
		CSceneMgr::update();
	}
	void CApplication::fixedupdate()
	{
		CSceneMgr::fixedupdate();
	}
	void CApplication::render()
	{
		CTimeMgr::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		CSceneMgr::render();

		graphicDevice->Present();
	}
	void CApplication::Run()
	{
		update();
		fixedupdate();
		render();
	}

	void CApplication::SetWindow(HWND _hwnd, UINT _width, UINT _height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = _hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = _width;
			mHeight = _height;
			
			eValidationMode vaildationMode = eValidationMode::Disabled;
			graphicDevice = std::make_unique<CGraphicDevice>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)_width , (LONG)_height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
