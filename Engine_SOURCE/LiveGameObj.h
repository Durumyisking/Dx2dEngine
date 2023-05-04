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
		renderer::AnimationCB AnimData;
		int Inverse; // 1이면 l 0이면 R

	};

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

		void RewindFlip();
		void ReplayFlip();

		renderer::AnimationCB GetCurrentAnimData() const { return mCurrentAnimData; }


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

    };

}

