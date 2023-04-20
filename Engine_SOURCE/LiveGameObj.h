#pragma once
#include "GameObj.h"

namespace dru
{
    class CLiveGameObj :
        public CGameObj
    {
	public:
		CLiveGameObj();
		virtual ~CLiveGameObj();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


		bool IsOnStair() { return mOnStair; }
		void SetStairOn(float _moveDegree)
		{
			mOnStair = true;
			mMoveDegree = _moveDegree;
		}
		void SetStairOff()
		{
			mOnStair = false;
			mMoveDegree = 0.f;
		}
		float GetSlope() const { return mMoveDegree; }

	public:
		bool mOnStair;
		float mMoveDegree;

    };

}

