#include "BlinkScript.h"
#include "TimeMgr.h"
#include "GameObj.h"

namespace dru
{
	CBlinkScript::CBlinkScript()
		: CScript()
		, mSwitch(false)
		,mIsBlinking(false)
		, mIsRandom(false)
		, mTimer(0.f)
		, mOnTime(0.f)
		, mOffTime(0.f)
	{
	}

	CBlinkScript::~CBlinkScript()
	{
	}

	void CBlinkScript::Initialize()
	{
	}

	void CBlinkScript::update()
	{
		if (mSwitch)
		{
			mTimer += CTimeMgr::DeltaTime();
		}
	}

	void CBlinkScript::fixedUpdate()
	{
		if (mSwitch)
		{

			if (!mIsBlinking)
			{
				if (mTimer > mOnTime)
				{
					GetOwner()->RenderingBlockOn();
					mIsBlinking = true;
					mTimer = 0.f;
				}
			}
			else
			{
				if (mTimer > mOffTime)
				{
					GetOwner()->RenderingBlockOff();
					mIsBlinking = false;
					mTimer = 0.f;
				}
			}
		}
	}

	void CBlinkScript::render()
	{


	}

	void CBlinkScript::OnCollisionEnter(CCollider2D* _oppo)
	{
	}

	void CBlinkScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBlinkScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

	void CBlinkScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CBlinkScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CBlinkScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}


}