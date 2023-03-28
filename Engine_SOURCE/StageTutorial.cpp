#include "StageTutorial.h"

namespace dru
{
	CStageTutorial::CStageTutorial()
		: mFadeTimer(0.f)
		, mbFadeDone(false)
		, mbZoomDone(false)
	{
	}

	CStageTutorial::~CStageTutorial()
	{
	}

	void CStageTutorial::InitStage()
	{

		//{
		//	CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mOwner, L"PointLight");
		//	PointLight->SetPos({ 0.f, 0.f, 4.9f });
		//	CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetRadius(110.f);
		//	lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		//}

		//{
		//	CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mOwner, L"PointLight");
		//	PointLight->SetPos({ 0.f, 0.f, 4.9f });
		//	CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetRadius(110.f);
		//	lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 1.f });
		//}


		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// 배경 튵리얼
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stagetutorial");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stagetutorial", L"SpriteShader");
			CResources::Insert<CMaterial>(L"StageTutorial", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(3.f, 0.f, 5.f));
			mStageBackground->SetScale(Vector3(8.f, 8.f, 1.f));
		}

		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-0.f, -2.9f, 4.999));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}

		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-9.f, -2.3f, 4.999f));
			mPlayer->GetComponent<CAnimator>()->Play(L"Player_Run");
			mPlayer->SetRight();
			mPlayer->GetComponent<CRigidBody>()->SetMaxVelocity(Vector3(3.f, 7.f, 0.f));
		}
		
		{
			CGameObj* mReadyTrigger= object::Instantiate<CGameObj>(eLayerType::Platforms, L"TutorialReadyTrigger");
			mReadyTrigger->SetPos(Vector3(0.f, 0.f, 1.f));
			mReadyTrigger->SetScale(Vector3(1.f, 1.f, 1.f));

			CCollider2D* coll = mReadyTrigger->AddComponent<CCollider2D>(eComponentType::Collider);
			coll->SetName(L"col_readyTrigger");
			coll->SetType(eColliderType::Rect);
			coll->SetScale(Vector2(0.2f, 10.f));

		}

	}

	void CStageTutorial::LoadAfterReady()
	{
		renderer::mainCamera->SetProjectionType(eProjectionType::Perspective);
		Vector3 pos = renderer::mainCamera->GetOwner()->GetPos();
		renderer::mainCamera->GetOwner()->SetPos(Vector3(pos.x, pos.y, -CAMTYPEGAP));

		//Vector3 pos2 = mStageBackground->GetPos();
		//mStageBackground->SetPos(Vector3(pos2.x, pos2.y - 0.75f, pos2.z));

		{
			mCamTarget = object::Instantiate<CGameObj>(eLayerType::None, L"CamTargetTutorialStage");
			mCamTarget->SetPos(Vector3(0.f, -2.f, 0.25f));
			mCamTarget->SetScale(Vector3(0.4f, 0.4f, 1.f));
		}



		{
			COutWall* LeftOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-8.25f, 0.f, 4.999f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}


		{
			COutWall* RightOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(8.25f, 0.f, 4.999));
			RightOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}

		{
			CGrunt* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.3f, 4.999));
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"CursorMat");
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script)->Initialize();
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 4.9999));
		}
	}

	void CStageTutorial::Update()
	{
		if (mReady == eReadyState::NotReady)
		{
			mPlayer->GetComponent<CRigidBody>()->AddForce({ 100.f, 0.f, 0.f });
		}

		if (mReady == eReadyState::ReadyEnd)
		{
			if (!mbZoomDone)
			{
				Vector3 TargetPos = mCamTarget->GetPos();
				Vector3 CamPos = renderer::mainCamera->GetOwner()->GetPos();
				Vector3 CamDir = (TargetPos - CamPos);
				CamDir.Normalize();
				float Distance = (TargetPos - CamPos).Length();

				if (Distance >= 0.01f)
				{
					float Speed = Distance / 0.5f;
					float Step = Speed * CTimeMgr::DeltaTime();

					if (Step < Distance)
					{
						CamPos += CamDir * Step;
						renderer::mainCamera->GetOwner()->SetPos(CamPos);
					}
				}
				else
				{
					mbZoomDone = true;

					{
						// 튜토리얼 제목 UI
						mUIBg = object::Instantiate<CBackgroundColor>(eLayerType::BackGround, L"TutorialTitleBg");
						CSpriteRenderer* SpriteRenderer = mUIBg->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

						std::shared_ptr<CMaterial> Material = CResources::Find <CMaterial>(L"UITitleBgMat");
						//CResources::Insert<CMaterial>(L"TutorialTitleBgMat", Material);
						SpriteRenderer->SetMaterial(Material);

						mUIBg->AddComponent<CBackgroundColorScript>(eComponentType::Script)->SetColor(Vector4{ 0.f, 0.f, 0.f, 0.125f });
						mUIBg->AddComponent<CFadeScript>(eComponentType::Script)->SetFadeType(1);
						mUIBg->SetPos(Vector3(0.f, -1.f, 2.5f));
						mUIBg->SetScale(Vector3(10.f, 0.05f, 1.f));

					}
								
				}
									
			}
			else
			{
				if (!mbFadeDone)
				{

					if (mFadeTimer < 1.f)
					{
						mFadeTimer += CTimeMgr::DeltaTime();
					}
					else
					{
						mTutorialtxt = object::Instantiate<CGameObj>(eLayerType::UI, L"Tutorialtxt");

						CSpriteRenderer* SpriteRenderer = mTutorialtxt->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
						std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"tutorialtxt", L"UIShader");
						CResources::Insert<CMaterial>(L"tutorialtxtmat", Material);
						SpriteRenderer->SetMaterial(Material);

						mTutorialtxt->SetPos(Vector3(0.f, 3.5f, 2.4f));
						mTutorialtxt->SetScale(Vector3(0.5f, 0.5f, 1.f));

						mbFadeDone = true;
					}
				}
			}

			
		}



		CStage::Update();
	}
}