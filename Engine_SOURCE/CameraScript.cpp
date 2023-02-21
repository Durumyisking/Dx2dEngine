#include "CameraScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"

namespace dru
{
	CCameraScript::CCameraScript()
	{
	}

	CCameraScript::~CCameraScript()
	{
	}

	void CCameraScript::Initialize()
	{
	}

	void CCameraScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();

		Vector3 pos = transform->GetPosition();

		if (CInput::GetKeyState(eKeyCode::I) == eKeyState::PRESSED)
		{
			pos += 3.f * transform->Up() *CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::K) == eKeyState::PRESSED)
		{
			pos += 3.f * -transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
		{
			pos += 3.f * -transform->Right() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::L) == eKeyState::PRESSED)
		{
			pos += 3.f * transform->Right() * CTimeMgr::DeltaTime();
		}


		transform->SetPosition(pos);
	}

	void CCameraScript::fixedupdate()
	{
	}

	void CCameraScript::render()
	{
	}

}