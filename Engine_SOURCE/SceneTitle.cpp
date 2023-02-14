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
		cameraTR->SetPosition(Vector3(0.f, 0.f, 0.0f));
		camera->AddComponent(cameraTR);
		CCamera* cameraComp = new CCamera();
		camera->AddComponent(cameraComp);

		CCameraScript* cameraScript = new CCameraScript();
		camera->AddComponent(cameraScript);

		this->AddGameObject(camera, eLayerType::Camera);

		{
			// 배경
			CGameObj* Background = new CGameObj();
			CTransform* transform = new CTransform();
			transform->SetPosition(Vector3(1.f, 0.f, 1.f));
			transform->SetRotation(Vector3(0.f, 0.f, 0.f));

			Background->AddComponent(transform);

			CMeshRenderer* meshRenderer = new CMeshRenderer();
			Background->AddComponent(meshRenderer);

			std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");
			std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"MeshMaterial");

			meshRenderer->SetMaterial(material);
			meshRenderer->SetMesh(mesh);


			this->AddGameObject(Background, eLayerType::BackGround);
		}


		{
			// 플레이어
			CGameObj* gameobj = new CGameObj();
			CTransform* transform = new CTransform();
			transform->SetPosition(Vector3(0.f, 0.f, 1.f));
			transform->SetRotation(Vector3(0.f, 0.f, 0.f));
			//transform->SetScale(Vector3(1.f, 1.f, 0.f));

			gameobj->AddComponent(transform);


			CSpriteRenderer* meshRenderer = new CSpriteRenderer();
			gameobj->AddComponent(meshRenderer);

			std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");
			std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"SpriteMaterial");

			meshRenderer->SetMaterial(material);
			meshRenderer->SetMesh(mesh);

			CPlayerScript* script = new CPlayerScript();
			gameobj->AddComponent(script);

			this->AddGameObject(gameobj, eLayerType::Player);
		}

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