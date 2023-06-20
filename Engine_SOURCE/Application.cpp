#include "Application.h"
#include "Renderer.h"
#include "TimeMgr.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Resources.h"
#include "CollisionMgr.h"
#include "FMod.h"
#include "FontWrapper.h"
#include "ObjectPool.h"

namespace dru
{
	using namespace graphics;

	CApplication::CApplication()
		: initalized (false)
		, graphicDevice(nullptr)
		, mHwnd{}
		, mHdc{}
		, mWidth(0)
		, mHeight(0)
		, mHmenu{}
		, mResolution(Vector2::Zero)
	{
	}
	CApplication::~CApplication()
	{
		CFmod::Release();
		CObjectPool::Release();
		CSceneMgr::release();
		CFontWrapper::Release();
	}

	void CApplication::Initialize()
	{
		CObjectPool::Initialize();
		CTimeMgr::Initialize();
		CInput::Initialize();
		CFmod::Initialize();
		CCollisionMgr::Initialize();
		renderer::Initialize();
		CFontWrapper::Initialize();
		CSceneMgr::Initialize();

	}
	void CApplication::update()
	{
		CTimeMgr::update();
		CInput::update();
		CCollisionMgr::update();
		CSceneMgr::update();
	}
	void CApplication::fixedUpdate()
	{
		CCollisionMgr::fixedUpdate();
		CSceneMgr::fixedUpdate();
	}
	void CApplication::render()
	{
		CTimeMgr::Render(mHdc);
		CInput::Render(mHdc);
//		CCollisionMgr::render();
		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		renderer::Render();
		CSceneMgr::render();
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
			//graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)_width , (LONG)_height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

	Vector2 CApplication::GetResolutionRatio()
	{
		RECT	windowRC;

		GetClientRect(mHwnd, &windowRC);

		float width = static_cast<float>(windowRC.right - windowRC.left);
		float height = static_cast<float>(windowRC.bottom - windowRC.top);

		return Vector2(mWidth / width, mHeight / height);

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
