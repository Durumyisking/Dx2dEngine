#include "SceneTitle.h"
#include "TimeMgr.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "BackgroundColorScript.h"
#include "Collider2D.h"
#include "Animator.h"

#include "AudioSource.h"

#include "SceneMain.h"


namespace dru
{
	CSceneTitle::CSceneTitle()
		: mCamMoveDone(false)
		, mCamMoveStart(false)
		, mUIMoveDone(false)
		, mCamera(nullptr)
		, mUICamera(nullptr)
		, mCamTarget(nullptr)
		, mCamTarget2(nullptr)
		, mUITarget(nullptr)
		, mUIBg(nullptr)
		, mUIMenu(nullptr)
		, mUIStart(nullptr)
		, mbgBlack(nullptr)
		, mbgSteel(nullptr)
		, mbgChain(nullptr)
		, mbgGrass(nullptr)
		, mbgKatana(nullptr)
		, mbgZer(nullptr)
		, mbgO(nullptr)
		, mbgGrass2(nullptr)
		, mMenu(1)
		, mFontAlpha(0.f)
	{
	}

	CSceneTitle::~CSceneTitle()
	{

	}

	void CSceneTitle::Initialize()
	{
		
		
		CScene::Initialize();
	}

	void CSceneTitle::update()
	{
		if (!mCamMoveDone && mCamera->GetComponent<CCamera>()->GetTarget() == nullptr)
		{
			mCamMoveDone = true;
		}
	

		if (mCamMoveDone)
		{
			if (mUIBg->MoveToTarget_Smooth_bool(mUITarget, 0.3f, true))
			{
				mUIMoveDone = true;
			}
		}


		if (mUIMoveDone)
		{
			Vector3 pos = mUIStart->GetPos();

			if (CInput::GetKeyTap(eKeyCode::UP))
			{
				mUIStart->GetComponent<CAudioSource>()->Play(L"SE_title_updown");
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
			if (CInput::GetKeyTap(eKeyCode::DOWN))
			{
				mUIStart->GetComponent<CAudioSource>()->Play(L"SE_title_updown");
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

			if (CInput::GetKeyTap(eKeyCode::ENTER))
			{
				mUIMenu->GetComponent<CAudioSource>()->Play(L"SE_title_select");
				switch (mMenu)
				{
				case 1:
					mCamera->GetComponent<CCamera>()->SmoothOff();
					mCamera->GetComponent<CCamera>()->SetTarget(mCamTarget2);
					mCamMoveStart = true;

					break;
				default:
					break;
				}
			}
		}

		if (mCamMoveStart)
		{
			if (mCamera->GetComponent<CCamera>()->GetTarget() == nullptr)
			{
				mCamera->GetComponent<CAudioSource>()->Stop(L"song_title_bgm");
				CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
			}

		}


		if (CInput::GetKeyTap(eKeyCode::N))
		{
			mCamera->GetComponent<CAudioSource>()->Stop(L"song_title_bgm");
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Main);
		}

		if (CInput::GetKeyTap(eKeyCode::M))
		{
			mCamera->GetComponent<CAudioSource>()->Stop(L"song_title_bgm");
			CSceneMgr::LoadScene(CSceneMgr::eSceneType::Ending);
		}

		CScene::update();
	}

	void CSceneTitle::fixedUpdate()
	{
		CScene::fixedUpdate();
	}

	void CSceneTitle::render()
	{
		if (mUIMoveDone)
		{
			if (255.f >= mFontAlpha)
			{
				mFontAlpha += CTimeMgr::DeltaTime() * 255.f;
			}
			if(!mCamMoveStart)
			{
				CFontWrapper::DrawFont(L"Game Start", 730.f, 535.f, 30.f, FONT_RGBA(255, 255, 255, mFontAlpha));
				CFontWrapper::DrawFont(L"ExitGame", 736.f, 765.f, 30.f, FONT_RGBA(255, 255, 255, mFontAlpha));
			}
		}
	}

	void CSceneTitle::Enter()
	{
		//mDeleteObj = true;

		{
			// main 카메라
			mCamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"MainCam");
			CCamera* cameraComp = mCamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->SmoothOn();
			mCamera->AddComponent<CCameraScript>(eComponentType::Script);
			renderer::mainCamera = cameraComp;
			cameraComp->SetProjectionType(eProjectionType::Perspective);
			mCamera->SetPos(Vector3(0.f, 1.f, 0.f));

			CAudioSource* audioSource = mCamera->AddComponent<CAudioSource>(eComponentType::AudioSource);
			audioSource->AddClipByKey(L"song_title_bgm");

			mCamera->GetComponent<CAudioSource>()->Play(L"song_title_bgm", true);

		}
		{
			// ui 카메라
			mUICamera = object::Instantiate<CGameObj>(eLayerType::Camera, L"UICam");
			CCamera* cameraComp = mUICamera->AddComponent<CCamera>(eComponentType::Camera);
			cameraComp->SetProjectionType(eProjectionType::Orthographic);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		{
			CGameObj* directionalLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
			directionalLight->SetPos({ 0.f, 0.f, -100.f });
			CLight* lightComp = directionalLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		}


		{
			{
				// 배경 black
				mbgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
				CSpriteRenderer* SpriteRenderer = mbgBlack->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgBlack->SetPos(Vector3(0.f, -1.f, 5.f));
				mbgBlack->SetScale(Vector3(10.f, 10.f, 1.f));

			}


			{
				// 배경 Steel
				mbgSteel = object::Instantiate<CBackground>(eLayerType::BackGround, L"Steel");
				CSpriteRenderer* SpriteRenderer = mbgSteel->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Steel", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Steel", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgSteel->SetPos(Vector3(0.f, -1.f, 5.f));
				mbgSteel->SetScale(Vector3(1.625f, 1.625f, 1.f));
			}

			{
				// 배경 TitleZer
				mbgZer = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleZer_1");
				CSpriteRenderer* SpriteRenderer = mbgZer->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleZer_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleZer_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgZer->SetPos(Vector3(-0.325f, -1.85f, 4.f));
				mbgZer->SetScale(Vector3(1.f, 1.f, 1.f));

			}


			{
				// 배경 TitleO
				mbgO = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleO_1");
				CSpriteRenderer* SpriteRenderer = mbgO->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleO_1", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleO_1", Material);
				SpriteRenderer->SetMaterial(Material);

				mbgO->SetPos(Vector3(1.1f, -1.85f, 4.f));
				mbgO->SetScale(Vector3(0.1f, 0.1f, 1.f));

				mbgO->AddComponent<CAudioSource>(eComponentType::AudioSource)->AddClipByKey(L"SE_title_neon");
			}

			{
				// 배경 TitleKatana
				mbgKatana = object::Instantiate<CBackground>(eLayerType::BackGround, L"TitleKatana");
				CSpriteRenderer* SpriteRenderer = mbgKatana->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleKatana", L"SpriteShader");
				CResources::Insert<CMaterial>(L"TitleKatana", Material);
				SpriteRenderer->SetMaterial(Material);


				mbgKatana->SetPos(Vector3(0.1f, -1.4f, 4.f));
				mbgKatana->SetScale(Vector3(1.f, 1.f, 1.f));
			}


			{
				// 배경 Fence
				mbgChain = object::Instantiate<CBackground>(eLayerType::BackGround, L"Fence");
				CSpriteRenderer* SpriteRenderer = mbgChain->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Fence", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Fence", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgChain->SetPos(Vector3(0.f, -0.4f, 3.f));
				mbgChain->SetScale(Vector3(3.85f, 3.85f, 1.f));
			}


			{
				// 배경 UI
				mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"UITitleBg");
				CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
				SpriteRenderer->SetMaterial(Material);

				mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 124.f, 124.f, 124.f, 0.125f });
				mUIBg->SetPos(Vector3(0.f, -10.f, 2.5f));
				mUIBg->SetScale(Vector3(0.1f, 0.1f, 1.f));

			}

			{
				// 선택메뉴
				mUIMenu = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, mUIBg, L"UITitleSelect");
