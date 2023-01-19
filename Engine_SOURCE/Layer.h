#pragma once
#include "GameObj.h"

namespace dru
{
	class CLayer
	{
	public:
		CLayer();
		virtual ~CLayer();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		void AddGameObject(const CGameObj* _GameObj);

	private:
		std::vector<CGameObj*> mGameObjs;

	};
}
