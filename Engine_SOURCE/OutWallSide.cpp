#include "OutWallSide.h"


namespace dru
{
	COutWallSide::COutWallSide()
		: CPlatforms(ePlatformType::OutWallSide)
	{
	}

	COutWallSide::~COutWallSide()
	{
	}

	void COutWallSide::Initialize()
	{
		CGameObj::Initialize();
	}

	void COutWallSide::update()
	{
		CGameObj::update();
	}

	void COutWallSide::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void COutWallSide::render()
	{
		CGameObj::render();
	}

}