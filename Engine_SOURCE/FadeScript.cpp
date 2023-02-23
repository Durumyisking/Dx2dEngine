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
		, go(0)
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
		if (CInput::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			go = 1;
		}

		if (1 == go)
		{
			mtime += CTimeMgr::DeltaTime();
			CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
			renderer::FadeCB data = {};

			data.fValue = mFadeValue * mtime;
			data.bFadeType = mFadeType;

			cb->Bind(&data);
			cb->SetPipeline(eShaderStage::VS);
			cb->SetPipeline(eShaderStage::PS);
		}
	}

	void CFadeScript::fixedupdate()
	{
	}

	void CFadeScript::render()
	{
	}

}