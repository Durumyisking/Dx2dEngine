#include "Stair.h"

namespace dru
{
	CStair::CStair()
		: CPlatforms(ePlatformType::Stair)
		, mSlopeDegree(0.f)
	{
	}

	CStair::~CStair()
	{
	}

	void CStair::Initialize()
	{
		CGameObj::Initialize();
	}

	void CStair::update()
	{
		mSlopeDegree =  GetComponent<CTransform>()->GetRotation().z;

		CGameObj::update();
	}

	void CStair::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CStair::render()
	{
		CGameObj::render();
	}

}
