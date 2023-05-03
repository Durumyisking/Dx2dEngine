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
		: mFadeValue(1.f)
		, mFadeType(1)
		, mStart(1)
		, mTime(1.f)
		, mElapsedTime(0.f)
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
	}

	void CFadeScript::fixedUpdate()
	{
	}

	void CFadeScript::render()
	{
		if (1 == mStart)
		{
			mElapsedTime += CTimeMgr::DeltaTime();

			CBaseRenderer* renderer = GetOwner()->GetComponent<CBaseRenderer>();
			std::shared_ptr<CMaterial> material = renderer->GetMaterial();

			renderer::MaterialCB data = {};

			data.fData1 = mFadeValue * (mElapsedTime / mTime);
			data.iData1 = mFadeType;
			data.iData2 = mFadeTextureType;


			material->SetData(eGPUParam::Float_1, &data.fData1);
			material->SetData(eGPUParam::Int_1, &data.iData1);
			material->SetData(eGPUParam::Int_2, &data.iData2);
		}

	}

	void CFadeScript::restart(int _fadeType)
	{
		mFadeType = _fadeType;
		mTime = 0;
	}

}