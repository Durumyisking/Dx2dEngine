#include "StageTutorial.h"


namespace dru
{
	CStageTutorial::CStageTutorial()
	{
	}

	CStageTutorial::~CStageTutorial()
	{
	}

	void CStageTutorial::InitStage()
	{
		//renderer::mainCamera->GetOwner()->SetPos({-2.f, 0.f, 0.f});

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
			// ¹è°æ ºg¸®¾ó
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
			Floor->SetPos(Vector3(-0.f, -2.9f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}

		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-9.f, -2.3f, 3.f));
			mPlayer->GetComponent<CAnimator>()->Play(L"Player_Run");
			mPlayer->SetRight();
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
		{
			COutWall* LeftOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-8.25f, 0.f, 3.f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}


		{
			COutWall* RightOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(8.25f, 0.f, 3.f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}

		{
			CGrunt* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.3f, 3.f));
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script)->Initialize();
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 1.f));
		}
	}

	void CStageTutorial::Update()
	{
		if (mReady == eReadyState::NotReady)
		{
			mPlayer->GetComponent<CRigidBody>()->AddForce({ 100.f, 0.f, 0.f });
		}

		CStage::Update();
	}
}