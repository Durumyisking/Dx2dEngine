#pragma once
#include "Entity.h"
#include "Layer.h"
#include "SceneMgr.h"
#include "GameObj.h"

namespace dru
{
	using namespace enums;
	class CSceneMgr;
	class CScene : public CEntity // �̸��� ���� id�� ���� class
	{
	public:
		CScene();
		virtual ~CScene();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		void AddGameObject(CGameObj* _GameObj, eLayerType _eLayer);

		void SetType(CSceneMgr::eSceneType _eType) { mType = _eType; }

	private:
		std::vector<CLayer> mLayers;
		CSceneMgr::eSceneType mType;

	};

}

