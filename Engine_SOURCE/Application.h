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

		virtual void Initialize();
		// 캐릭터 / 로직 업데이트
		virtual void update();
		// gpu 업데이트
		virtual void fixedupdate();
		virtual void render();
		virtual void destroy();
		// engine loop
		void Run();

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

