#pragma once
#include "GameObj.h"

namespace dru
{

	struct FrameCapturedData
	{
	public:
		FrameCapturedData() : Texture(nullptr), TextureScale(Vector3::Zero) {};
		~FrameCapturedData() {};

		std::shared_ptr<CTexture> Texture;
		Vector3 Position;
		Vector3 TextureScale;

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
		virtual void PushFrameCpaturedData() = 0;

		virtual void RewindOperate() = 0;


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


	protected:
		std::stack<FrameCapturedData*> mFrameCaptureData;
		bool mbRewind;

		bool mOnStair;
		float mMoveDegree;


    };

}

