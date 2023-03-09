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
			CTransform* transform = GetOwner()->GetComponent<CTransform>();
			Vector3 pos = transform->GetPosition();

			if ((GetOwner()->GetPos().x == mTargetTransform->GetPosition().x) && (GetOwner()->GetPos().y == mTargetTransform->GetPosition().y))
			{
				mbMoveDone = true;
			}


			if(!mbGoDown)
				pos += 3.f * transform->Up() * CTimeMgr::DeltaTime();
			else
				pos -= 3.f * transform->Up() * CTimeMgr::DeltaTime();

		}
	}

	void CMaskScript::fixedUpdate()
	{
	}

	void CMaskScript::render()
	{
	}

}