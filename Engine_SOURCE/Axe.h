#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CAxe :
		public CLiveGameObj
	{
	public:
		CAxe();
		virtual ~CAxe();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void Spin();
		void Reset();

	private:
		CTransform* mTransform;
		Vector3 mDefaultPos;
		Vector3 mKissyfaceCenter;

		float mAngle;
		float mInitialRadius;
		float mRadiusIncrement;

		int mFramePass;


	public:
		void SetKissyfaceCenter(Vector3 _Pos) { mKissyfaceCenter = _Pos; }
		float CalculateRadius(float angle, float initialRadius, float radiusIncrement, bool reverse);
	};
}