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
		, mTransform(nullptr)
		, mTarget(nullptr)
		, mPlayer(nullptr)
		, mSpeed(0.f)
		, mCamStep(0.f)
		, mLookAt(Vector3::Zero)

	{
	}

	CCameraScript::~CCameraScript()
	{
	}

	void CCameraScript::Initialize()
	{
		mCameraObject = GetOwner()->GetComponent<CCamera>();
		mTransform = GetOwner()->GetComponent<CTransform>();
	}

	void CCameraScript::update()
	{
		mLookAt = mTransform->GetPosition();

		mTarget = mCameraObject->mTargetObj;


		mCamStep = mSpeed * CTimeMgr::DeltaTime();

		KeyBoardMove();

		TargetMove();

		mTransform->SetPosition(mLookAt);
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

	void CCameraScript::KeyBoardMove()
	{
		// Keyboard Move

		if (CInput::GetKeyState(eKeyCode::U) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::UP] == false)
				mLookAt += 10.f * mTransform->Up() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::UP] = true;
		}
		if (CInput::GetKeyState(eKeyCode::J) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::DOWN] == false)
				mLookAt += 10.f * -mTransform->Up() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::DOWN] = true;
		}
		if (CInput::GetKeyState(eKeyCode::H) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::LEFT] == false)
				mLookAt += 10.f * -mTransform->Right() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::LEFT] = true;
		}
		if (CInput::GetKeyState(eKeyCode::K) == eKeyState::DOWN)
		{
			if (mDirBlock[(UINT)eDir::RIGHT] == false)
				mLookAt += 10.f * mTransform->Right() * CTimeMgr::DeltaTime();

			mDir[(UINT)eDir::RIGHT] = true;
		}
		if (CInput::GetKeyState(eKeyCode::P) == eKeyState::DOWN)
		{
			mLookAt -= 100.f * mTransform->Forward() * CTimeMgr::DeltaTime();
		}
		if (CInput::GetKeyState(eKeyCode::O) == eKeyState::DOWN)
		{
			mLookAt += 100.f * mTransform->Forward() * CTimeMgr::DeltaTime();
		}
	}

	void CCameraScript::TargetMove()
	{
		// Target Move
		if (mTarget)
		{
			if (mTarget->IsDead())
				mTarget = nullptr;
			else
			{
				if (mCamStep > mCameraObject->mFarDist)
				{
					mLookAt.x = mCameraObject->mTargetObj->GetPos().x;
					mLookAt.y = mCameraObject->mTargetObj->GetPos().y;

					mCameraObject->mTargetObj = nullptr;
				}
				else
				{
					mLookAt += mCameraObject->mCamDir * mCamStep;
				}
			}
		}
		else
		{
			if (mbCamFollowPlayerX)
			{
				mLookAt = renderer::mainCamera->GetOwner()->MoveToTarget_Smooth_vector3(mPlayer, 0.2, eDir::LEFT);
			}
			if (mbCamFollowPlayerY)
			{
				mLookAt = renderer::mainCamera->GetOwner()->MoveToTarget_Smooth_vector3(mPlayer, 0.2, eDir::UP);
			}
		}
	}


}