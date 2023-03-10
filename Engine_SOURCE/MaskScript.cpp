#include "MaskScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "TimeMgr.h"

namespace dru
{
	CMaskScript::CMaskScript()
		: mbMoveDone(false)
		, mTargetTransform(nullptr)
		, mbGoDown(false)
		, mSpeed(50.f)
		, mStep(0.f)
	{
	}

	CMaskScript::~CMaskScript()
	{
	}

	void CMaskScript::Initialize()
	{
	}

	void CMaskScript::update()
	{
		if (!mbMoveDone)
		{
			Vector3 TargetPos = mTargetTransform->GetPosition();
			Vector3 MaskPos = GetOwner()->GetPos();

			float Distance = (TargetPos - MaskPos).Length();

			if (Distance >= 1.f)
			{
				mStep = mSpeed * CTimeMgr::DeltaTime();

				if (mStep < Distance)
				{
					MaskPos += GetOwner()->Up() * mStep;
					GetOwner()->SetPos(MaskPos);
				}
			}
			else
			{
				mbMoveDone = true;
			}

		}
	}

	void CMaskScript::fixedUpdate()
	{
	}

	void CMaskScript::render()
	{
	}

}