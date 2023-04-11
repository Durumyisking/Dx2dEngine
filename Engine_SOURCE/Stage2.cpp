#include "Stage2.h"

namespace dru
{
	CStage2::CStage2()
		: mStageBackground(nullptr)
	{
		mStageState = eStageState::ReadyEnd;
	}

	CStage2::~CStage2()
	{
	}

	void CStage2::InitStage()
	{
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
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage2");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage2", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(2.25f, 0.f, 5.f));
			mStageBackground->SetScale(Vector3(1.f, 1.f, 1.f));
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

	void CStage2::LoadinReady()
	{
	}

	void CStage2::Update()
	{
		if (mStageState == eStageState::NotReady)
		{
			NotReadyOperate();
		}

		if (mStageState == eStageState::Ready)
		{
			ReadyOperate();
		}

		if (mStageState == eStageState::ReadyEnd)
		{
			ReadyEndOperate();
		}

		if (mStageState == eStageState::LoadUI)
		{
			LoadUIOperate();
		}

		if (mStageState == eStageState::LoadEnd)
		{
			BulletTimeBatteryOperation();
		}

		CStage::Update();
	}

	void CStage2::Exit()
	{
	}

	void CStage2::NotReadyOperate()
	{
		CStage::NotReadyOperate();
	}

	void CStage2::ReadyOperate()
	{
		CStage::ReadyOperate();
	}

	void CStage2::ReadyEndOperate()
	{
		CStage::ReadyEndOperate();
	}

	void CStage2::LoadUIOperate()
	{
		CStage::LoadUIOperate();
	}

	void CStage2::LoadEndOperate()
	{
		CStage::LoadEndOperate();
	}

	void CStage2::CreateOutWall()
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

	void CStage2::CreateFirstFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-4.f, -3.7f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });

		}


		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-5.625f, -0.65f, 3.f));
			Ceiling->SetColliderScale({ 10.f, 0.1f });
		}
	}

	void CStage2::CreateSecondFloor()
	{
	}

}