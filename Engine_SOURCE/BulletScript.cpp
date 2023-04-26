#include "BulletScript.h"
#include "TimeMgr.h"
#include "Bullet.h"

namespace dru
{
	CBulletScript::CBulletScript()
		: mBullet(nullptr)
		, mElapsedTime(0.f)
		, mDefaultBulletScale(Vector3::Zero)	
		, mbScalingDone(false)
	{
	}

	CBulletScript::~CBulletScript()
	{
	}

	void CBulletScript::Initialize()
	{
		mBullet = dynamic_cast<CBullet*>(GetOwner());
	}

	void CBulletScript::update()
	{
		mElapsedTime += CTimeMgr::DeltaTime();
		BulletMove();
	}

	void CBulletScript::fixedUpdate()
	{
	}

	void CBulletScript::render()
	{
	}

	void CBulletScript::OnCollisionEnter(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

	void CBulletScript::BulletScaling()
	{
		if (!mbScalingDone)
		{
			// 0.5초동안 줄어들게
			float Ratio = 1 - mElapsedTime / 0.5f;

			float NewX = mDefaultBulletScale.x * Ratio;
			GetOwner()->SetScale({ NewX, mDefaultBulletScale.y , mDefaultBulletScale.z });
			GetOwner()->SetPos({ GetOwnerPos().x - (mDefaultBulletScale.x - NewX) * 0.5f, GetOwnerPos().y, GetOwnerPos().z });
			mbScalingDone = true;
		}
	}

	void CBulletScript::BulletMove()
	{
		Vector3 dir = mBullet->GetDir();
		Vector3 pos = GetOwnerPos();

		pos += dir * CTimeMgr::DeltaTime() * mBullet->GetSpeed();

		GetOwner()->SetPos(pos);
	}

	void CBulletScript::BulletReflect()
	{
	}

}	