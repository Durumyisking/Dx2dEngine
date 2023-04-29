#include "Stage1.h"
#include "Scene.h"
#include "SceneMain.h"

namespace dru
{
	CStage1::CStage1()
		: mStageBackground(nullptr)
	
	{
		mStageState = eStageState::ReadyEnd;
	}

	CStage1::~CStage1()
	{
	}

	void CStage1::InitStage()
	{

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ -2.5f, -1.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 1.f, 0.f, 0.f, 0.5f });
		}


		{
			// 배경 black
			CGameObj* bgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
			CSpriteRenderer* SpriteRenderer = bgBlack->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Black", Material);
			SpriteRenderer->SetMaterial(Material);
			bgBlack->SetPos(Vector3(0.f, 0.f, 5.f));
			bgBlack->SetScale(Vector3(100.f, 100.f, 1.f));

		}

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// 배경 Stage1
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage1", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(4.3f, 3.125f, 5.f));
			mStageBackground->SetScale(Vector3(6.5f, 6.5f, 1.f));
		}


		{
			mPlayer = object::Instantiate<CPlayer>(eLayerType::Player, L"Player");
			mPlayer->SetPos(Vector3(-6.f, -2.5f, 3.f));
		}

		CreateOutWall();
		CreateFirstFloor();
		CreateSecondFloor();


		{
			CGameObj* mMon = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mMon->SetPos(Vector3(-2.f, -2.5f, 3.f));
		}

	}

	void CStage1::LoadinReady()
	{

	}

	void CStage1::Update()
	{


		CStage::Update();
	}

	void CStage1::Exit()
	{
	}

	void CStage1::Reset()
	{
	
		CStage::Reset();

	}

	void CStage1::AddStartingLiveObjects()
	{
		CStage::AddStartingLiveObjects();
	}

	void CStage1::NotReadyOperate()
	{
		CStage::NotReadyOperate();
	}

	void CStage1::ReadyOperate()
	{
		CStage::ReadyOperate();
	}

	void CStage1::ReadyEndOperate()
	{
		CStage::ReadyEndOperate();
	}

	void CStage1::LoadUIOperate()
	{
		CStage::LoadUIOperate();
	}

	void CStage1::LoadEndOperate()
	{
		CStage::LoadEndOperate();
	}

	void CStage1::CreateOutWall()
	{
		{
			COutWallSide* LeftOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-8.2f, 0.f, 4.999f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}


		{
			COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(30.f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 10.f));
		}

		{
			COutWall* UpOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"UpOutWall");
			UpOutWall->SetPos(Vector3(0.f, 18.f, 4.999f));
			UpOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}

		{
			COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
			DownOutWall->SetPos(Vector3(0.f, -5.f, 4.999f));
			DownOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}
	}

	void CStage1::CreateFirstFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-4.f, -3.4f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });

		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(-1.05f, -1.1f, 3.f));
			Wall->SetColliderScale({ 0.5f, 6.5f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(-3.2f, 1.85f, 3.f));
			Wall->SetColliderScale({ 0.5f, 5.f });
		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-8.f, -0.47f, 3.f));
			Ceiling->SetColliderScale({ 10.f, 0.4f });
		}
	}

	void CStage1::CreateSecondFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(3.75f, 2.f, 3.f));
			Floor->SetColliderScale({ 10.f, 0.4f });
		}
	}

}