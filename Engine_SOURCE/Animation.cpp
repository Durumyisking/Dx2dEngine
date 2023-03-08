#include "Animation.h"
#include "TimeMgr.h"

namespace dru
{
	CAnimation::CAnimation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.f)
		, mbComplete(false)
	{

	}

	CAnimation::~CAnimation()
	{
	}

	void CAnimation::update()
	{
		if (mbComplete)
			return;

		// �ð� üũ
		mTime += CTimeMgr::DeltaTime();

		// ���� �ð��� �ش� �������� �����ð��� �Ѿ�� 
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			++mIndex;

			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;

			}
		}
	}

	void CAnimation::fixedUpdate()
	{
	}

	void CAnimation::render()
	{
	}

	void CAnimation::Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _columnLength, UINT _spriteLength, float _duration)
	{
		mName = _name;
	}

	void CAnimation::BindShader()
	{
	}

	void CAnimation::Clear()
	{
	}

	void CAnimation::Reset()
	{
		mTime = 0.f;
		mIndex = 0;
		mbComplete = false;
	}

}