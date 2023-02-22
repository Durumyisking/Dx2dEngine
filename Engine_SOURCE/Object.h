#pragma once
#include "Scene.h"
#include "Layer.h"
#include "GameObj.h"
#include "SceneMgr.h"
#include "Transform.h"

namespace dru::object
{
	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, std::wstring _Name)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(_LayerType);
		layer.AddGameObject(gameObj);

		gameObj->SetName(_Name);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, CTransform* _Parent)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj);

		CTransform* tr = gameObj->GetComponent<CTransform*>();
		tr->SetParent(_Parent);

		return gameObj;
	}

	//template <typename T>
	//static T* Instantiate(enums::eLayerType _LayerType, CTransform* _Parent, bool InstantiateInWorldSpace)
	//{
	//	T* gameObj = new T();
	//	CScene* scene = CSceneMgr::mActiveScene;
	//	CLayer& layer = scene->GetLayer();
	//	layer.AddGameObject(gameObj);

	//	CTransform* tr = gameObj->GetComponent<CTransform*>();
	//	tr->SetParent(_Parent);

	//	if (InstantiateInWorldSpace)
	//	{

	//	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, Vector3 _Pos, Vector3 _Rotation)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj);

		CTransform* tr = gameObj->GetComponent<CTransform*>();
		tr->SetPosition(_Pos);
		tr->SetRotation(_Rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType _LayerType, Vector3 _Pos, Vector3 _Rotation, CTransform* _Parent)
	{
		T* gameObj = new T();
		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer();
		layer.AddGameObject(gameObj);

		CTransform* tr = gameObj->GetComponent<CTransform*>();
		tr->SetPosition(_Pos);
		tr->SetRotation(_Rotation);

		tr->SetParent(_Parent);

		return gameObj;
	}

	//	return gameObj;
	//}

	//linear interpolation/

}