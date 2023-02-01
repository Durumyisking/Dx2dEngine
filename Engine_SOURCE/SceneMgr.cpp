#include "SceneMgr.h"

#include "Scene.h"

#include "SceneTitle.h"
#include "SceneMain.h"

#include "Transform.h"
#include "MeshRenderer.h"

#include "Renderer.h"

namespace dru
{
	CScene* CSceneMgr::mScenes[(static_cast<UINT>(CSceneMgr::eSceneType::End))] = {};
	CScene* CSceneMgr::mPlayScene = nullptr;

	CSceneMgr::CSceneMgr()
	{
	}
	CSceneMgr::~CSceneMgr()
	{
	}

	void CSceneMgr::Initialize()
	{

		mScenes[static_cast<UINT>(eSceneType::Title)] = new CSceneTitle;
		mScenes[static_cast<UINT>(eSceneType::Title)]->SetType(eSceneType::Title);
		mScenes[static_cast<UINT>(eSceneType::Main)] = new CSceneMain;
		mScenes[static_cast<UINT>(eSceneType::Main)]->SetType(eSceneType::Main);

		mPlayScene = mScenes[static_cast<UINT>(eSceneType::Title)];
		mPlayScene->Initialize();

		CGameObj* gameobj = new CGameObj();

		CTransform* transform = new CTransform();
		transform->SetPosition(Vector4(0.2f, 0.2f, 0.f, 0.f));
		gameobj->AddComponent(transform);

		CMeshRenderer* meshRenderer = new CMeshRenderer();
		gameobj->AddComponent(meshRenderer);

		meshRenderer->SetShader(renderer::Shader);
		meshRenderer->SetMesh(renderer::Mesh);

		mPlayScene->AddGameObject(gameobj, eLayerType::Player);
		
	}

	void CSceneMgr::update()
	{
		mPlayScene->update();
	}

	void CSceneMgr::fixedupdate()
	{
		mPlayScene->fixedupdate();
	}

	void CSceneMgr::render()
	{
		mPlayScene->render();
	}

}