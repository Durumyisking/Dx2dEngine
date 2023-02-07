#include "SceneMgr.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Renderer.h"
#include "Texture.h"

#include "PlayerScript.h"

namespace dru
{
//	CScene* CSceneMgr::mScenes[(static_cast<UINT>(CSceneMgr::eSceneType::End))] = {};
	CScene* CSceneMgr::mPlayScene = nullptr;


	void CSceneMgr::Initialize()
	{

		//mScenes[static_cast<UINT>(eSceneType::Title)] = new CSceneTitle;
		//mScenes[static_cast<UINT>(eSceneType::Title)]->SetType(eSceneType::Title);
		//mScenes[static_cast<UINT>(eSceneType::Main)] = new CSceneMain;
		//mScenes[static_cast<UINT>(eSceneType::Main)]->SetType(eSceneType::Main);

//		mPlayScene = mScenes[static_cast<UINT>(eSceneType::Title)];
		mPlayScene = new CScene();
		mPlayScene->Initialize();

		CGameObj* gameobj = new CGameObj();
		CTransform* transform = new CTransform();
		transform->SetPosition(Vector3(0.2f, 0.2f, 0.f));
		gameobj->AddComponent(transform);

		CMeshRenderer* meshRenderer = new CMeshRenderer();
		gameobj->AddComponent(meshRenderer);

		CMesh* mesh = CResources::Find<CMesh>(L"RectMesh");
		CMaterial* material = CResources::Find<CMaterial>(L"DefaultMaterial");

		meshRenderer->SetMaterial(material);
		meshRenderer->SetMesh(mesh);

		CTexture* texture = CResources::Load<CTexture>(L"Test", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		CPlayerScript* script = new CPlayerScript();
		gameobj->AddComponent(script);

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