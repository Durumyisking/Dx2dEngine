#include "Layer.h"


namespace dru
{
	CLayer::CLayer()
	{
	}

	CLayer::~CLayer()
	{
	}

	void CLayer::init()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			Obj->init();
		}
	}

	void CLayer::update()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			Obj->update();
		}
	}

	void CLayer::fixedupdate()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			Obj->fixedupdate();
		}
	}

	void CLayer::render()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			Obj->render();
		}
	}

	void CLayer::AddGameObject(const CGameObj* _GameObj)
	{
	}

}