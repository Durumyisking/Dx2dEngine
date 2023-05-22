#include "BeamScript.h"
#include "GameObj.h"
#include "TimeMgr.h"
#include "CameraScript.h"

namespace dru
{
	CBeamScript::CBeamScript()
		: mBeam(nullptr)
		, mbLaserShoot(false)
		, mbLaserShooted(false)
		, mLaserOperateTimer(0.f)
	{
	}

	CBeamScript::~CBeamScript()
	{
	}

	void CBeamScript::Initialize()
	{
	}

	void CBeamScript::update()
	{
		if (mbLaserShoot)
		{
			mLaserOperateTimer += CTimeMgr::DeltaTime();
			mBeam->GetComponent<CTransform>()->AddScaleX(CTimeMgr::DeltaTime() * -0.5f);

			if (0.2f < mLaserOperateTimer)
			{
				mBeam->GetComponent<CSpriteRenderer>()->ChangeColor(ORANGE);
			}
			if (0.3f < mLaserOperateTimer)
			{
				mBeam->GetComponent<CSpriteRenderer>()->ChangeColor(PEARL);
			}
			if (0.5f < mLaserOperateTimer)
			{
				mbLaserShoot = false;
				mLaserOperateTimer = 0.f;
				mBeam->GetComponent<CTransform>()->SetScaleX(0.25f);
				mBeam->RenderingBlockOn();
			}
		}
	}

	void CBeamScript::fixedUpdate()
	{
	}

	void CBeamScript::render()
	{
	}

	void CBeamScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_player" == _oppo->GetName())
		{
			mBeam->RenderingBlockOff();
			mBeam->GetComponent<CSpriteRenderer>()->ChangeColor(PEARL);
			mbLaserShoot = true;
			mbLaserShooted = true;
		}

	}

	void CBeamScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBeamScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

}