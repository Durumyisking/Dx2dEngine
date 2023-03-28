#include "CameraScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "Camera.h"

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
		mCameraObject = GetOwner()->GetComponent<CCamera>();
	}

	void CCameraScript::update()
	{
		CTransform* transform = GetOwner()->GetComponent<CTransform>();
		Vector3 LookAt = transform->GetPosition();

		CGameObj* target = mCameraObject->mTargetObj;
		float	speed = mCameraObject->mCamSpeed;
		float	camStep = 0.f;


		camStep = speed * CTimeMgr::DeltaTime();

		// Keyboard Move

		if (CInput::GetKeyState(eKeyCode::U) == eKeyState::DOWN)
		{
			LookAt += 10.f * transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::J) == eKeyState::DOWN)
		{
			LookAt += 10.f * -transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::H) == eKeyState::DOWN)
		{
			LookAt += 10.f * -transform->Right() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::K) == eKeyState::DOWN)
		{
			LookAt += 10.f * transform->Right() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::P) == eKeyState::DOWN)
		{
			LookAt -= 10.f * transform->Forward() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::O) == eKeyState::DOWN)
		{
			LookAt += 10.f * transform->Forward() * CTimeMgr::DeltaTime();
		}


		// Target Move
		if (target)
		{
			if (target->IsDead())
				target = nullptr;
			else
			{
				if (camStep > mCameraObject->mFarDist)
				{
					LookAt.x = mCameraObject->mTargetObj->GetPos().x;
					LookAt.y = mCameraObject->mTargetObj->GetPos().y;

					mCameraObject->mTargetObj = nullptr;
				}
				else
				{
					LookAt += mCameraObject->mCamDir * camStep;
				}
			}
		}

		transform->SetPosition(LookAt);
	}

	void CCameraScript::fixedUpdate()
	{
	}

	void CCameraScript::render()
	{
	}


}