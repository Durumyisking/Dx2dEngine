#include "BossStage1.h"
#include "Kissyface.h"
#include "KissyfaceScript.h"

namespace dru
{
	CBossStage1::CBossStage1()
		: mKissyface(nullptr)
		, mKissyfaceDefaultPos(Vector3::Zero)
	{
		mStageNumbmer = 3;
	}

	CBossStage1::~CBossStage1()
	{
	}

	void CBossStage1::InitStage()
	{
		/////////////////////////////Obj Add /////////////////////////////////////
		{

			mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"BossStage1");
			CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bossStage1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bossStage1Mat", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(-0.5f, -0.0625f, 5.f));
			mStageBackground->SetScale(Vector3(7.9f, 7.9f, 1.f));
		}

		CCollider2D* coll = renderer::mainCamera->GetOwner()->GetComponent<CCollider2D>();
		coll->SetScale(Vector2(GetDevice()->ViewportWidth() / 102.125f, GetDevice()->ViewportHeight() / 102.5f));

		mPlayerDefaultPos = Vector3(-3.f, -1.25f, 3.f);
		mKissyfaceDefaultPos = Vector3(3.f, -1.25f, 3.f);

		mStageState = eStageState::Ready;

		mEnemyCount = 1;

		AddStartingLiveObjects();

		CreateOutWall();
		CreateFirstFloor();
	}

	void CBossStage1::LoadinReady()
	{
	}

	void CBossStage1::Update()
	{
		CStage::Update();
	}

	void CBossStage1::Exit()
	{
		CStage::Exit();
	}

	void CBossStage1::NotReadyOperate()
	{
		CStage::NotReadyOperate();
	}

	void CBossStage1::ReadyOperate()
	{
		CStage::ReadyOperate();
	}

	void CBossStage1::ReadyEndOperate()
	{
		CStage::ReadyEndOperate();

		if (CInput::GetKeyTap(eKeyCode::ENTER))
		{
			mKissyface->GetComponent<CAnimator>()->Play(L"kissyface_WaitingEnd", false);
		}
	}

	void CBossStage1::LoadUIOperate()
	{
		CStage::LoadUIOperate();
	}

	void CBossStage1::LoadEndOperate()
	{
		CStage::LoadEndOperate();
	}

	void CBossStage1::Reset()
	{
		mPlayer->SetPos(mPlayerDefaultPos);
		CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
		playerScript->Reset();

		mKissyface->SetPos(mKissyfaceDefaultPos);
		mKissyface->GetScript<CBossScript>()->Reset();
		mKissyface->SetRight();

		CStage::Reset();
	}

	void CBossStage1::AddStartingLiveObjects()
	{
		mKissyface = object::Instantiate<CKissyface>(eLayerType::Boss, L"kissyface");
		mKissyface->SetPos(mKissyfaceDefaultPos);
		mRewindObjects.push_back(mKissyface);
		mKissyface->SetLeft();

		mRewindObjects.push_back(dynamic_cast<CKissyface*>(mKissyface)->GetAxe());

		CStage::AddStartingLiveObjects();

		mKissyface->GetScript<CKissyfaceScript>()->SetPlayer(mPlayer);
//		mPlayer->SetScale(Vector3(1.f, 1.f, 0.f));
	}

	void CBossStage1::CreateOutWall()
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
			UpOutWall->SetPos(Vector3(0.f, -5.f, 4.999f));
			UpOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}
		{
			COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
			DownOutWall->SetPos(Vector3(0.f, 3.85f, 4.999f));
			DownOutWall->SetColliderScale(Vector2(20.f, 0.5f));
		}
	}

	void CBossStage1::CreateFirstFloor()
	{
		{
			CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
			Floor->SetPos(Vector3(0.f, -2.25f, 3.f));
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
	}

}