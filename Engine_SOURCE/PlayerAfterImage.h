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

		CPlayer* GetOwner() const { return mOwner; }
		renderer::AnimationCB GetAnimCB() { return mPlayerFrameCaptures.AnimData; }
		void SetFrameCapturedData(FrameCapturedData& _FrameCapturedData) { mPlayerFrameCaptures = _FrameCapturedData; }

	private:
		FrameCapturedData mPlayerFrameCaptures;
		CPlayer* mOwner;
    };
}