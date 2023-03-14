#include "Animation.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "Renderer.h"

namespace dru
{
	CAnimation::CAnimation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.f)
		, mbComplete(false)
		, mSpriteLength(0)
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
			if (mbReversePlay)
			{
				--mIndex;

				if (0 == mIndex)
				{
					mbComplete = true;
					mIndex = mSpriteLength;
				}
			}
			else
			{
				++mIndex;

				if (mSpriteSheet.size() <= mIndex)
				{
					mbComplete = true;
					mIndex = mSpriteSheet.size() - 1;

				}
			}
		}
	}

	void CAnimation::fixedUpdate()
	{
	}

	void CAnimation::render()
	{
	}

	void CAnimation::Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _spriteLength, float _duration, bool _Reverse)
	{
		mAnimationName = _name;
		mAtlas = _atlas;
		mbReversePlay = _Reverse;
		mSpriteLength = _spriteLength;

		float height = (float)_atlas->GetHeight();
		float width = (float)_atlas->GetWidth();

		for (size_t i = 0; i < _spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.LT = Vector2(
				(_leftTop.x + (_size.x * (float)i)) / width, 
				_leftTop.y / height
			);
			sprite.size = Vector2(_size.x / width, _size.y / height);
			sprite.offset = _offset;
			sprite.duration = _duration;
			sprite.altasSize = Vector2(35.f / width, 35.f / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void CAnimation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		CConstantBuffer* cb =  renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB data = {};

		data.type = (UINT)eAnimationType::SecondDimension;
		data.LT = mSpriteSheet[mIndex].LT;
		data.offset = mSpriteSheet[mIndex].offset;
		data.size = mSpriteSheet[mIndex].size;
		data.atlasSize = mSpriteSheet[mIndex].altasSize;

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);
	}

	void CAnimation::Clear()
	{
		// Texture Clear
		CTexture::Clear(12);

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB data = {};
		data.type = (UINT)eAnimationType::None;

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);

	}

	void CAnimation::Reset()
	{
		mTime = 0.f;

		if(mbReversePlay)
			mIndex = mSpriteLength;
		else
			mIndex = 0;

		mbComplete = false;
	}

}