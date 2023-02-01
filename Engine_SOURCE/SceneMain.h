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

		virtual void Initialize();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();
	};

}

