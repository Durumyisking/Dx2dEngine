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
		// Ä«¸Þ¶ó
		CGameObj* camera = new CGameObj();
		CTransform* cameraTR = new CTransform();
		cameraTR->SetPosition(Vector3(0.f, 0.f, 0.0f));
		camera->AddComponent(cameraTR);
		CCamera* cameraComp = new CCamera();
		camera->AddComponent(cameraComp);

		CCameraScript* cameraScript = new CCameraScript();
		camera->AddComponent(cameraScript);

		this->AddGameObject(camera, eLayerType::Camera);

		// Light Object
		CGameObj* spriteObj = new CGameObj();
		spriteObj->SetName(L"LIGHT");
		CTransform* spriteTr = new CTransform();
		spriteTr->SetPosition(Vector3(1.0f, 0.0f, 11.0f));
		spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		spriteObj->AddComponent(spriteTr);

		CSpriteRenderer* sr = new CSpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");
		std::shared_ptr<CMaterial> spriteMaterial = CResources::Find<CMaterial>(L"SpriteMaterial");

		std::shared_ptr<CTexture> texture = CResources::Load<CTexture>(L"Light", L"Light.png");	
		spriteMaterial->SetTexture(texture);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		AddGameObject(spriteObj, eLayerType::Player);

		//SMILE RECT
		CGameObj* obj = new CGameObj();
		obj->SetName(L"SMILE");
		CTransform* tr = new CTransform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		obj->AddComponent(tr);

		CSpriteRenderer* mr = new CSpriteRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<CMaterial> mateiral = CResources::Find<CMaterial>(L"MeshMaterial");

		std::shared_ptr<CTexture> texture2 = CResources::Load<CTexture>(L"Smile", L"Smile.png");
		mateiral->SetTexture(texture2);

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);


		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		AddGameObject(obj, eLayerType::Player);


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