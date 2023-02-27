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

			if(CGameObj::eState::Active == Obj->GetState())
				Obj->update();
		}
	}

	void CLayer::fixedupdate()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;

			if (CGameObj::eState::Active == Obj->GetState())
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

	void CLayer::destroy()
	{
		std::set<CGameObj*> DeadObjs;
		for (CGameObj* Obj : mGameObjs)
		{
			if (Obj->IsDead())
				DeadObjs.insert(Obj);
		}

		for (GameObjectIter iter = mGameObjs.begin(); iter != mGameObjs.end(); )
		{
			std::set<CGameObj*>::iterator deleteIter = DeadObjs.find(*iter);

			if (deleteIter != DeadObjs.end())
			{
				mGameObjs.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (CGameObj* Obj : DeadObjs)
		{
			delete Obj;
			Obj = nullptr;
		}

	}

	void CLayer::AddGameObject(CGameObj* _GameObj, eLayerType _Type)
	{
		if (nullptr == _GameObj)	
			return;
		
		_GameObj->SetLayerType(_Type);
		mGameObjs.push_back(_GameObj);
 	}

	std::vector<CGameObj*> CLayer::GetDontDestroyObjects()
	{
		std::vector<CGameObj*> donts;

		for (GameObjectIter iter = mGameObjs.begin();  iter != mGameObjs.end(); )
		{
			if (nullptr == (*iter))
				continue;

			if ((*iter)->IsDontDestroy())
			{
				donts.push_back((*iter));
				mGameObjs.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		return donts;
	}

}