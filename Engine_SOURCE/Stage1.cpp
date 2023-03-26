#include "Stage1.h"
#include "Scene.h"


namespace dru
{
	CStage1::CStage1()
	{
	}

	CStage1::~CStage1()
	{
	}

	void CStage1::InitStage()
	{
		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mOwner, L"PointLight");
			PointLight->SetPos({ -2.5f, -1.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 1.f, 0.f, 0.f, 1.f });

		}


		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mOwner, L"PointLight");
			PointLight->SetPos({ 0.f, -1.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 0.5f, 0.5f, 0.5f, 1.f });

		}

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// ¹è°æ Stage1
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage1", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(7.f, 5.f, 5.f));
			mStageBackground->SetScale(Vector3(8.f, 8.f, 1.f));
		}


		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-6.f, -2.5f, 3.f));
		}

		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-4.f, -3.4f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });

		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(0.85f, 0.f, 3.f));
			Wall->SetColliderScale({ 0.5f, 20.f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(-1.8f, 1.8f, 3.f));
			Wall->SetColliderScale({ 0.5f, 5.f });
		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-6.6f, -0.5f, 3.f));
			Ceiling->SetColliderScale({ 10.f, 0.4f });
		}



		{
			CGameObj* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.5f, 3.f));
		}

		{
			mUICursor = object::Instantiate<CBackground>(eLayerType::UI, L"Cursor");

			CSpriteRenderer* SpriteRenderer = mUICursor->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
			SpriteRenderer->SetMaterial(Material);
			mUICursor->AddComponent<CCursorScript>(eComponentType::Script);
			mUICursor->SetPos(Vector3(0.f, 0.f, 3.f));
			mUICursor->SetScale(Vector3(0.7f, 0.7f, 1.f));
		}
	}

}