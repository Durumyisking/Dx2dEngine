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
		std::deque<CPlayerAfterImage*> mAfterImages; // �Ź� ��� ������ ���̴��� ���� �ε����� �����ؾ������� �Ϲ� ť���ٴ� ����ť�� �����ϴ�.
		UINT mAfterImageCount;
		UINT mPrevAfterImageCount;

	public:
		void SetAfterImageCount(UINT _Count) 
		{
			mPrevAfterImageCount = mAfterImageCount;
			mAfterImageCount = _Count; 
		}
		UINT GetAfterImageMaxCount() const { return mAfterImageCount; }
		UINT GetAfterImageCount() const { return mAfterImages.size(); }
	};
}