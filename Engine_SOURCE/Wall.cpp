#include "Wall.h"

namespace dru
{
	CWall::CWall()
		: CPlatforms(ePlatformType::Wall)
	{
	}

	CWall::~CWall()
	{
	}

	void CWall::Initialize()
	{
		CGameObj::Initialize();
	}

	void CWall::update()
	{
		CGameObj::update();
	}

	void CWall::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CWall::render()
	{
		CGameObj::render();
	}

}
