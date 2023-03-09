#include "PlayerScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "RigidBody.h"

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

#pragma region pos
		CRigidBody* rigidebody = GetOwner()->GetComponent<CRigidBody>();

		Vector3 pos = transform->GetPosition();

		if (CInput::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = transform->GetRotation();
			rot.z += 10.0f * CTimeMgr::DeltaTime();
			transform->SetRotation(rot);
		}

		if (CInput::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += 2.5f * transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos -= 2.5f * transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			rigidebody->AddVelocity(transform->Right() * -10.f);
		}
		if (CInput::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			rigidebody->AddVelocity(transform->Right() * 10.f);
		}
		transform->SetPosition(pos);

#pragma endregion

#pragma region rot
		
		Vector3 MousePos;
		MousePos = CInput::GetMousePosition();

		Vector3 rotation = transform->GetRotation();
		rotation.z = atan2(MousePos.y - pos.y, MousePos.x - pos.x);

		transform->SetRotation(rotation);

#pragma endregion

//		transform->SetScale(Vector3( - 1.f, 1.f, 1.f));
	}

	void CPlayerScript::fixedUpdate()
	{
	}

	void CPlayerScript::render()
	{
	}

}