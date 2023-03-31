#include "CameraScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "Camera.h"

#include "Scene.h"
#include "SceneMain.h"
#include "SceneMgr.h"
#include "Stage.h"

namespace dru
{
	CCameraScript::CCameraScript()
		: mCameraObject(nullptr)
		, mDir{}
		, mDirBlock{}
		, mbCamFollowPlayerX(false)
		, mbCamFollowPlayerY(false)

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
			if(mDirBlock[(UINT)eDir::UP] == false)
				LookAt += 10.f * transform->Up() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::UP] = true;
		}
		if (CInput::GetKeyState(eKeyCode::J) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::DOWN] == false)
				LookAt += 10.f * -transform->Up() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::DOWN] = true;
		}
		if (CInput::GetKeyState(eKeyCode::H) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::LEFT] == false)
				LookAt += 10.f * -transform->Right() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::LEFT] = true;
		}
		if (CInput::GetKeyState(eKeyCode::K) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::RIGHT] == false)
				LookAt += 10.f * transform->Right() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::RIGHT] = true;
		}
		if (CInput::GetKeyState(eKeyCode::P) == eKeyState::DOWN)
		{
			LookAt -= 100.f * transform->Forward() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::O) == eKeyState::DOWN)
		{
			LookAt += 100.f * transform->Forward() * CTimeMgr::DeltaTime();
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
		else
		{
			if (mbCamFollowPlayerX)
			{
				renderer::mainCamera->GetOwner()->MoveToTarget_Smooth(mPlayer, 0.1, eDir::LEFT);
			}
			if (mbCamFollowPlayerY)
			{
				renderer::mainCamera->GetOwner()->MoveToTarget_Smooth(mPlayer, 0.1, eDir::UP);
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

	void CCameraScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_outWallside" == _oppo->GetName())
		{

			// Ä·º¸´Ù ¿ÞÂÊÀÌ¸é
			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
			{
				mDirBlock[(UINT)eDir::LEFT] = true;
				mbCamFollowPlayerX = false;
			}
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x <  _oppo->GetColliderPos().x)
			{
				mDirBlock[(UINT)eDir::RIGHT] = true;
				mbCamFollowPlayerX = false;
			}
		}
	}

	void CCameraScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CCameraScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_outWallside" == _oppo->GetName())
		{
			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
			{
				mDirBlock[(UINT)eDir::LEFT] = false;
//				dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->CamFollowOffX();
			}
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
			{
				mDirBlock[(UINT)eDir::RIGHT] = false;
//				dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->CamFollowOffX();
			}


			//if (mDir[(UINT)eDir::UP] == true || mDir[(UINT)eDir::DOWN] == true)
			//	dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->CamFollowOnY();
			//if (mDir[(UINT)eDir::LEFT] == true || mDir[(UINT)eDir::RIGHT] == true)
			//	dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->CamFollowOnX();
		}
	}


}