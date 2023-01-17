#pragma once
#include "Scene.h"

namespace dru
{
	class CSceneMgr
	{
	public:
		static void init();
		static void update();
		static void fixedupdate();
		static void render();


	private:
		static CScene* mPlayScene;

	};

}

