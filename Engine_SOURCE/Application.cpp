#include "Application.h"

namespace dru
{
	using namespace graphics;
	CApplication::CApplication()
	{
	}
	CApplication::~CApplication()
	{
	}
	void CApplication::Run()
	{
		update();
		fixedupdate();
		render();
	}
	void CApplication::init()
	{
	}
	void CApplication::update()
	{
	}
	void CApplication::fixedupdate()
	{
	}
	void CApplication::render()
	{
		graphicDevice->Draw();
	}
	void CApplication::SetWindow(HWND _hwnd, UINT _width, UINT _height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = _hwnd;
			mWidth = _width;
			mHeight = _height;

			eValidationMode vaildationMode = eValidationMode::Disabled;
			graphicDevice = std::make_unique<CGraphicDevice>();
		}

		RECT rt = { 0, 0, (LONG)_width , (LONG)_height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
