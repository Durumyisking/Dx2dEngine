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
		virtual void fixedUpdate();
		virtual void render();
		virtual void destroy();
		// engine loop
		void Run();
		void Present();


		void SetWindow(HWND _hwnd, UINT _width, UINT _height);

		void SetHwnd(HWND _hwnd) { mHwnd = _hwnd; }
		HWND GetHwnd() const { return mHwnd; }

		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }
		math::Vector2 GetResolutionRatio();

		void DockingMenu();
		void DivideMenu();
		void ChangeWindowSize(bool _bMenu);

		void SetResolution(math::Vector2 _Resolution) { mResolution = _Resolution; };
		math::Vector2 WinResolution() const { return mResolution; }


	private:
		bool initalized = false;
		std::unique_ptr<graphics::CGraphicDevice> graphicDevice;

		HWND mHwnd;
		HDC	 mHdc;
		UINT mWidth;
		UINT mHeight;

		// 메뉴
		HMENU	mHmenu; // Tool Scene에서만 사용하고싶은 menu
		math::Vector2 mResolution;


	};
}

