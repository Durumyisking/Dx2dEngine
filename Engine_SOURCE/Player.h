#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CPlayerAfterImage;
	class CPlayer :
		public CLiveGameObj
	{

	public:
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void PushFrameCapturedData();
		virtual void RewindOperate(float _ElapsedTime);
		virtual void MakeFrameCaptureData();

		void RemoveAfterImage();
		void SetAfterImageCount(int _Count) { mAfterImageCount = _Count; }

	private:
		void MakeAfterImage();
		void FlipAfterImage(CPlayerAfterImage* _AfterImage);
		void SetAfterImage(CPlayerAfterImage* _AfterImage);

	private:
		std::queue<CPlayerAfterImage*> mAfterImages;
		int mAfterImageCount;
	};
}