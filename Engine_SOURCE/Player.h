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


		void RemoveAfterImage();


	private:
		void MakeAfterImage();
		void FlipAfterImage(CPlayerAfterImage* _AfterImage);
		void SetAfterImage(CPlayerAfterImage* _AfterImage);

	private:
		std::deque<CPlayerAfterImage*> mAfterImages; // 매번 모든 원소의 쉐이더에 보낼 인덱스를 수정해야함으로 일반 큐보다는 원형큐가 적합하다.
		UINT mAfterImageCount;

	public:
		void SetAfterImageCount(UINT _Count) { mAfterImageCount = _Count; }
		UINT GetAfterImageCount() const { return mAfterImageCount; }
	};
}