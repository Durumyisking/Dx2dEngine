#pragma once
#include "Entity.h"
#include "Layer.h"
#include "SceneMgr.h"

namespace dru
{
	class CSceneMgr;
	class CScene : public CEntity // 이름과 고유 id를 가진 class
	{
	public:
		CScene();
		virtual ~CScene();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		void SetType(CSceneMgr::eSceneType _eType) { mType = _eType; }

	private:
		std::vector<CLayer> mLayers;
		CSceneMgr::eSceneType mType;

	};

}

