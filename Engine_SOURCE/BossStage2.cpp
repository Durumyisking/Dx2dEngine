#include "BossStage2.h"
namespace dru
{
	CBossStage2::CBossStage2()
	{
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

			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Stage2", Material);
			SpriteRenderer->SetMaterial(Material);
			mStageBackground->SetPos(Vector3(2.25f, 0.f, 5.f));
			mStageBackground->SetScale(Vector3(1.f, 1.f, 1.f));
		}


		mStageState = eStageState::Ready;

		AddStartingLiveObjects();

		CreateOutWall();
		CreateFirstFloor();
	}

	void CBossStage2::LoadinReady()
	{
	}

	void CBossStage2::Update()
	{
	}

	void CBossStage2::Exit()
	{
	}

	void CBossStage2::NotReadyOperate()
	{
	}

	void CBossStage2::ReadyOperate()
	{
	}

	void CBossStage2::ReadyEndOperate()
	{
	}

	void CBossStage2::LoadUIOperate()
	{
	}

	void CBossStage2::LoadEndOperate()
	{
	}


	void CBossStage2::Reset()
	{
	}

	void CBossStage2::AddStartingLiveObjects()
	{
	}

	void CBossStage2::CreateOutWall()
	{
	}

	void CBossStage2::CreateFirstFloor()
	{
	}

}