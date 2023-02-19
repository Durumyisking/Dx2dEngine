#include "SceneTitle.h"
#include "TimeMgr.h"

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
			{
				// 배경 black
				mbgBlack = new CGameObj();
				CTransform* transform = new CTransform();
				transform->SetPosition(Vector3(0.f, -4.f, 1.1f));
				transform->SetScale(Vector3(10.f, 10.f, 1.f));

				mbgBlack->AddComponent(transform);


				CSpriteRenderer* SpriteRenderer = new CSpriteRenderer();
				mbgBlack->AddComponent(SpriteRenderer);


				std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");

				std::shared_ptr<CTexture> texture = CResources::Load<CTexture>(L"Black", L"TitleScene/bgBlack.png");

				std::shared_ptr<CShader> SpriteShader = CResources::Find<CShader>(L"SpriteShader");
				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>();
				SpriteMaterial->SetShader(SpriteShader);
				SpriteMaterial->SetTexture(texture);
				CResources::Insert<CMaterial>(L"BlackMaterial", SpriteMaterial);

				SpriteRenderer->SetMaterial(SpriteMaterial);
				SpriteRenderer->SetMesh(mesh);

				this->AddGameObject(mbgBlack, eLayerType::BackGround);
			}

			{
				// 배경 Steel
				mbgSteel = new CGameObj();
				CTransform* transform = new CTransform();
				transform->SetPosition(Vector3(0.f, -4.f, 1.f));
				transform->SetScale(Vector3(2.5f, 2.5f, 1.f));

				mbgSteel->AddComponent(transform);


				CSpriteRenderer* SpriteRenderer = new CSpriteRenderer();
				mbgSteel->AddComponent(SpriteRenderer);


				std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"RectMesh");
				std::shared_ptr<CMaterial> material = CResources::Find<CMaterial>(L"SpriteMaterial");

				std::shared_ptr<CTexture> texture = CResources::Load<CTexture>(L"Steel", L"TitleScene/bgSteel.png");



				std::shared_ptr<CShader> SpriteShader = CResources::Find<CShader>(L"SpriteShader");
				std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>();
				SpriteMaterial->SetShader(SpriteShader);
				SpriteMaterial->SetTexture(texture);
				CResources::Insert<CMaterial>(L"SteelMaterial", SpriteMaterial);

				SpriteRenderer->SetMaterial(SpriteMaterial);
				SpriteRenderer->SetMesh(mesh);

				this->AddGameObject(mbgSteel, eLayerType::BackGround);
			}
		}

		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		CScene::update();
	}

	void CSceneTitle::fixedupdate()
	{
		Vector3 pos = mbgSteel->GetComponent<CTransform>()->GetPosition();
		pos.y += 3.f * CTimeMgr::DeltaTime();
		mbgSteel->GetComponent<CTransform>()->SetPosition(pos);

		CScene::fixedupdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}


}