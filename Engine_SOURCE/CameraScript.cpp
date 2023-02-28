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

		mCameraObject->mAccTime += CTimeMgr::DeltaTime();

		// Target Move
		if (target)
		{
			if (target->IsDead())
				target = nullptr;
			else
			{
				LookAt += mCameraObject->mCamDir * mCameraObject->mCamSpeed * CTimeMgr::DeltaTime();
			}
		}

		// Keyboard Move

		if (CInput::GetKeyState(eKeyCode::U) == eKeyState::PRESSED)
		{
			LookAt += 3.f * transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::J) == eKeyState::PRESSED)
		{
			LookAt += 3.f * -transform->Up() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::H) == eKeyState::PRESSED)
		{
			LookAt += 3.f * -transform->Right() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::K) == eKeyState::PRESSED)
		{
			LookAt += 3.f * transform->Right() * CTimeMgr::DeltaTime();
		}


		if (mCameraObject->mTime <= mCameraObject->mAccTime) // 정해진 캠 이동 시간이 초과하면
		{
			LookAt.x = mCameraObject->mTargetObj->GetPos().x;
			LookAt.y = mCameraObject->mTargetObj->GetPos().y;

			mCameraObject->mAccTime = 0.f;
		}



		transform->SetPosition(LookAt);
	}

	void CCameraScript::fixedupdate()
	{
	}

	void CCameraScript::render()
	{
	}


}