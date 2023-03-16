#include "Input.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	std::vector<CInput::Key> CInput::mKeys;
	math::Vector3 CInput::mMousePosition;
	float CInput::mWinWidthCenter;
	float CInput::mWinHeightCenter;

	int ASCII[(UINT)eKeyCode::END] =
	{
		//Alphabet
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		//Special Key
		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		//Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		//Num Line
		'0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9',
	};


	void CInput::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key key;
			key.eType = (eKeyCode)i;
			key.eState = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}

		RECT winRect = {};
		GetClientRect(application.GetHwnd(), &winRect);
		mWinWidthCenter = ((float)winRect.right - (float)winRect.left) / 2.0f;
		mWinHeightCenter = ((float)winRect.bottom - (float)winRect.top) / 2.0f;
	}

	void CInput::update()
	{
		if (GetFocus())
		{
			//KEY
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				// 해당키가 현재 눌려있다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::DOWN;
					else
						mKeys[i].eState = eKeyState::TAP;

					mKeys[i].bPressed = true;
				}
				else // 해당키가 현재 안눌려있다.
				{
					// 이전 프레임에는 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::UP;
					else // 이전 프레임에도 안눌려 있었다.
						mKeys[i].eState = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);
			mMousePosition.x = ((float)mousePos.x - mWinWidthCenter);
			mMousePosition.y = -((float)mousePos.y - mWinHeightCenter);
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				if (eKeyState::TAP == mKeys[i].eState || eKeyState::DOWN == mKeys[i].eState)
					mKeys[i].eState = eKeyState::UP;
				else if (eKeyState::UP == mKeys[i].eState)
					mKeys[i].eState = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}

	}
	void CInput::Render(HDC hdc)
	{
		HWND hWnd = application.GetHwnd();

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"X : %f | Y : %f", mMousePosition.x, mMousePosition.y);

		SetWindowText(hWnd, szFloat);
	}
}