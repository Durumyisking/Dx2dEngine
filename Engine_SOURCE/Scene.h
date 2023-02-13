#pragma once
#include "Entity.h"
#include "Layer.h"
#include "SceneMgr.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"


#include "PlayerScript.h"

namespace dru
{
	using namespace enums;
	class CSceneMgr;
	class CScene : public CEntity // 이름과 고유 id를 가진 class
	{
	public:
		CScene();
		virtual ~CScene();

		virtual void Initialize();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		void AddGameObject(CGameObj* _GameObj, const eLayerType _eLayer);

		void SetType(CSceneMgr::eSceneType _eType) { mType = _eType; }

	private:
		std::vector<CLayer> mLayers;
		CSceneMgr::eSceneType mType;

	};

}

