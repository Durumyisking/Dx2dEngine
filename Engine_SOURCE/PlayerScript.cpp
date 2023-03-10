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

#pragma region Run

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
			rigidebody->AddForce(transform->Right() * -50.f);
			GetOwner()->SetLeft();
		}
		if (CInput::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			rigidebody->AddForce(transform->Right() * 50.f);
			GetOwner()->SetRight();
		}


#pragma endregion

#pragma region Attack
		
		Vector3 MousePos = CInput::GetMousePosition();

		if (CInput::GetKeyDown(eKeyCode::LBTN) || CInput::GetKeyDown(eKeyCode::RBTN))
		{
			if ((MousePos.x / 100.f) < pos.x)
				GetOwner()->SetLeft();
			else
				GetOwner()->SetRight();
		}


#pragma endregion


		transform->SetPosition(pos);
		GetOwner()->Flip();
	}

	void CPlayerScript::fixedUpdate()
	{
	}

	void CPlayerScript::render()
	{
	}

}