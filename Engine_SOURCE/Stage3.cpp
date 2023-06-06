#include "Stage3.h"

namespace dru
{
    CStage3::CStage3()
        :mPomp1(nullptr)
        ,mPomp1DefaultPos{}
    {
        mStageNumbmer = 4;
    }

    CStage3::~CStage3()
    {
    }

    void CStage3::InitStage()
    {
        /////////////////////////////Obj Add /////////////////////////////////////
        {
            // ¹è°æ Stage3
            mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage3");
            CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

            std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage3", L"SpriteShader");
            CResources::Insert<CMaterial>(L"Stage3", Material);
            SpriteRenderer->SetMaterial(Material);
            mStageBackground->SetPos(Vector3(0.9f, -6.f, 5.f));
            mStageBackground->SetScale(Vector3(2.f, 2.f, 1.f));
        }

        mPlayerDefaultPos = Vector3(-6.f, 1.f, 3.f);
        mPomp1DefaultPos = Vector3(0.f, -4.f, 3.f);

        mEnemyCount = 1;
        mStageState = eStageState::Ready;

        AddStartingLiveObjects();

        CreateOutWall();
        CreateFirstFloor();
        CreateSecondFloor();
    }

    void CStage3::LoadinReady()
    {
    }

    void CStage3::Update()
    {
        CStage::Update();
    }

    void CStage3::Exit()
    {
        CStage::Exit();
        mPlayer->GetComponent<CAudioSource>()->Stop(L"song_main_bgm");
    }

    void CStage3::Reset()
    {
        mPlayer->SetPos(mPlayerDefaultPos);
        mPlayer->GetComponent<CAudioSource>()->Play(L"song_main_bgm", true);
        CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
        playerScript->Reset();


        mPomp1->SetPos(mPomp1DefaultPos);
        mPomp1->GetScript<CMonsterScript>()->Reset();


        CStage::Reset();
    }

    void CStage3::AddStartingLiveObjects()
    {
        {
            mPomp1 = object::Instantiate<CPomp>(eLayerType::Monster, L"Pomp");
            mPomp1->SetPos(mPomp1DefaultPos);
            mPomp1->SetLeft();
            mRewindObjects.push_back(mPomp1);
        }

        CStage::AddStartingLiveObjects();
    }

    void CStage3::NotReadyOperate()
    {
        CStage::NotReadyOperate();
    }

    void CStage3::ReadyOperate()
    {
        mPlayer->GetComponent<CAudioSource>()->Play(L"song_main_bgm", true);
        CStage::ReadyOperate();
    }

    void CStage3::ReadyEndOperate()
    {
        CStage::ReadyEndOperate();
    }

    void CStage3::LoadUIOperate()
    {
        CStage::LoadUIOperate();
    }

    void CStage3::LoadEndOperate()
    {
        CStage::LoadEndOperate();
    }

    void CStage3::CreateOutWall()
    {
        {
            COutWallSide* LeftOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"LeftOutwall");
            LeftOutWall->SetPos(Vector3(-8.2f, 0.f, 4.999f));
            LeftOutWall->SetColliderScale(Vector2(0.5f, 100.f));
        }


        {
            COutWallSide* RightOutWall = object::Instantiate<COutWallSide>(eLayerType::Platforms, L"RightOutwall");
            RightOutWall->SetPos(Vector3(13.5f, 0.f, 4.999f));
            RightOutWall->SetColliderScale(Vector2(0.5f, 100.f));
        }

        {
            COutWall* UpOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"UpOutWall");
            UpOutWall->SetPos(Vector3(0.f, 5.f, 4.999f));
            UpOutWall->SetColliderScale(Vector2(100.f, 0.4f));
        }

        {
            COutWall* DownOutWall = object::Instantiate<COutWall>(eLayerType::Platforms, L"DownOutWall");
            DownOutWall->SetPos(Vector3(0.f, -25.f, 4.999f));
            DownOutWall->SetColliderScale(Vector2(100.f, 0.4f));
        }

    }

    void CStage3::CreateFirstFloor()
    {
        {
            CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-7.7f, -0.61f, 3.f));
            Floor->SetColliderScale({ 4.5f, 0.4f });
        }
        {
            CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-1.3f, -0.61f, 3.f));
            Floor->SetColliderScale({ 4.5f, 0.4f });
        }
        {
            CFloor2* Floor = object::Instantiate<CFloor2>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-4.3f, -0.61f, 3.f));
            //Floor->SetColliderScale({ 2.f, 0.1f });
            Floor->SetColliderScale({ 2.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(-4.f, 2.2f, 3.f));
            Ceiling->SetColliderScale({ 10.f, 0.4f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(0.85f, 1.f, 3.f));
            Wall->SetColliderScale({ 0.3f, 3.f });
        }


    }

    void CStage3::CreateSecondFloor()
    {
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(-5.45f, -3.f, 3.f));
            Wall->SetColliderScale({ 0.3f, 5.f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(-3.55f, -1.4f, 3.f));
            Wall->SetColliderScale({ 0.3f, 1.75f });
        }
        {
            CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-0.4f, -5.f, 3.f));
            Floor->SetColliderScale({ 11.5f, 0.4f });
        }

    }


}