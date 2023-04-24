#pragma once
#include "GameObj.h"
#include "LiveGameObj.h"

namespace dru
{
	class CPlayer;
    class CPlayerAfterImage :
        public CGameObj
    {
	public:
		CPlayerAfterImage();
		virtual ~CPlayerAfterImage();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

	private:
		FrameCapturedData mPlayerFrameCaptures;
		CPlayer* mOwner;
		UINT mIndex;
		float mAlpha;

	public:
		UINT GetIndex() { return mIndex; }
		void SetIndex(UINT _Idx) { mIndex = _Idx; }
		
		CPlayer* GetOwner() const { return mOwner; }
		void SetOwner(CPlayer* _Owner) { mOwner = _Owner; }


		renderer::AnimationCB GetAnimCB() { return mPlayerFrameCaptures.AnimData; }
		void SetFrameCapturedData(FrameCapturedData& _FrameCapturedData) { mPlayerFrameCaptures = _FrameCapturedData; }


    };
}