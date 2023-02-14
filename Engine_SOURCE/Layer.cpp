#include "Layer.h"


namespace dru
{
	CLayer::CLayer()
	{
	}

	CLayer::~CLayer()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;

			delete Obj;
			Obj = nullptr;
		}

	}

	void CLayer::Initialize()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;
			Obj->Initialize();
		}
	}

	void CLayer::update()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;
			Obj->update();
		}
	}

	void CLayer::fixedupdate()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;
			Obj->fixedupdate();
		}
	}

	void CLayer::render()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;
			Obj->render();
		}
	}



	void CLayer::AddGameObject(CGameObj* _GameObj)
	{
		if (nullptr == _GameObj)	
			return;
		

		mGameObjs.push_back(_GameObj);
 	}

}