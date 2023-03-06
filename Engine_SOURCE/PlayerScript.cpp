#include "PlayerScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"

namespace dru
{
	CPlayerScript::CPlayerScript()
		
	{
	}

	CPlayerScript::~CPlayerScript()
	{
	}

	void CPlayerScript::Initialize()
	{
	}

	void CPlayerScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();

		Vector3 pos = transform->GetPosition();

		if (CInput::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = transform->GetRotation();
			rot.z += 10.0f * CTimeMgr::DeltaTime();
			transform->SetRotation(rot);
		}

		if (CInput::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos.z += 3.f * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos.z -= 3.f * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos.x -= 3.f * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos.x += 3.f * CTimeMgr::DeltaTime();
		}


		transform->SetPosition(pos);
	}

	void CPlayerScript::fixedUpdate()
	{
	}

	void CPlayerScript::render()
	{
	}

}