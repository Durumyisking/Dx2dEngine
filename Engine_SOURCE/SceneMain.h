#pragma once
#include "Scene.h"

namespace dru
{
	class CSceneMain :
		public CScene
	{
	public:
		CSceneMain();
		virtual ~CSceneMain();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();
	};

}

