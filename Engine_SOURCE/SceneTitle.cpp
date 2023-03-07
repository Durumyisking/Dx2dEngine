#include "SceneTitle.h"
#include "TimeMgr.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "BackgroundColorScript.h"
#include "Collider2D.h"

namespace dru
{
	CSceneTitle::CSceneTitle()
		: mCamMoveDone(false)
		, mUIMoveDone(false)
		, mCamera(nullptr)
		, mUICamera(nullptr)
		, mCamTarget(nullptr)
		, mUITarget(nullptr)
		, mUIBg(nullptr)
		, mUIStart(nullptr)
		, mbgBlack(nullptr)
		, mbgSteel(nullptr)
		, mbgChain(nullptr)
		, mbgGrass(nullptr)
		, mbgKatana(nullptr)
		, mbgZer(nullptr)
		, mbgO(nullptr)
		, mMenu(1)
	{
	}

	CSceneTitle::~CSceneTitle()
	{

	}

	void CSceneTitle::Initialize()
	{
		//mDeleteObj = true;
		{
			// main ī�޶�
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->SmoothOn();
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;

		}
		{
			// ui ī�޶�
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(CCamera::eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		{			
			{
				// ��� black
				mbgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
				CSpriteRenderer* SpriteRenderer = mbgBlack->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgBlack->SetPos(Vector3(0.f, -1.f, 1.f));
				mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

			}


			{
				// ��� Steel
				mbgSteel = object::Instantiate<CBackground>(eLayerType::BackGround, L"Steel");
				CSpriteRenderer* SpriteRenderer = mbgSteel->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
	
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Steel", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Steel", Material);
 				SpriteRenderer->SetMaterial(Material);
				mbgSteel->SetPos(Vector3(0.f, -1.f, 1.f));
				mbgSteel->SetScale(Vector3(2.5f, 2.5f, 1.f));
			}

			{
				// ��� TitleZer
				mbgZer = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleZer_1");
				CSpriteRenderer* SpriteRenderer = mbgZer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleZer_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleZer_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgZer->SetPos(Vector3(-0.6f, -2.3f, 0.81f));
				mbgZer->SetScale(Vector3(2.f, 2.f, 1.f));

			}


			{
				// ��� TitleO
				mbgO = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleO_1");
				CSpriteRenderer* SpriteRenderer = mbgO->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleO_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleO_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgO->SetPos(Vector3(2.2f, -2.3f, 0.81f));
				mbgO->SetScale(Vector3(0.2f, 0.2f, 1.f));
			}

			{
				// ��� TitleKatana
				mbgKatana = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleKatana");
				CSpriteRenderer* SpriteRenderer = mbgKatana->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleKatana", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleKatana", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgKatana->SetPos(Vector3(0.25f, -1.3f, 0.6f));
				mbgKatana->SetScale(Vector3(2.f, 2.f, 1.f));
			}


			{
				// ��� Fence
				mbgChain = object::Instantiate<CBackground>(eLayerType::BackGround, L"Fence");
				CSpriteRenderer* SpriteRenderer = mbgChain->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Fence", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Fence", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgChain->SetPos(Vector3(0.f, 1.75f, 0.7f));
				mbgChain->SetScale(Vector3(10.f, 10.f, 1.f));
			}

			{
				// ��� Grass
				mbgGrass = object::Instantiate<CBackground>(eLayerType::BackGround, L"Grass");
				CSpriteRenderer* SpriteRenderer = mbgGrass->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Grass", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Grass", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgGrass->SetPos(Vector3(0.f, -6.5f, 0.69f));
				mbgGrass->SetScale(Vector3(0.9f, 0.9f, 1.f));
			}

			{
				// ��� UI
				mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::UI, L"UITitleBg");
				CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
				CResources::Insert<CMaterial>(L"UITitleBgMat", Material);
				SpriteRenderer->SetMaterial(Material);
				mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 255.f, 0.f, 255.f, 0.5f });
				mUIBg->SetPos(Vector3(0.f, -6.f, 0.5f));
				mUIBg->SetScale(Vector3(0.3f, 0.3f, 1.f));
			}

			{
				// UIStart
				mUIStart = object::Instantiate<CBackgroundColor>(eLayerType::UI, mUIBg->GetComponent<CTransform>(), L"UITitleStart");

				CSpriteRenderer* SpriteRenderer = mUIStart->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
				CResources::Insert<CMaterial>(L"UITitleStartMat", Material);
				SpriteRenderer->SetMaterial(Material);
				mUIStart->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 255.f, 0.5f });
				mUIStart->SetPos(Vector3(0.f, 0.41f, 0.5f));
				mUIStart->SetScale(Vector3(0.15f, 0.02f, 1.f));
			}


			{
				mCamTarget = object::Instantiate<CBackground>(eLayerType::None, L"CamTargetTitleScene");
				mCamTarget->SetPos(Vector3(0.f, -2.5f, 1.f));
				mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}

			{
				mUITarget = object::Instantiate<CBackground>(eLayerType::None, L"UITargetTitleScene");
				mUITarget->SetPos(Vector3(0.f, -2.5f, 0.5f));
				mUITarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}
		}

		mCamera->GetComponent<CCamera>()->SetTarget(mCamTarget);
		
		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		if (!mCamMoveDone && mCamera->GetComponent<CCamera>()->GetTarget() == nullptr)
			mCamMoveDone = true;

		if (mCamMoveDone)
		{
			Vector3 TargetPos = mUITarget->GetPos();
			Vector3 UIPos = mUIBg->GetPos();

			float Distance = (TargetPos- UIPos).Length();

			if (Distance >= 0.001f)
			{
				float Speed = Distance / 0.3f;
				float Step = Speed * CTimeMgr::DeltaTime();

				if (Step < Distance)
				{
					UIPos += mUIBg->Up() * Step;
					mUIBg->SetPos(UIPos);
				}
			}
			else
			{
				mUIMoveDone = true;
			}

		}

		if (mUIMoveDone)
		{
			Vector3 pos = mUIStart->GetPos();

			if (CInput::GetKeyDown(eKeyCode::UP))
			{
				if (1 != mMenu)
				{
					pos = { pos.x, pos.y + 0.2f, pos.z };
					mUIStart->SetPos(pos);
					--mMenu;
				}
				else
				{
					pos = { pos.x, pos.y - (0.2f * 4), pos.z };
					mUIStart->SetPos(pos);
					mMenu = 5; 
				}
			}
			if (CInput::GetKeyDown(eKeyCode::DOWN))
			{
				if (5 != mMenu)
				{
					pos = { pos.x, pos.y - 0.2f, pos.z };
					mUIStart->SetPos(pos);
					++mMenu;
				}
				else
				{
					pos = { pos.x, pos.y + (0.2f * 4), pos.z };
					mUIStart->SetPos(pos);
					mMenu = 1;
				}
			}

			if (CInput::GetKeyDown(eKeyCode::ENTER))
			{
				switch (mMenu)
				{
				case 1:
					CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
					break;
				default:
					break;
				}
			}
		}


		if (CInput::GetKeyDown(eKeyCode::N))
		{
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
		}

		CScene::update();
	}

	void CSceneTitle::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneTitle::render()
	{
		CScene::render();
	}

	void CSceneTitle::Enter()
	{
		CScene::Enter();
	}

	void CSceneTitle::Exit()
	{
		CScene::Exit();
	}


}