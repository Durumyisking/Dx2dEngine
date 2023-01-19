#include "Scene.h"
#include "Input.h"

namespace dru
{
	CScene::CScene()
	{
	}
	CScene::~CScene()
	{
	}
	void CScene::init()
	{
		for (CLayer& layer : mLayers)
		{
			layer.init();
		}
	}

	void CScene::update()
	{
		for (CLayer& layer : mLayers)
		{
			layer.update();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			return;
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