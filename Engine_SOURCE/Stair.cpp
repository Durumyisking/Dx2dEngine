#include "Stair.h"

namespace dru
{
	CStair::CStair()
		: CPlatforms(ePlatformType::Stair)
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