//				CSpriteRenderer* SpriteRenderer = mUIMenu->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				//std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"TitleButton", L"SpriteShader");
				//CResources::Insert<CMaterial>(L"TitleButtonMat", Material);
				//SpriteRenderer->SetMaterial(Material);
				//mUIMenu->SetPos(Vector3(0.f, 0.05f, 0.f));
				//mUIMenu->SetScale(Vector3(0.35f, 0.475f, 1.f));

				mUIMenu->AddComponent<CAudioSource>(eComponentType::AudioSource)->AddClipByKey(L"SE_title_select");
//				mUIMenu->GetComponent<CAudioSource>()->Play();
			}

			{
				// UIStart
				mUIStart = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, mUIBg, L"UITitleStart");

				CSpriteRenderer* SpriteRenderer = mUIStart->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
				CResources::Insert<CMaterial>(L"UITitleStartMat", Material);
				SpriteRenderer->SetMaterial(Material);
				mUIStart->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.5f });
				mUIStart->SetPos(Vector3(0.f, 0.4f, 0.f));
				mUIStart->SetScale(Vector3(0.06f, 0.015f, 1.f));

				mUIStart->AddComponent<CAudioSource>(eComponentType::AudioSource)->AddClipByKey(L"SE_title_updown");
//				mUIStart->GetComponent<CAudioSource>()->Play();

			}

			{
				// 배경 Grass
				mbgGrass = object::Instantiate<CBackground>(eLayerType::BackGround, L"Grass");
				CSpriteRenderer* SpriteRenderer = mbgGrass->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Grass", L"SpriteShader");
				CResources::Insert<CMaterial>(L"GrassMat", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgGrass->SetPos(Vector3(0.f, -2.6f, 1.f));
				mbgGrass->SetScale(Vector3(0.13f, 0.13f, 1.f));
			}

			{
				// 배경 Grass2
				mbgGrass2 = object::Instantiate<CBackground>(eLayerType::BackGround, L"Grass2");
				CSpriteRenderer* SpriteRenderer = mbgGrass2->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Grass2", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Grass2Mat", Material);
				//				Renderer->SetMaterial(Material);

				SpriteRenderer->SetAnimMaterial(Material, { 640.f, 255.f });

				mbgGrass2->SetPos(Vector3(0.f, -2.25f, 1.f));
				mbgGrass2->SetScale(Vector3(0.16f, 0.16f, 1.f));

				CAnimator* animator = mbgGrass2->AddComponent<CAnimator>(eComponentType::Animator);
				animator->Create(L"Grass_Title", Material->GetTexture(), { 0.f, 0.f }, { 640.f, 255.f }, Vector2::Zero, 12, { 640.f, 255.f }, 0.1f);
				animator->Play(L"Grass_Title");

			}

			{
				// 배경 black
				mbgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
				CSpriteRenderer* SpriteRenderer = mbgBlack->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

				std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
				CResources::Insert<CMaterial>(L"Black", Material);
				SpriteRenderer->SetMaterial(Material);
				mbgBlack->SetPos(Vector3(0.f, -25.25f, 1.f));
				mbgBlack->SetScale(Vector3(5.f, 5.f, 1.f));

			}

			{
				mCamTarget = object::Instantiate<CBackground>(eLayerType::None, L"CamTargetTitleScene");
				mCamTarget->SetPos(Vector3(0.f, -2.1f, 1.f));
				mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}


			{
				mCamTarget2 = object::Instantiate<CBackground>(eLayerType::None, L"CamTargetTitleScene2");
				mCamTarget2->SetPos(Vector3(0.f, -3.3f, 1.f));
				mCamTarget2->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}


			{
				mUITarget = object::Instantiate<CBackground>(eLayerType::None, L"UITargetTitleScene");
				mUITarget->SetPos(Vector3(0.f, -2.8f, 2.5f));
				mUITarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
			}
		}

		mCamera->GetComponent<CCamera>()->SetTarget(mCamTarget);

		CScene::Enter();
	}

	void CSceneTitle::Exit()
	{
		CScene::Exit();
	}


}