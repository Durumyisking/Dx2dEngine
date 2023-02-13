#include "SceneTitle.h"

namespace dru
{
	CSceneTitle::CSceneTitle()
	{
	}

	CSceneTitle::~CSceneTitle()
	{

	}

	void CSceneTitle::Initialize()
	{
		CGameObj* gameobj = new CGameObj();
		CTransform* transform = new CTransform();
		transform->SetPosition(Vector3(0.2f, 0.2f, 0.f));
		gameobj->AddComponent(transform);

		CMeshRenderer* meshRenderer = new CMeshRenderer();
		gameobj->AddComponent(meshRenderer);

		CMesh* mesh = CResources::Find<CMesh>(L"RectMesh").get();
		CMaterial* material = CResources::Find<CMaterial>(L"DefaultMaterial").get();

		meshRenderer->SetMaterial(material);
		meshRenderer->SetMesh(mesh);

		CTexture* texture = CResources::Load<CTexture>(L"Test", L"Test.png").get();
		texture->BindShader(eShaderStage::PS, 0);

		CPlayerScript* script = new CPlayerScript();
		gameobj->AddComponent(script);

		this->AddGameObject(gameobj, eLayerType::Player);



		CGameObj* camera = new CGameObj();
		CTransform* cameraTR = new CTransform();
		cameraTR->SetPosition(Vector3(0.f, 0.f, 0.f));
		camera->AddComponent(cameraTR);

		CCamera* cameraComp = new CCamera();
		camera->AddComponent(cameraComp);

		this->AddGameObject(gameobj, eLayerType::Camera);


		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		CScene::update();
	}

	void CSceneTitle::fixedupdate()
	{
		CScene::fixedupdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}


}