#include "OutWall.h"


namespace dru
{
	COutWall::COutWall()
		: CPlatforms(ePlatformType::OutWall)
	{
	}

	COutWall::~COutWall()
	{
	}

	void COutWall::Initialize()
	{
		CGameObj::Initialize();
	}

	void COutWall::update()
	{
		CGameObj::update();
	}

	void COutWall::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void COutWall::render()
	{
		CGameObj::render();
	}


}