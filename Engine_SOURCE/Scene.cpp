#include "Scene.h"
#include "Input.h"

namespace dru
{
	CScene::CScene()
		: mDeleteObj(false)
		, mType(CSceneMgr::eSceneType::End)
		, mbPause(false)
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	CScene::~CScene()
	{
	}
	void CScene::Initialize()
	{
//		mLayers.resize((UINT)eLayerType::None);

	}

	void CScene::update()
	{
		for (CLayer& layer : mLayers)
		{
			layer.update();
		}
	}

	void CScene::fixedUpdate()
	{
		for (CLayer& layer : mLayers)
		{
			layer.fixedUpdate();
		}
	}

	void CScene::render()
	{
	}

	void CScene::fontRender()
	{
		for (CLayer& layer : mLayers)
		{
			layer.fontRender();
		}
	}

	void CScene::destroy()
	{
		for (CLayer& layer : mLayers)
		{
			layer.destroy();
		}
	}

	void CScene::Enter()
	{
		//Initialize();
		for (CLayer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void CScene::Exit()
	{
		if (mDeleteObj)
		{
			for (CLayer& layer : mLayers)
			{
				layer.DeleteObject();
			}
			mDeleteObj = false;
		}

		destroy();
	}

	void CScene::AddGameObject(CGameObj* _GameObj, eLayerType _eLayer)
	{
		mLayers[static_cast<UINT>(_eLayer)].AddGameObject(_GameObj, _eLayer);
	}


	std::vector<CGameObj*> CScene::GetDontDestroyObjects()
	{
		std::vector<CGameObj*> allLayerDontDestroyObjs;
		for (CLayer& layer : mLayers)
		{
			std::vector<CGameObj*> dontDestroyObjs = layer.GetDontDestroyObjects();

			allLayerDontDestroyObjs.insert(allLayerDontDestroyObjs.end(), dontDestroyObjs.begin(), dontDestroyObjs.end());

		}

		return allLayerDontDestroyObjs;
	}

	const std::vector<CGameObj*>& CScene::GetGameObj(eLayerType _eLayer)
	{

		return mLayers[(UINT)_eLayer].GetGameObjects();
	}

}