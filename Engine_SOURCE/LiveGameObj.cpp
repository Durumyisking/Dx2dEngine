#include "LiveGameObj.h"
#include "SceneMain.h"

namespace dru
{
	CLiveGameObj::CLiveGameObj()
		: mFrameCaptureData{}
		, mFrameCapture{}
		, mbRewind(false)
		, mbReplay(false)
		, mOnStair(false)
		, mMoveDegree(0.f)
		, mCurrentAnimData{}
		, mCurrentInverse(0)
		, mRewindTime(3.f)
	{
		mObjectType = eObjectType::Live;
	}

	CLiveGameObj::~CLiveGameObj()
	{
		while (!mFrameCaptureData.empty())
		{
			mFrameCaptureData.pop_back();
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
		if (mbReplay)
		{
			ReplayOperate();
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
		mFrameCaptureData.push_front(mFrameCapture);
	}

	void CLiveGameObj::RewindOperate(float _ElapsedTime)
	{
		if (mFrameCaptureData.empty())
			mbRewind = false;
		else
		{
			// ĸ��ť�� front���� pop�ϸ鼭 �βٲ���
			mCurrentAnimData = mFrameCaptureData.front().AnimData;

			RewindFlip();

			Vector3 pos = mFrameCaptureData.front().Position;
			SetPos(pos);

			if (_ElapsedTime > mRewindTime)
			{
				// ElapsedTime�� ���̵� RewindTime �ʸ�ŭ ������ ����
				// ElapsedTime�� �������� �ѹ��� ���� ĸ�� �����͵��� pop���ش�.
				int a = static_cast<int>( (_ElapsedTime / mRewindTime) + 1.f);

				for (int i = 0; i < a; i++)
				{
					if (!mFrameCaptureData.empty())
						mFrameCaptureData.pop_front();
				}
			}
			else
			{
				mFrameCaptureData.pop_front();
			}
		}
	}

	void CLiveGameObj::ReplayOperate()
	{
		if (mFrameCaptureData.empty())
			mbReplay = false;
		else
		{
			// ĸ��ť�� back���� pop
			mCurrentAnimData = mFrameCaptureData.back().AnimData;
			ReplayFlip();
			Vector3 pos = mFrameCaptureData.back().Position;
			SetPos(pos);
			mFrameCaptureData.pop_back();
		}
	}

	void CLiveGameObj::MakeFrameCaptureData()
	{
		mFrameCapture.Position = GetComponent<CTransform>()->GetPosition();
		mFrameCapture.Texture = GetComponent<CSpriteRenderer>()->GetMaterial()->GetTexture();
		mFrameCapture.AnimData = GetComponent<CAnimator>()->GetCurrentAnimation()->GetAnimationData();
		if (IsLeft())
		{
			mFrameCapture.Inverse = -1;
		}
		else
		{
			mFrameCapture.Inverse = 1;
		}
	}

	bool CLiveGameObj::FrameCaptureCheck()
	{
		CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);

		if ((eStageState::LoadEnd == scene->GetCurrentStage()->GetReadyState()) && !mbRewind && !mbReplay)
		{
			// �Ҹ�Ÿ�� Ʋ���������� 3�����Ӵ� 1�� ĸ�ĸ��Ѵ�.
			if (CTimeMgr::IsFramePass())
			{
				return true;
			}
		}
		return false;
	}

	void CLiveGameObj::RewindFlip()
	{
		mCurrentInverse = mFrameCaptureData.front().Inverse;

		if (-1 == mCurrentInverse)
		{
			SetLeft();
		}
		else if (1 == mCurrentInverse)
		{
			SetRight();
		}
		Flip();
	}

	void CLiveGameObj::ReplayFlip()
	{
		mCurrentInverse = mFrameCaptureData.back().Inverse;

		if (-1 == mCurrentInverse)
		{
			SetLeft();
		}
		else if (1 == mCurrentInverse)
		{
			SetRight();
		}
		Flip();
	}
}