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

	private:
		void PushFrameCapturedDataToAfterImage();


	private:
		std::queue<CPlayerAfterImage*> mAfterImages;
		int mAfterImageCount;
	};
}