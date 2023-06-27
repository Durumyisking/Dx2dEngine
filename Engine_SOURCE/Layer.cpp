#include "Layer.h"
#include "Renderer.h"
#include "Transform.h"


namespace dru
{
	//static bool CompareGameObjectByZAxis(CGameObj* a, CGameObj* b)
	//{
	//	CTransform* aTr = a->GetComponent<CTransform>();
	//	CTransform* bTr = b->GetComponent<CTransform>();

	//	if (aTr->GetPosition().z <= bTr->GetPosition().z)
	//	{
	//		return true;
	//	}

	//	return false;
	//}


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

	void CLayer::fixedUpdate()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;

			if (CGameObj::eState::Active == Obj->GetState())
				Obj->fixedUpdate();
		}

		//// sort z axis
		//std::sort(mGameObjs.begin(), mGameObjs.end(), CompareGameObjectByZAxis);

	}

	void CLayer::render()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;

			if (CGameObj::eState::Active == Obj->GetState())
				Obj->render();

		}
	}

	void CLayer::fontRender()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (nullptr == Obj)
				continue;

			if (CGameObj::eState::Active == Obj->GetState())
				Obj->fontRender();

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
				iter = mGameObjs.erase(iter);
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

	void CLayer::DeleteObject()
	{
		for (CGameObj* Obj : mGameObjs)
		{
			if (!Obj->IsDontDestroy())
				Obj->Die();
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
				iter = mGameObjs.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		return donts;
	}

}