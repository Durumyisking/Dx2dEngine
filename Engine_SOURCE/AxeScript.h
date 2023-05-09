#pragma once
#include "Script.h"

#define FLY_SPEED 5.f

namespace dru
{
	enum class eState
	{
		Rotate,
		Orbit,
		Fly,
		Recieve,
		Stuck,

		End,
	};
	class CAxe;
	class CAxeScript :
		public CScript
	{
	public:
		CAxeScript();
		virtual ~CAxeScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		virtual void OnCollisionEnter(CCollider2D* _oppo);
		virtual void OnCollision(CCollider2D* _oppo);
		virtual void OnCollisionExit(CCollider2D* _oppo);

		void Rotate();
		void Orbit();

		void Fly();

		void Reset();

		bool GetState(eState _Type) { return mState[static_cast<UINT>(_Type)]; }
		void SetStateOn(eState _Type) { mState[static_cast<UINT>(_Type)] = true; }
		void SetStateOff(eState _Type) { mState[static_cast<UINT>(_Type)] = false; }


	private:
		CAxe* mAxe;
		CTransform* mTransform;
		Vector3 mDefaultPos;
		Vector3 mKissyfaceCenter;
		Vector3 mDir;

		float mAngle;
		float mInitialRadius;
		float mRadiusIncrement;

		std::bitset<static_cast<UINT>(eState::End)> mState;

	public:
		void SetKissyfaceCenter(Vector3 _Pos) { mKissyfaceCenter = _Pos; }

		void SetDir(Vector3 _Dir) { mDir = _Dir; }


	};
}
