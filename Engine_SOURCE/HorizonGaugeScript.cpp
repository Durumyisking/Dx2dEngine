#include "HorizonGaugeScript.h"
#include "GameObj.h"
#include "TimeMgr.h"

namespace dru
{
	CHorizonGaugeScript::CHorizonGaugeScript()
		: mTransform(nullptr)
		, mColor(math::Vector4::Zero)
		, mDefaultPosition(Vector3::Zero)
		, mDefaultScale(Vector3::Zero)
		, mTimer(0.f)
 		, mElapsedTime(0.f) 
		, mbPlaySwitch(false)
	{
	}

	CHorizonGaugeScript::~CHorizonGaugeScript()
	{
	}

	void CHorizonGaugeScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<CTransform>();
		mDefaultPosition = mTransform->GetWorldPosition();
		mDefaultScale = mTransform->GetScale();
	}

	void CHorizonGaugeScript::update()
	{
		if (mbPlaySwitch)	
		{
			mElapsedTime += CTimeMgr::DeltaTime();
			float Ratio = 1 - mElapsedTime / mTimer;
			if (Ratio >= 0.0f)
			{
				float NewX = mDefaultScale.x * Ratio;
				mTransform->SetScale({ NewX, mDefaultScale.y , mDefaultScale.z });
				mTransform->SetPosition({ mDefaultPosition.x - (mDefaultScale.x - NewX) * 0.5f, mDefaultPosition.y, mDefaultPosition.z });
			}
			else
			{
				GetOwner()->RenderingBlockOn();
				mElapsedTime = 0.f;
				mbPlaySwitch = false;
				mTransform->SetScale(mDefaultScale);
				mTransform->SetPosition(mDefaultPosition);
			}
		}
	}

	void CHorizonGaugeScript::fixedUpdate()
	{
	}

	void CHorizonGaugeScript::render()
	{

	}

	void CHorizonGaugeScript::Play()
	{
		GetOwner()->RenderingBlockOff();
		mbPlaySwitch = true;
	}

}