#include "Stage2.h"

namespace dru
{
	CStage2::CStage2()
		: mStageBackground(nullptr)
		, mGrunt1(nullptr)
		, mCop1(nullptr)
		, mGrunt1DefaultPos{}
		, mCop1DefaultPos{}
	{
	}

	CStage2::~CStage2()
	{
	}

	void CStage2::InitStage()
	{
		{
			// 배경 black
			CGameObj* bgBlack = object::Instantiate<CBackground>(eLayerType::BackGround, L"Black");
			CSpriteRenderer* SpriteRenderer = bgBlack->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Black", Material);
			SpriteRenderer->SetMaterial(Material);
			bgBlack->SetPos(Vector3(0.f, 0.f, 5.f));
			bgBlack->SetScale(Vector3(100.f, 100.f, 1.f));

		}

		/////////////////////////////Obj Add /////////////////////////////////////
		{
			// 배경 Stage2
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage2");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage2", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(2.25f, 0.f, 5.f));
			mStageBackground->SetScale(Vector3(1.f, 1.f, 1.f));
		}

		mPlayerDefaultPos = Vector3(-6.f, -3.f, 3.f);
		mGrunt1DefaultPos = Vector3(0.f, -3.f, 3.f);
		mCop1DefaultPos = Vector3(0.f, -3.f, 3.f);

		mEnemyCount = 1;
		mStageState = eStageState::ReadyEnd;

		AddStartingLiveObjects();

		CreateOutWall();
		CreateFirstFloor();
		CreateSecondFloor();

	}

	void CStage2::LoadinReady()
	{
	}

	void CStage2::Update()
	{


		CStage::Update();
	}

	void CStage2::Exit()
	{
		CStage::Exit();
	}

	void CStage2::Reset()
	{
		mPlayer->SetPos(mPlayerDefaultPos);
		CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
		playerScript->Reset();

		//mGrunt1->SetPos(mGrunt1DefaultPos);
		//mGrunt1->GetScript<CMonsterScript>()->Reset();

		mCop1->SetPos(mCop1DefaultPos);
		mCop1->GetScript<CMonsterScript>()->Reset();

		mEnemyCount = 1;


		CStage::Reset();
	}

	void CStage2::AddStartingLiveObjects()
	{

		//{
		//	mGrunt1 = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
		//	mGrunt1->SetPos(mGrunt1DefaultPos);
		//	mRewindObjects.push_back(mGrunt1);
		//}

		{
			mCop1 = object::Instantiate<CCop>(eLayerType::Monster, L"Cop");
			mCop1->SetPos(mCop1DefaultPos);
			mCop1->SetRight();
			mRewindObjects.push_back(mCop1);
		}

		CStage::AddStartingLiveObjects();
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
			LeftOutWall->SetColliderScale(Vector2(0.5f, 100.f));
		}


		{
			COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(30.f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 100.f));
		}

		{
			COutWall* UpOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"UpOutWall");
			UpOutWall->SetPos(Vector3(0.f, 18.f, 4.999f));
			UpOutWall->SetColliderScale(Vector2(100.f, 0.5f));
		}

		{
			COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
			DownOutWall->SetPos(Vector3(0.f, -5.f, 4.999f));
			DownOutWall->SetColliderScale(Vector2(100.f, 0.5f));
		}
	}

	void CStage2::CreateFirstFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-4.5f, -3.7f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });

		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-5.7f, -0.65f, 3.f));
			Ceiling->SetColliderScale({ 10.f, 0.1f });
		}

		{
			CStair* stair = object::Instantiate<CStair>(eLayerType::Platforms, L"stair");
			stair->SetPos(Vector3(2.65f, -1.9f, 3.f));
			stair->GetComponent<CTransform>()->SetRotationZ(45.f);
			stair->SetColliderScale({ 5.5f, 0.01f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ -2.5f, -2.f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(2.5f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.5f });
		}
		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 0.f, -1.f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(1.5f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.25f });
		}

	}

	void CStage2::CreateSecondFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(-11.5f, -0.11f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}
		{
			CFloor2* Floor2 = object::Instantiate<CFloor2>(eLayerType::Platforms, L"floor2");
			Floor2->SetPos(Vector3(1.6f, -0.025f, 3.f));
			Floor2->SetColliderScale({ 6.f, 0.2f });
		}

		{
			CStair* stair = object::Instantiate<CStair>(eLayerType::Platforms, L"stair");
			stair->SetPos(Vector3(-1.025f, -0.29f, 3.f));
			stair->GetComponent<CTransform>()->SetRotationZ(-45.f);
			stair->SetColliderScale({ 1.f, 0.01f });
		}


		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(14.75f, -0.11f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });

		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-6.5f, 3.f, 3.f));
			Ceiling->SetColliderScale({ 100.f, 0.1f });
		}

		{
			CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
			Wall->SetPos(Vector3(-1.4f, 3.f, 3.f));
			Wall->SetColliderScale({ 0.7f, 2.5f });
		}

		{
			CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
			Ceiling->SetPos(Vector3(-1.4f, 1.75f, 3.f));
			Ceiling->SetColliderScale({ 0.5f, 0.1f });
		}

		{
			CGameObj* plant = object::Instantiate<CGameObj>(eLayerType::Objects, L"plant");
			plant->SetPos(Vector3(-3.4f, 0.6f, 3.f));
			plant->SetScale({ 0.5f, 1.f, 0.f });
			CSpriteRenderer* SpriteRenderer = plant->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			SpriteRenderer->SetMaterialByKey(L"plantMat");
		}

		{
			CGameObj* desk = object::Instantiate<CGameObj>(eLayerType::Objects, L"desk");
			desk->SetPos(Vector3(-5.4f, 0.6f, 3.f));
			desk->SetScale({ 2.f, 1.f, 0.f });
			CSpriteRenderer* SpriteRenderer = desk->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			SpriteRenderer->SetMaterialByKey(L"deskMat");
		}

		{
			CLightObject* halogen = object::Instantiate<CLightObject>(eLayerType::Objects, L"Halogen");
			halogen->SetPos(Vector3(-4.f, 2.85f, 1.f));
			halogen->SetScale(Vector3(0.125f, 0.125f, 1.f));
			halogen->SetMaterial(L"halogenMat", { 92.f, 15.f });
			halogen->PlayAnim({ 46.f, 15.f });
		}

		{
			CLightObject* halogen = object::Instantiate<CLightObject>(eLayerType::Objects, L"Halogen");
			halogen->SetPos(Vector3(-7.55f, 2.85f, 1.f));
			halogen->SetScale(Vector3(0.125f, 0.125f, 1.f));
			halogen->SetMaterial(L"halogenMat", { 92.f, 15.f });
			halogen->PlayAnim({ 46.f, 15.f });

		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 2.f, 2.3f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(1.5f);
			lightComp->SetDiffuse({ 0.f, 1.f, 0.f, 0.5f });
		}

		{
			CGameObj* PointLight = object::Instantiate<CGameObj>(eLayerType::None, mScene, L"PointLight");
			PointLight->SetPos({ 5.f, 2.5f, 0.f });
			CLight* lightComp = PointLight->AddComponent<CLight>(eComponentType::Light);
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(2.5f);
			lightComp->SetDiffuse({ 0.f, 1.f, 1.f, 0.5f });
		}
	}

}