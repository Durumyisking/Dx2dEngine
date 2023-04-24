#include "LiveGameObj.h"
#include "SceneMain.h"

namespace dru
{
	CLiveGameObj::CLiveGameObj()
		: mFrameCaptureData{}
		, mFrameCapture{}
		, mbRewind(false)
		, mOnStair(false)
		, mMoveDegree(0.f)
		, mCurrentAnimData{}
		, mRewindTime(3.f)
	{
		mObjectType = eObjectType::Live;
	}

	CLiveGameObj::~CLiveGameObj()
	{
		while (!mFrameCaptureData.empty())
		{
			mFrameCaptureData.pop();
		}
	}

	void CLiveGameObj::Initialize()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->Initialize();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
		}
	}

	void CLiveGameObj::update()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->update();
		}
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->update();
		}
	}

	void CLiveGameObj::fixedUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedUpdate();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->fixedUpdate();
		}
	}

	void CLiveGameObj::render()
	{
		if (mbRewind)
		{
			CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
			CStage* stage = scene->GetCurrentStage();
			RewindOperate(stage->GetElapsedTime());
		}

		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->render();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->render();
		}
	}

	void CLiveGameObj::FrameCaptureOperate()
	{
		MakeFrameCaptureData();
		PushFrameCapturedData();
	}

	void CLiveGameObj::PushFrameCapturedData()
	{
		mFrameCaptureData.push(mFrameCapture);
	}

	void CLiveGameObj::RewindOperate(float _ElapsedTime)
	{
		if (mFrameCaptureData.empty())
			mbRewind = false;
		else
		{
			Vector3 p = mFrameCaptureData.top().Position;
			mCurrentAnimData = mFrameCaptureData.top().AnimData;
			SetPos(p);


			if (_ElapsedTime > mRewindTime)
			{
				int a = (_ElapsedTime / mRewindTime) + 1;

				for (int i = 0; i < a; i++)
				{
					if (!mFrameCaptureData.empty())
						mFrameCaptureData.pop();
				}
			}
			else
			{
				mFrameCaptureData.pop();
			}
		}
	}

	void CLiveGameObj::MakeFrameCaptureData()
	{
		mFrameCapture.Position = GetComponent<CTransform>()->GetPosition();
		mFrameCapture.Texture = GetComponent<CSpriteRenderer>()->GetMaterial()->GetTexture();
		mFrameCapture.AnimData = GetComponent<CAnimator>()->GetCurrentAnimation()->GetAnimationData();
	}

	bool CLiveGameObj::FrameCaptureCheck()
	{
		CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);

		if ((eStageState::LoadEnd == scene->GetCurrentStage()->GetReadyState()) && !mbRewind)
		{
			// 불릿타임 틀어져있으면 3프레임당 1번 캡쳐를한다.
			if (CTimeMgr::IsFramePass())
			{
				return true;
			}
		}
		return false;
	}


}