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
	void CApplication::fixedUpdate()
	{
		CSceneMgr::fixedUpdate();
	}
	void CApplication::render()
	{
		CTimeMgr::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

//		CSceneMgr::render();
		renderer::Render();

	}

	void CApplication::destroy()
	{
		CSceneMgr::destory();
	}

	void CApplication::Run()
	{
		update();
		fixedUpdate();
		render();
		destroy();
	}

	void CApplication::Present()
	{
		graphicDevice->Present();
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
	void CApplication::DockingMenu()
	{
		SetMenu(mHwnd, mHmenu);
		// 메뉴가 있으니까 true
		ChangeWindowSize(true);
	}
	void CApplication::DivideMenu()
	{
		SetMenu(mHwnd, nullptr);
		ChangeWindowSize(false);
	}
	void CApplication::ChangeWindowSize(bool _bMenu)
	{
		RECT rt = { 0, 0, static_cast<LONG>(mResolution.x), static_cast<LONG>(mResolution.y) };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	}
}
