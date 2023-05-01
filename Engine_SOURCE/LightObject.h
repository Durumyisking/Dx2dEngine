#pragma once
#include "GameObj.h"

namespace dru
{
    class CLightObject :
        public CGameObj
    {
	public:
		CLightObject();
		virtual ~CLightObject();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void SetMaterial(std::wstring _MaterialName, Vector2 _MaterialSize);
		void PlayAnim(Vector2 _SpriteSize);

	private:
		CSpriteRenderer* mSpriteRenderer;
		CAnimator* mAnimator;
		std::shared_ptr<CMaterial> mMaterial;

		CGameObj* mPointLight;

		float mSwitchTime;
		float mElapsedTime;
		bool mIsBlinked;

    };
}

