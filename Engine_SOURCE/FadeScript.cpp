#include "FadeScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Application.h"
#include "ConstantBuffer.h"
#include "TimeMgr.h"
#include "Input.h"


namespace dru
{
	CFadeScript::CFadeScript()
		: mFadeValue(1)
		, mFadeType(1)
		, mStart(1)
		, mtime(0)
		, mFadeTextureType(1)
	{
	}

	CFadeScript::~CFadeScript()
	{
	}

	void CFadeScript::Initialize()
	{
	}

	void CFadeScript::update()
	{
		//if (CInput::GetKeyState(eKeyCode::I) == eKeyState::DOWN)
		//{
		//	mStart = 1;
		//	mFadeType = 1;
		//	mtime = 0;
		//}
		//if (CInput::GetKeyState(eKeyCode::O) == eKeyState::DOWN)
		//{
		//	mStart = 1;
		//	mFadeType = 0;
		//	mtime = 0;
		//}

	}

	void CFadeScript::fixedUpdate()
	{
	}

	void CFadeScript::render()
	{
		if (1 == mStart)
		{
			mtime += CTimeMgr::DeltaTime();
			CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
			renderer::FadeCB data = {};

			data.fValue = mFadeValue * mtime;
			data.bFadeType = mFadeType;
			data.bTextureType = mFadeTextureType;

			cb->SetData(&data);
			cb->Bind(eShaderStage::PS);
		}

	}

	void CFadeScript::restart(int _fadeType)
	{
		mFadeType = _fadeType;
		mtime = 0;
	}

}