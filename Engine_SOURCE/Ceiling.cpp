#include "Ceiling.h"


namespace dru
{
	CCeiling::CCeiling()
		: CPlatforms(ePlatformType::Ceiling)
	{
	}

	CCeiling::~CCeiling()
	{
	}

	void CCeiling::Initialize()
	{
		CGameObj::Initialize();
	}

	void CCeiling::update()
	{
		CGameObj::update();
	}

	void CCeiling::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CCeiling::render()
	{
		CGameObj::render();
	}

}