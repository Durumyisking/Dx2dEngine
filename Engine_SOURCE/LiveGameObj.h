#pragma once
#include "GameObj.h"
#include "Animator.h"
#include "RigidBody.h"


namespace dru
{

	struct FrameCapturedData
	{
	public:
		FrameCapturedData() : Texture(nullptr), Position{}, AnimData{}, Inverse(0) {};
		~FrameCapturedData() {};

		std::shared_ptr<CTexture> Texture;
		Vector3 Position;
		Vector3 WorldPosition;
		Vector3 Scale;
		Vector3 Rotation;
		renderer::AnimationCB AnimData;
		int Inverse; // 1이면 l 0이면 R
		bool RenderingBlock;
		UINT FrameNumber;

	};

	class CAfterImage;
    class CLiveGameObj :
        public CGameObj
    {
	public:
		CLiveGameObj();
		virtual ~CLiveGameObj();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void FrameCaptureOperate();

		void PushFrameCapturedData();
		void RewindOperate(float _ElapsedTime);
		void ReplayOperate();

		void SetRewindTransform();
		void SetReplayTransform();

		void MakeFrameCaptureData() ;

		bool FrameCaptureCheck();

		bool IsOnStair() { return mOnStair; }
		void SetStairOn(float _moveDegree)
		{
			mOnStair = true;
			mMoveDegree = _moveDegree;
		}
		void SetStairOff()
		{
			mOnStair = false;
			mMoveDegree = 0.f;
		}
		float GetSlope() const { return mMoveDegree; }

		void SetRewindOn() { mbRewind = true; }
		void SetRewindOff() { mbRewind = false; }
	
		void SetReplayOn() { mbReplay = true; }
		void SetReplayOff() { mbReplay = false; }

		bool IsRewinding() const { return mbRewind; };
		bool IsReplaying() const { return mbReplay; };

		bool IsRewindRePlaying() const { return mbRewind || mbReplay; }

		void RewindFlip();
		void ReplayFlip();

		renderer::AnimationCB GetCurrentAnimData() const { return mCurrentAnimData; }

		void RemoveAfterImage();

	protected:
		void MakeAfterImage(bool _IsAnimation, float _AnimSize = 0.f);
		void FlipAfterImage(CAfterImage* _AfterImage);
		void SetAfterImage(CAfterImage* _AfterImage);


	protected:
		std::deque<FrameCapturedData> mFrameCaptureData;
		FrameCapturedData mFrameCapture;

		renderer::AnimationCB mCurrentAnimData;
		int mCurrentInverse;

		bool mbRewind;
		bool mbReplay;

		bool mOnStair;
		float mMoveDegree;
		const float mRewindTime;

		std::deque<CAfterImage*> mAfterImages; // 매번 모든 원소의 쉐이더에 보낼 인덱스를 수정해야함으로 일반 큐보다는 원형큐가 적합하다.
		UINT mAfterImageCount;

		Vector4 mAfterImageColor;

	public:
		void SetAfterImageCount(UINT _Count)
		{
			mAfterImageCount = _Count;
		}
		UINT GetAfterImageMaxCount() const { return mAfterImageCount; }
		UINT GetAfterImageCount() const { return static_cast<UINT32>(mAfterImages.size()); }

		void SetAfterImageColor(Vector4 _Color) { mAfterImageColor = _Color; };
		void ResetAfterImageColor() { mAfterImageColor = Vector4::Zero; }

    };

}

