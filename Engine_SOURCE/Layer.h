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


	private:
		std::vector<CGameObj*> mGameObjs;

	};
}
