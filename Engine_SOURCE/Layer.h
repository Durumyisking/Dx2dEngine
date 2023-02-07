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
		virtual void fixedupdate();
		virtual void render();

		virtual void Release();

		void AddGameObject(CGameObj* _GameObj);


	private:
		std::vector<CGameObj*>	mGameObjs;

	};
}
