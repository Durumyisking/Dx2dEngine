#include "Scene.h"
#include "Input.h"

namespace dru
{
	CScene::CScene()
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	CScene::~CScene()
	{
	}
	void CScene::Initialize()
	{
		mLayers.resize((UINT)eLayerType::End);
		for (CLayer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void CScene::update()
	{
		for (CLayer& layer : mLayers)
		{
			layer.update();
		}
	}

	void CScene::fixedupdate()
	{
		for (CLayer& layer : mLayers)
		{
			layer.fixedupdate();
		}

	}

	void CScene::render()
	{
		for (CLayer& layer : mLayers)
		{
			layer.render();
		}

	}

	void CScene::AddGameObject(CGameObj* _GameObj, eLayerType _eLayer)
	{
		mLayers[static_cast<UINT>(_eLayer)].AddGameObject(_GameObj);
	}

}