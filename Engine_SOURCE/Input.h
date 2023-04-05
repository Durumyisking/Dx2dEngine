#pragma once
#include "Engine.h"
#include "druMath.h"
#include "GameObj.h"
#include "Application.h"

extern dru::CApplication application;

namespace dru
{
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		//Special Key
		ENTER, ESC, LSHIFT, LALT, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,

		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5,
		N_6, N_7, N_8, N_9,

		END,
	};
	enum class eKeyState
	{
		TAP,
		DOWN,
		UP,
		NONE,
	};

	class CInput
	{
	public:
		struct Key
		{
			eKeyCode  eType;
			eKeyState eState;
			bool	  bPressed;
		};

		static void Initialize();
		static void update();
		static void Render(HDC hdc);
		static void ComputeMousePos();

		static __forceinline eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState;
		}

		static __forceinline math::Vector3 GetMousePosition()
		{
			return mMousePosition;
		}

		static __forceinline math::Vector3 GetMousePosition_world()
		{		
			return mWorldMousePosition;
		}



		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::DOWN;
		}

		static __forceinline bool GetKeyTap(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::TAP;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::UP;
		}

		static __forceinline bool GetKeyNone(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::NONE;
		}

	private:
		CInput() = delete;
		~CInput() = delete;

	private:
		static std::vector<Key> mKeys;
		static math::Vector3 mMousePosition;
		static math::Vector3 mWorldMousePosition;
		static float mWinWidthCenter;
		static float mWinHeightCenter;
	};
}

