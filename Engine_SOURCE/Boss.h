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

	private:
		UINT mHP;


	public:
		void SetHp(UINT _Value) { mHP = _Value; }
		UINT GetHP() const { return mHP; }

    };
}
