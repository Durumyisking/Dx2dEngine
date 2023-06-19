#include "BossStage2.h"
#include "Headhunter.h"
#include "BossScript.h"

namespace dru
{
	CBossStage2::CBossStage2()
	{
		mStageNumbmer = 5;
	}

	CBossStage2::~CBossStage2()
	{
	}

	void CBossStage2::InitStage()
	{
		/////////////////////////////Obj Add /////////////////////////////////////
		{
			
			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage2");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bossStage2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bossStage2Mat", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(0.f, 0.5f, 5.f));
			mStageBackground->SetScale(Vector3(1.75f, 1.75f, 1.f));
		}

		renderer::mainCamera->GetOwner()->SetPos({ 0.f, 0.75f, 0.f });
		CCollider2D* coll = renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>();
		coll->SetScale(Vector2(GetDevice()->ViewportWidth() / 102.125f, GetDevice()->ViewportHeight() / 102.5f));

		mPlayerDefaultPos = Vector3(-3.5f, -1.f, 3.f);
		mHeadhunterDefaultPos = Vector3(3.f, -1.f, 3.f);

		mStageState = eStageState::Ready;

		mEnemyCount = 1;

		AddStartingLiveObjects();

		CreateOutWall();
		CreateFirstFloor();
	}

	void CBossStage2::LoadinReady()
	{
	}

	void CBossStage2::Update()
	{
		if (mHeadhunter->IsDeadState())
		{
			mPlayer->GetComponent<CAudioSource>()->SetVolume(L"song_boss_bgm", 0.f);
			mPlayer->GetComponent<CAudioSource>()->Stop(L"song_boss_bgm");
		}

		CStage::Update();
	}

	void CBossStage2::Exit()
	{
		mPlayer->GetComponent<CAudioSource>()->Stop(L"song_boss_bgm");
		CStage::Exit();
	}

	void CBossStage2::NotReadyOperate()
	{
		CStage::NotReadyOperate();
	}

	void CBossStage2::ReadyOperate()
	{
		mPlayer->GetComponent<CAudioSource>()->Play(L"song_boss_bgm", true);
		CStage::ReadyOperate();
	}

	void CBossStage2::ReadyEndOperate()
	{
		CStage::ReadyEndOperate();
	}

	void CBossStage2::LoadUIOperate()
	{
		CStage::LoadUIOperate();
	}

	void CBossStage2::LoadEndOperate()
	{
		CStage::LoadEndOperate();
	}

	void CBossStage2::Reset()
	{
		mPlayer->SetPos(mPlayerDefaultPos);
		mPlayer->GetComponent<CAudioSource>()->Play_NoInterrupt(L"song_boss_bgm", true);
		CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
		playerScript->Reset();

		mHeadhunter->SetPos(mHeadhunterDefaultPos);
		mHeadhunter->GetScript<CBossScript>()->Reset();
		mHeadhunter->SetLeft();

		CStage::Reset();
	}

	void CBossStage2::AddStartingLiveObjects()
	{
		mHeadhunter = object::Instantiate<CHeadhunter>(eLayerType::Boss, L"Headhunter");
		mHeadhunter->SetPos(mHeadhunterDefaultPos);
		mRewindObjects.push_back(mHeadhunter);
		mHeadhunter->SetLeft();

		CStage::AddStartingLiveObjects();

		mHeadhunter->GetScript<CBossScript>()->SetPlayer(mPlayer);
	}

	void CBossStage2::CreateOutWall()
	{
		{
			COutWallSide* LeftOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"LeftOutwall");
			LeftOutWall->SetPos(Vector3(-8.f, 0.f, 4.999f));
			LeftOutWall->SetColliderScale(Vector2(0.5f, 30.f));
		}
		{
			COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
			RightOutWall->SetPos(Vector3(8.f, 0.f, 4.999f));
			RightOutWall->SetColliderScale(Vector2(0.5f, 30.f));
		}
		{
			COutWall* UpOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"UpOutWall");
			UpOutWall->SetPos(Vector3(0.f, -3.75f, 4.999f));
			UpOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}
		{
			COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
			DownOutWall->SetPos(Vector3(0.f, 5.85f, 4.999f));
			DownOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}
	}

	void CBossStage2::CreateFirstFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(0.f, -2.575f, 3.f));
			Floor->SetColliderScale({ 20.f, 0.4f });
		}
		{
			CWall* LeftWall = object::Instantiate<CWall>(eLayerType::Platforms, L"Leftwall");
			LeftWall->SetPos(Vector3(-8.f, 0.f, 4.999f));
			LeftWall->SetColliderScale(Vector2(0.6f, 30.f));
		}
		{
			CWall* RightWall = object::Instantiate<CWall>(eLayerType::Platforms, L"Rightwall");
			RightWall->SetPos(Vector3(8.f, 0.f, 4.999f));
			RightWall->SetColliderScale(Vector2(0.6f, 30.f));
		}

		SetClearCollider({ 8.f, -2.f, 0.f });

	}

}