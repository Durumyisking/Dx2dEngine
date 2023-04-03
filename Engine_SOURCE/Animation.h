#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Texture.h"

using namespace dru::math;
using namespace dru::graphics;

namespace dru
{

	class CAnimation : public CEntity
	{
	public:
		struct Sprite
		{
			Vector2 LT;
			Vector2 size;	// 잘라낼 픽셀 크기
			Vector2 offset;
			Vector2 altasSize;
			float duration; // 이미지 프레임당 시간 간격

			Sprite()
				: LT(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, altasSize(Vector2::Zero)
				, duration(0.1f)
			{

			}
		};

		CAnimation();
		~CAnimation();
		
		UINT update();
		void fixedUpdate();
		void render();

		void Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _spriteLength, Vector2 _Ratio, float _duration, bool _Reverse);
		void BindShader();
		void Clear();
		void Reset();
		void SetDuration(float _Value);

		bool IsCompleted() { return mbComplete; }

		std::wstring& GetAnimationName() { return mAnimationName; }

	private:
		class CAnimator* mAnimator;
		std::wstring mAnimationName;

		std::shared_ptr<CTexture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
		bool mbReversePlay;
		UINT mSpriteLength;

	};
}

