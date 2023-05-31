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
		, mSpriteLength(0)
		, mbReversePlay(false)
		, mbCompleteEventPlayed(false)
	{

	}

	CAnimation::~CAnimation()
	{
	}

	UINT CAnimation::update()
	{
		if (mbComplete)
			return -1;

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

				return mIndex;

			}
			else
			{
				++mIndex;

				if (mSpriteSheet.size() <= mIndex)
				{
					mbComplete = true;
					mIndex = static_cast<int>(mSpriteSheet.size() - 1);

				}

				return mIndex;
			}	
		}
		return -1;
	}

	void CAnimation::fixedUpdate()
	{
	}

	void CAnimation::render()
	{
	}

	void CAnimation::Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _spriteLength, Vector2 _Ratio, float _duration, bool _Reverse)
	{
		mAnimationName = _name;
		mAtlas = _atlas;
		mbReversePlay = _Reverse;
		mSpriteLength = _spriteLength;

		float width = (float)_atlas->GetWidth();
		float height = (float)_atlas->GetHeight();

		size_t CollSkipCount = 0;
		for (size_t i = 0; i < _spriteLength; i++)
		{
			Sprite sprite = {};

			// 스프라이트의 LT가 + 사이즈가 width를 넘어가면 다음줄로 바꾼다.
			if (_leftTop.x + (_size.x * (float)i) >= width)
			{
				_leftTop.x = 0.f;
				_leftTop.y += _size.y;

				CollSkipCount = i;
			}

			// uv좌표로 넘기기 위해 width, height로 나눈다.
			sprite.LT = Vector2(
				(_leftTop.x + (_size.x * (float)(i - CollSkipCount))) / width,
				_leftTop.y / height
			);

			sprite.size = Vector2(fabs(_size.x) / width, fabs(_size.y) / height);
			sprite.offset = Vector2(_offset.x / width, _offset.y / height);
			sprite.duration = _duration;
			sprite.altasSize = Vector2(_Ratio.x / width, _Ratio.y / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void CAnimation::BindShader()
	{
		mAtlas->BindShaderResource(eShaderStage::PS, 12); // 아틀라스 srv에 바인딩

		CConstantBuffer* cb =  renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB data = {};

		data.type = (UINT)eAnimationType::SecondDimension;
		data.LT = mSpriteSheet[mIndex].LT;
		data.offset = mSpriteSheet[mIndex].offset;
		data.size = mSpriteSheet[mIndex].size;
		data.atlasSize = mSpriteSheet[mIndex].altasSize;

		cb->SetData(&data);
		cb->Bind(eShaderStage::PS);
	}

	void CAnimation::BindSpriteToShader(renderer::AnimationCB _Sprite)
	{
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		cb->SetData(&_Sprite);
		cb->Bind(eShaderStage::PS);
	}


	void CAnimation::Clear()
	{
		// Texture Clear
		CTexture::Clear(12);

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB data = {};
		data.type = (UINT)eAnimationType::None;

		cb->SetData(&data);
		cb->Bind(eShaderStage::PS);

	}

	void CAnimation::Reset()
	{
		mTime = 0.f;

		if(mbReversePlay)
			mIndex = mSpriteLength;
		else
			mIndex = 0;

		mbComplete = false;
		mbCompleteEventPlayed = false;
	}

	void CAnimation::SetDuration(float _Value)
	{
		for (size_t i = 0; i < mSpriteSheet.size(); i++)
		{	
			mSpriteSheet[i].duration = _Value;
		}
	}

	renderer::AnimationCB CAnimation::GetAnimationData()
	{
		renderer::AnimationCB data = {};
		
		data.type = (UINT)eAnimationType::SecondDimension;
		data.LT = mSpriteSheet[mIndex].LT;
		data.offset = mSpriteSheet[mIndex].offset;
		data.size = mSpriteSheet[mIndex].size;
		data.atlasSize = mSpriteSheet[mIndex].altasSize;

		return data;
	}

}

// 컨 k s if문 묶이
// 컨 j 함수찾기
// 컨 mm 코드블록 닫고 열기
// 컨트롤 RO 함수 구조변경
