#include "Floor.h"

namespace dru
{
	CFloor::CFloor()
		: CPlatforms(ePlatformType::Floor)
	{

	}

	CFloor::~CFloor()
	{
	}

	void CFloor::Initialize()
	{
		CGameObj::Initialize();
	}

	void CFloor::update()
	{
		CGameObj::update();
	}

	void CFloor::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CFloor::render()
	{
		CGameObj::render();
	}

}