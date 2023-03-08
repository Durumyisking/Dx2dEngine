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
			Vector2 anchor;
			float duration; // 이미지 프레임당 시간 간격

			Sprite()
				: LT(Vector2::Zero)
				, size(Vector2::Zero)
				, anchor(Vector2::Zero)
				, duration(0.1f)
			{

			}
		};

		CAnimation();
		~CAnimation();
		
		void update();
		void fixedUpdate();
		void render();

		void Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _columnLength, UINT _spriteLength, float _duration);
		void BindShader();
		void Clear();
		void Reset();

		bool IsCompleted() { return mbComplete; }

		std::wstring& GetAnimationName() { return mName; }

	private:
		class CAnimator* mAnimator;
		std::wstring mName;

		std::shared_ptr<CTexture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;

	};
}

