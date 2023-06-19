#pragma once
#include "LiveGameObj.h"
#include "PlayerAfterImage.h"

namespace dru
{
    class CBoss :
        public CLiveGameObj
    {
	public:
		CBoss();
		virtual ~CBoss();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();

		void Disable();

	protected:
		UINT mMaxHp;
		UINT mHp;


	public:
		void SetHp(UINT _Value) { mHp = _Value; }
		void Damaged() { mHp--; }
		void ResetHp() { mHp = mMaxHp; }
		UINT GetHp() const { return mHp; }
		bool IsDeadState();

    };
}
