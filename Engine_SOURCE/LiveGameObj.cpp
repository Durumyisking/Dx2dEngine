#include "LiveGameObj.h"
#include "SceneMain.h"
#include "AfterImageRenderer.h"

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
		, mAfterImages{}
		, mAfterImageCount(0)
		, mAfterImageColor(Vector4::Zero)
	{
		mObjectType = eObjectType::Live;
	}

	CLiveGameObj::~CLiveGameObj()
	{
		while (!mFrameCaptureData.empty())
		{
			mFrameCaptureData.pop_back();
		}
		while (!mAfterImages.empty())
		{
			mAfterImages.front()->Die();
			mAfterImages.pop_front();
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

	void CLiveGameObj::rewindRender()
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
		{
			mbRewind = false;
			if (eLayerType::FX == GetLayerType())
			{
				Die();
				GetCurrentStage()->PopRewindObject(this);
			}
			if (eLayerType::BackGround == GetLayerType())
			{
				Die();
				GetCurrentStage()->PopRewindObject(this);
			}
		}
		else
		{
			if (mFrameCaptureData.front().FrameNumber == GetCurrentStage()->GetFrameCount())
			{
			
				if (mFrameCaptureData.front().RenderingBlock)
				{
					RenderingBlockOn();
				}
				else
				{
					RenderingBlockOff();
				}

				// ĸ��ť�� front���� pop�ϸ鼭 �βٲ���
				mCurrentAnimData = mFrameCaptureData.front().AnimData;

				RewindFlip();
				SetRewindTransform();

				if (_ElapsedTime > mRewindTime)
				{
					// ElapsedTime�� ���̵� RewindTime �ʸ�ŭ ������ ����
					// ElapsedTime�� �������� �ѹ��� ���� ĸ�� �����͵��� pop���ش�.
					int a = static_cast<int>((_ElapsedTime / mRewindTime) + 1.f);

					for (int i = 0; i < a; i++)
					{
						if (!mFrameCaptureData.empty())
						{
							mFrameCaptureData.pop_front();
						}
					}
				}
				else
				{
					mFrameCaptureData.pop_front();
				}
			}
		}
	}

	void CLiveGameObj::ReplayOperate()
	{
		if (mFrameCaptureData.empty())
		{
			mbReplay = false;
			if (eLayerType::FX == GetLayerType() || eLayerType::BackGround == GetLayerType())
			{
				Die();
				GetCurrentStage()->PopRewindObject(this);
			}
		}
		else
		{
			if (mFrameCaptureData.back().FrameNumber == GetCurrentStage()->GetFrameCount())
			{
				RenderingBlockOff();
				// ĸ��ť�� back���� pop
				mCurrentAnimData = mFrameCaptureData.back().AnimData;

				ReplayFlip();
				SetReplayTransform();
				mFrameCaptureData.pop_back();
			}
		}
	}

	void CLiveGameObj::SetRewindTransform()
	{
		Vector3 pos = mFrameCaptureData.front().Position;
		Vector3 scale = mFrameCaptureData.front().Scale;
		Vector3 rot = mFrameCaptureData.front().Rotation;
		SetPos(pos);
	//	SetScale(scale);
		SetRotation(rot);
	}

	void CLiveGameObj::SetReplayTransform()
	{
		Vector3 pos = mFrameCaptureData.back().Position;
		Vector3 scale = mFrameCaptureData.back().Scale;
		Vector3 rot = mFrameCaptureData.back().Rotation;
		SetPos(pos);
//		SetScale(scale);
		SetRotation(rot);
	}

	void CLiveGameObj::MakeFrameCaptureData()
	{
		mFrameCapture.Position = GetComponent<CTransform>()->GetPosition();
		mFrameCapture.WorldPosition = GetComponent<CTransform>()->GetWorldPosition();
		mFrameCapture.Scale= GetComponent<CTransform>()->GetScale();
		mFrameCapture.Rotation= GetComponent<CTransform>()->GetRotation();
		mFrameCapture.Texture = GetComponent<CSpriteRenderer>()->GetMaterial()->GetTexture();
		mFrameCapture.FrameNumber = GetCurrentStage()->GetFrameCount();

		if (GetComponent<CAnimator>())
		{
			mFrameCapture.AnimData = GetComponent<CAnimator>()->GetCurrentAnimation()->GetAnimationData();
		}
		if (IsLeft())
		{
			mFrameCapture.Inverse = -1;
		}
		else
		{
			mFrameCapture.Inverse = 1;
		}

		if (IsRenderingBlock())
		{
			mFrameCapture.RenderingBlock = true;
		}
		else
		{
			mFrameCapture.RenderingBlock = false;
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
	void CLiveGameObj::RemoveAfterImage()
	{
		while (!mAfterImages.empty())
		{
			mAfterImages.front()->Die();
			mAfterImages.pop_front();
		}
	}
	void CLiveGameObj::MakeAfterImage(bool _IsAnimation, float _AnimSize)
	{
		CAfterImage* afterImage = object::Instantiate<CAfterImage>(eLayerType::AfterImage, L"AfterImage");
		afterImage->SetScale(GetComponent<CTransform>()->GetWorldScale());

		SetAfterImage(afterImage);
		afterImage->SetOwner(this);
		afterImage->Initialize();
		afterImage->GetComponent<CAfterImageRenderer>()->SetMultableColor(mAfterImageColor);

		if (_IsAnimation)
		{
			afterImage->CreateAnimator(_AnimSize);
		}

		FlipAfterImage(afterImage);
	}
	void CLiveGameObj::FlipAfterImage(CAfterImage* _AfterImage)
	{
		_AfterImage->SetFrameCapturedData(mFrameCapture);

		if (IsLeft())
		{
			_AfterImage->SetLeft();
		}
		else
		{
			_AfterImage->SetRight();
		}
		_AfterImage->Flip();
	}
	void CLiveGameObj::SetAfterImage(CAfterImage* _AfterImage)
	{
		if (mAfterImageCount < mAfterImages.size())
		{
			mAfterImages.front()->Die();
			mAfterImages.pop_front();

			if (!mAfterImages.empty()) // �ܻ� ���� 0�϶��� 2���� pop�ϸ� �ȵ�
			{
				mAfterImages.front()->Die();
				mAfterImages.pop_front();
			}
		}

		mAfterImages.push_back(_AfterImage);

		// �ܻ� �ε���
		for (UINT i = 0; i < mAfterImages.size(); i++)
		{
			mAfterImages[i]->SetIndex(i);
		}
	}

}