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
		, mStart(false)
		, mtime(0)
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
		if (CInput::GetKeyState(eKeyCode::I) == eKeyState::PRESSED)
		{
			mStart = 1;
			mFadeType = 1;
			mtime = 0;
		}
		if (CInput::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
		{
			mStart = 1;
			mFadeType = 0;
			mtime = 0;
		}

		if (1 == mStart)
		{
			mtime += CTimeMgr::DeltaTime();
			CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
			renderer::FadeCB data = {};

			data.fValue = mFadeValue * mtime;
			data.bFadeType = mFadeType;
			data.bTextureType = mFadeTextureType;

			cb->Bind(&data);
			cb->SetPipeline(eShaderStage::PS);
		}
	}

	void CFadeScript::fixedUpdate()
	{
	}

	void CFadeScript::render()
	{
	}

}