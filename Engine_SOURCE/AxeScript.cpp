#include "AxeScript.h"
#include "TimeMgr.h"
#include "GameObj.h"
#include "Axe.h"
#include "Kissyface.h"
#include "KissyfaceScript.h"
#include "CameraScript.h"

namespace dru
{
	CAxeScript::CAxeScript()
		: mAxe(nullptr)
		, mTransform(nullptr)
		, mAudioSource(nullptr)
		, mDefaultPos(Vector3::Zero)
		, mKissyfaceCenter(Vector3::Zero)
		, mAngle(10.f)
		, mInitialRadius(0.f)
		, mRadiusIncrement(0.05f)
		, mState{}
	{
		mDefaultPos = { 0.36f, -0.45f, 0.f };

	}

	CAxeScript::~CAxeScript()
	{
	}

	void CAxeScript::Initialize()
	{
		mAxe = dynamic_cast<CAxe*>(GetOwner());
		mTransform = GetOwner()->GetComponent<CTransform>();
		mAudioSource = GetOwner()->GetComponent<CAudioSource>();
	}

	void CAxeScript::update()
	{
		if (GetState(eState::Rotate))
		{
			Rotate();
		}
		if (GetState(eState::Orbit))
		{
			Orbit();
		}
		if (GetState(eState::Fly) || GetState(eState::Recieve))
		{
			Fly();
		}


	}

	void CAxeScript::fixedUpdate()
	{
	}

	void CAxeScript::render()
	{

	}

	void CAxeScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_wall" == _oppo->GetName())
		{
			if (GetState(eState::Fly))
			{
				mState.reset();
				SetStateOn(eState::Stuck);
			}
		}
		if (L"col_monster" == _oppo->GetName())
		{
			if (GetState(eState::Recieve))
			{
				mState.reset();
			}
		}
		if (L"col_Player_Slash" == _oppo->GetName())
		{
			SetStateOff(eState::Fly);
			SetStateOn(eState::Recieve);

			mAudioSource->Play(L"kissyface_axeimpact");

			mAxe->GetKissyface()->GetScript<CKissyfaceScript>()->PlayBulletReflect(GetOwnerWorldPos());
			CTimeMgr::BulletTime(0.25f);

			// CamShake
			ShakeParams sp = {};
			sp.duration = 0.25f;
			sp.magnitude = 0.0500f;
			renderer::mainCamera->GetCamScript()->Shake(sp);
		}
	}

	void CAxeScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CAxeScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

	void CAxeScript::Rotate()
	{
		mTransform->AddRotationZ(mAngle);
	}

	void CAxeScript::Orbit()
	{
		mAngle += CTimeMgr::DeltaTime() * 20.f;

		float radius = 0.f;

		if (mAngle >= 20.f && 0.f == mInitialRadius)
		{
			mInitialRadius = 2.f;
			mRadiusIncrement = -mRadiusIncrement;
		}
		radius = mInitialRadius + mRadiusIncrement * mAngle;

		Vector3 Pos = GetOwnerPos();
		Pos.x = radius * cos(mAngle);
		Pos.y = radius * sin(mAngle);

		GetOwner()->SetPos(Pos);
	}

	void CAxeScript::Fly()
	{
		if (GetState(eState::Fly))
		{
			mTransform->AddPositionX(mDir.x * FLY_SPEED * CTimeMgr::DeltaTime());
		}
		else if (GetState(eState::Recieve))
		{
			mTransform->AddPositionX(mDir.x * -FLY_SPEED * CTimeMgr::DeltaTime());
		}
	}

	void CAxeScript::Reset()
	{
		GetOwner()->SetPosAbs(mDefaultPos);
		GetOwner()->SetRotation({ 0.f, 0.f, 270.f });
		mAngle = 10.f;
		mInitialRadius = 0.f;
		mRadiusIncrement = 0.05f;
		mDir = Vector3::Zero;
	}

}