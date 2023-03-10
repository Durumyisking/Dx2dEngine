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

			if (Distance >= 0.001f)
			{
				float Speed = 50.f;
				float Step = Speed * CTimeMgr::DeltaTime();

				if (Step < Distance)
				{
					MaskPos += GetOwner()->Up() * Step;
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