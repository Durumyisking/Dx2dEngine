#pragma once
#include "Scene.h"
#include "Layer.h"
#include "Transform.h"

namespace dru::object
{
	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj, _LayerType);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, CScene* _Scene)
	{
		T* gameObj = new T();
		CLayer& layer = _Scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj, _LayerType);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, CScene* _Scene, std::wstring _Name)
	{
		T* gameObj = new T();
		CLayer& layer = _Scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj, _LayerType);

		gameObj->SetName(_Name);

		return gameObj;
	}


	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, std::wstring _Name)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj, _LayerType);

		gameObj->SetName(_Name);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate_pooling(enums::eLayerType _LayerType, std::wstring _Name)
	{
		T* gameObj = new T();

		gameObj->SetName(_Name);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, CGameObj* _Parent, std::wstring _Name)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj, _LayerType);
		gameObj->SetName(_Name);
		CTransform* tr = gameObj->GetComponent<CTransform>();
		tr->SetParent(_Parent);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, Vector3 _Pos, Vector3 _Rotation, std::wstring _Name)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj, _LayerType);
		gameObj->SetName(_Name);
		CTransform* tr = gameObj->GetComponent<CTransform>();
		tr->SetPosition(_Pos);
		tr->SetRotation(_Rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, Vector3 _Pos, Vector3 _Rotation, CGameObj* _Parent, std::wstring _Name)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj, _LayerType);
		gameObj->SetName(_Name);
		CTransform* tr = gameObj->GetComponent<CTransform>();
		tr->SetPosition(_Pos);
		tr->SetRotation(_Rotation);

		tr->SetParent(_Parent);

		return gameObj;
	}



	static void DontDestroyOnLoad(CGameObj* _Gameobj)
	{
		if (_Gameobj == nullptr)
			return;

		_Gameobj->DontDestroy();
	}
}