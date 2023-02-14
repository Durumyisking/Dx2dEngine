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
		// 카메라
		CGameObj* camera = new CGameObj();
		CTransform* cameraTR = new CTransform();
		cameraTR->SetPosition(Vector3(0.f, 0.f, 0.f));
		camera->AddComponent(cameraTR);
		CCamera* cameraComp = new CCamera();
		camera->AddComponent(cameraComp);

		this->AddGameObject(camera, eLayerType::Camera);


		// 플레이어
		CGameObj* gameobj = new CGameObj();
		CTransform* transform = new CTransform();
		//transform->SetPosition(Vector3(0.f, 0.f, 1.f));
		//transform->SetRotation(Vector3(0.5f, 0.f, 0.f));
		//transform->SetScale(Vector3(1.f, 1.f, 0.f));

		gameobj->AddComponent(transform);


		CMeshRenderer* meshRenderer = new CMeshRenderer();
		gameobj->AddComponent(meshRenderer);

		std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");
		std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"DefaultMaterial");

		Vector2 vec2(1.0f, 1.0f);
		material->SetData(eGPUParam::Vector2, &vec2);

		meshRenderer->SetMaterial(material.get());
		meshRenderer->SetMesh(mesh.get());

		CPlayerScript* script = new CPlayerScript();
		gameobj->AddComponent(script);

		std::shared_ptr<CTexture> texture = CResources::Load<CTexture>(L"Test", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		this->AddGameObject(gameobj, eLayerType::Player);

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