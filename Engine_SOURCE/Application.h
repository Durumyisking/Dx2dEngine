#pragma once
#include "Engine.h"
#include "Graphics.h"
#include "GraphicDevice.h"


namespace dru
{
	class CApplication
	{
	public:
		CApplication();
		~CApplication();

		// engine loop
		void Run();

		virtual void init();
		// ĳ���� / ���� ������Ʈ
		virtual void update();
		// gpu ������Ʈ
		virtual void fixedupdate();
		virtual void render();

		void SetWindow(HWND _hwnd, UINT _width, UINT _height);

		void SetHwnd(HWND _hwnd) { mHwnd = _hwnd; }
		HWND GetHwnd() const { return mHwnd; }

		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }


	private:
		bool initalized = false;
		std::unique_ptr<graphics::CGraphicDevice> graphicDevice;

		HWND mHwnd;
		HDC	 mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

