#pragma once
#include "GameObj.h"
#include "Animator.h"
#include "RigidBody.h"


namespace dru
{

	struct FrameCapturedData
	{
	public:
		FrameCapturedData() : Texture(nullptr), AnimData{} {};
		~FrameCapturedData() {};

		std::shared_ptr<CTexture> Texture;
		Vector3 Position;
		renderer::AnimationCB AnimData;

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

		bool IsRewinding() const { return mbRewind; };


		renderer::AnimationCB GetCurrentAnimData() const { return mCurrentAnimData; }


	protected:
		std::stack<FrameCapturedData> mFrameCaptureData;
		FrameCapturedData mFrameCapture;

		renderer::AnimationCB mCurrentAnimData;
		bool mbRewind;

		bool mOnStair;
		float mMoveDegree;
		const float mRewindTime;

    };

}

