#pragma once
#include "GameObj.h"

namespace dru
{
	class CLayer : public CEntity
	{
	public:
		CLayer();
		virtual ~CLayer();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void fontRender();
		virtual void destroy();
		void DeleteObject ();


		void AddGameObject(CGameObj* _GameObj, eLayerType _Type);
		const std::vector<CGameObj*>& GetGameObjects() { return mGameObjs; }
		std::vector<CGameObj*> GetDontDestroyObjects();


	private:
		std::vector<CGameObj*>	mGameObjs;

	};

	typedef const std::vector<CGameObj*>& GameObjects;
	typedef std::vector<CGameObj*>::iterator GameObjectIter;
}
