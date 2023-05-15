#include "Stage1.h"
#include "Scene.h"
#include "SceneMain.h"

namespace dru
{
	CStage1::CStage1()
		: mGrunt1(nullptr)
		, mGrunt2(nullptr)
		, mLaserFloor(nullptr)
		, mLaserTurret(nullptr)
		, mGrunt1DefaultPos{}
		, mGrunt2DefaultPos{}

	{
	}

	CStage1::~CStage1()
	{
	}

	void CStage1::InitStage()
	{

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// ¹è°æ Stage1
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage1", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(4.3f, 3.125f, 5.f));
			mStageBackground->SetScale(Vector3(6.5f, 6.5f, 1.f));
		}

		mPlayerDefaultPos = Vector3(-6.f, -2.5f, 3.f);
		mGrunt1DefaultPos = Vector3(0.f, 2.75f, 3.f);
		mGrunt2DefaultPos = Vector3(3.4f, 2.75f, 3.f);

		mStageState = eStageState::Ready;

		mEnemyCount = 2;

		AddStartingLiveObjects();

		CreateOutWall();
		CreateFirstFloor();
		CreateSecondFloor();
		CreateThirdFloor();
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
		CStage::Exit();
	}

	void CStage1::Reset()
	{
		mPlayer->SetPos(mPlayerDefaultPos);
		CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
		playerScript->Reset();

		mGrunt1->SetPos(mGrunt1DefaultPos);
		mGrunt1->GetScript<CMonsterScript>()->Reset();
		mGrunt1->SetRight();

		mGrunt2->SetPos(mGrunt2DefaultPos);
		mGrunt2->GetScript<CMonsterScript>()->Reset();
		mGrunt2->SetLeft();

		mEnemyCount = 2;

		CStage::Reset();

	}

	void CStage1::AddStartingLiveObjects()
	{
		{
			mGrunt1 = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mGrunt1->SetPos(mGrunt1DefaultPos);
			mRewindObjects.push_back(mGrunt1);
			mGrunt1->SetLeft();
		}
		{
			mGrunt2 = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
			mGrunt2->SetPos(mGrunt2DefaultPos);
			mRewindObjects.push_back(mGrunt2);
			mGrunt2->SetLeft();
		}

		CStage::AddStartingLiveObjects();
	}

	void CStage1::NotReadyOperate()
	{
		CStage::NotReadyOperate();
	}

	void CStage1::ReadyOperate()
	{
		mLaserTurret->AdjustLaserTransform();
		mLaserTurret->AdjustAimParticle();

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
			LeftOutWall->SetColliderScale(Vector2(0.5f, 30.f));
		}

		{
			COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(20.f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 30.f));
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
			Wall->SetPos(Vector3(-3.2f, 4.4f, 3.f));
			Wall->SetColliderScale({ 0.5f, 10.f });
		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-8.f, -0.47f, 3.f));
			Ceiling->SetColliderScale({ 10.f, 0.4f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ -2.5f, -1.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 1.f, 0.f, 0.f, 0.5f });
		}
	}

	void CStage1::CreateSecondFloor()
	{
		{
			mLaserFloor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			mLaserFloor->SetPos(Vector3(3.75f, 2.f, 3.f));
			mLaserFloor->SetColliderScale({ 10.f, 0.4f });

			mLaserTurret = object::Instantiate<CTurret>(eLayerType::None, L"Laser");
			mLaserTurret->SetPos(Vector3(3.9f, 9.f, 3.f));
			mLaserTurret->SetScale({ 0.25f, 0.25f, 0.f });

			mLaserTurret->SetDestinationFloor(mLaserFloor);
		}

		{
			CFloor2* Floor = object::Instantiate<CFloor2>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-2.3f, 2.15f, 3.f));
			Floor->SetColliderScale({ 2.f, 0.1f });
		}


		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 1.f, 1.f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.5f });
		}


		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-1.f, 5.35f, 3.f));
			Ceiling->SetColliderScale({ 6.f, 0.4f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(2.43f, 9.47f, 3.f));
			Wall->SetColliderScale({ 0.8f, 10.f });
		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(2.425f, 4.38f, 3.f));
			Ceiling->SetColliderScale({ 0.6f, 0.2f });
		}


		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(5.2f, 2.4f, 3.f));
			Wall->SetColliderScale({ 0.5f, 7.f });
		}


	}

	void CStage1::CreateThirdFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(15.f, 5.78f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 2.5f, 8.f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(2.f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.5f });
		}


		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(5.f, 9.15f, 3.f));
			Ceiling->SetColliderScale({ 30.f, 0.4f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 13.f, 10.f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(2.5f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.5f });
		}

		SetClearCollider({ 17.f, 8.f, 0.f });
	}


}