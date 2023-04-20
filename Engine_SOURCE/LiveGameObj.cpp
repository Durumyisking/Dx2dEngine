#include "LiveGameObj.h"


namespace dru
{
	CLiveGameObj::CLiveGameObj()
		: mOnStair(false)
		, mMoveDegree(0.f)
	{
	}

	CLiveGameObj::~CLiveGameObj()
	{
	}

	void CLiveGameObj::Initialize()
	{
		CGameObj::Initialize();
	}

	void CLiveGameObj::update()
	{
		CGameObj::update();
	}

	void CLiveGameObj::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CLiveGameObj::render()
	{
		CGameObj::render();
	}


}