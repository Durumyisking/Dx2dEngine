#pragma once
#include "GameObj.h"
#include "LiveGameObj.h"

namespace dru
{
	class CPlayer;
    class CAfterImage :
        public CGameObj
    {
	public:
		CAfterImage();
		virtual ~CAfterImage();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	private:
		FrameCapturedData mFrameCaptures;
		std::shared_ptr<CMaterial> mMaterial;
		CLiveGameObj* mOwner;
		UINT mIndex;

	public:
		UINT GetIndex() { return mIndex; }
		void SetIndex(UINT _Idx) { mIndex = _Idx; }
		
		CLiveGameObj* GetOwner() const { return mOwner; }
		void SetOwner(CLiveGameObj* _Owner) { mOwner = _Owner; }


		renderer::AnimationCB GetAnimCB() { return mFrameCaptures.AnimData; }
		void SetFrameCapturedData(FrameCapturedData& _FrameCapturedData) { mFrameCaptures = _FrameCapturedData; }

		void CreateAnimator(float _AnimSize);
    };
}