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

		// 시간 체크
		mTime += CTimeMgr::DeltaTime();

		// 누적 시간이 해당 프레임의 유지시간을 넘어서면 
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