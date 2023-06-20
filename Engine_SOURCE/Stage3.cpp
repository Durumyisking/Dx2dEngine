#include "Stage3.h"

namespace dru
{
    CStage3::CStage3()
        : mPomp1(nullptr)
        , mPomp2(nullptr)
        , mGrunt1(nullptr)
        , mGrunt2(nullptr)
        , mCop1(nullptr)
        , mCop2(nullptr)
        , mDoor1(nullptr)
        , mDoor2(nullptr)
        , mDoor3(nullptr)
        , mLaserFloor(nullptr)
        , mLaserTurret1(nullptr)
        , mLaserTurret2(nullptr)
        , mLaserTurret3(nullptr)
        , mPomp1DefaultPos{}
        , mPomp2DefaultPos{}
        , mGrunt1DefaultPos{}
        , mGrunt2DefaultPos{}
        , mCop1DefaultPos{}
        , mCop2DefaultPos{}
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
        mPomp2DefaultPos = Vector3(6.3f, -8.5f, 3.f);
        mGrunt1DefaultPos = Vector3(1.5f, -4.f, 3.f);
        mGrunt2DefaultPos = Vector3(1.5f, -14.f, 3.f);
        mCop1DefaultPos = Vector3(-4.f, -8.f, 3.f);
        mCop2DefaultPos = Vector3(6.5f, -14.f, 3.f);

        mEnemyCount = 6;
        mStageState = eStageState::Ready;

        AddStartingLiveObjects();

        CreateOutWall();
        CreateFirstFloor();
        CreateSecondFloor();
        CreateThirdFloor();
        CreateFourthFloor();

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
        mPlayer->GetComponent<CAudioSource>()->Stop(L"song_main_bgm");
        CStage::Exit();
    }

    void CStage3::Reset()
    {
        mPlayer->SetPos(mPlayerDefaultPos);
        mPlayer->GetComponent<CAudioSource>()->Play(L"song_main_bgm", true);
        CPlayerScript* playerScript = mPlayer->GetScript<CPlayerScript>();
        playerScript->Reset();

        mPomp1->SetPos(mPomp1DefaultPos);
        mPomp1->GetScript<CMonsterScript>()->Reset();

        mPomp2->SetPos(mPomp2DefaultPos);
        mPomp2->RayExceptWallOn(); 
        mPomp2->GetScript<CMonsterScript>()->Reset();
        
        mGrunt1->SetPos(mGrunt1DefaultPos);
        mGrunt1->GetScript<CMonsterScript>()->Reset();

        mGrunt2->SetPos(mGrunt2DefaultPos);
        mGrunt2->GetScript<CMonsterScript>()->Reset();

        mCop1->SetPos(mCop1DefaultPos);
        mCop1->GetScript<CMonsterScript>()->Reset();

        mCop2->SetPos(mCop2DefaultPos);
        mCop2->GetScript<CMonsterScript>()->Reset();

        mLaserTurret1->Reset();
        mLaserTurret2->Reset();
        mLaserTurret3->Reset();

        mEnemyCount = 6;


        mDoor1->GetScript<CDoorScript>()->Reset();
        mDoor2->GetScript<CDoorScript>()->Reset();
        mDoor3->GetScript<CDoorScript>()->Reset();

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
        {
            mPomp2 = object::Instantiate<CPomp>(eLayerType::Monster, L"Pomp");
            mPomp2->SetPos(mPomp2DefaultPos);
            mPomp2->SetLeft();
            mRewindObjects.push_back(mPomp2);
        }
        {
            mGrunt1 = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
            mGrunt1->SetPos(mGrunt1DefaultPos);
            mGrunt1->SetRight();
            mGrunt1->MonsterPatrolOn();
            mRewindObjects.push_back(mGrunt1);
        }
        {
            mGrunt2 = object::Instantiate<CGrunt>(eLayerType::Monster, L"Grunt");
            mGrunt2->SetPos(mGrunt2DefaultPos);
            mGrunt2->SetLeft();
            mGrunt2->MonsterPatrolOn();
            mRewindObjects.push_back(mGrunt2);
        }
        {
            mCop1 = object::Instantiate<CCop>(eLayerType::Monster, L"Cop");
            mCop1->SetPos(mCop1DefaultPos);
            mCop1->SetRight();
            mRewindObjects.push_back(mCop1);
        }
        {
            mCop2 = object::Instantiate<CCop>(eLayerType::Monster, L"Cop");
            mCop2->SetPos(mCop2DefaultPos);
            mCop2->SetLeft();
            mRewindObjects.push_back(mCop2);
        }
        {
            mDoor1 = object::Instantiate<CDoor>(eLayerType::Objects, L"door");
            mDoor1->SetPos({1.1f, -4.f, 0.f});
            mRewindObjects.push_back(mDoor1);
        }
        {
            mDoor2 = object::Instantiate<CDoor>(eLayerType::Objects, L"door");
            mDoor2->SetPos({ 1.1f, -8.8f, 0.f });
            mDoor2->SetLeft();
            mRewindObjects.push_back(mDoor2);
        }
        {
            mDoor3 = object::Instantiate<CDoor>(eLayerType::Objects, L"door");
            mDoor3->SetPos({ 1.1f, -13.6f, 0.f });
            mRewindObjects.push_back(mDoor3);
        }

        CStage::AddStartingLiveObjects();

        dynamic_cast<CPomp*>(mPomp1)->SetPlayer(mPlayer);
        dynamic_cast<CPomp*>(mPomp2)->SetPlayer(mPlayer);
    }

    void CStage3::NotReadyOperate()
    {
        CStage::NotReadyOperate();
    }

    void CStage3::ReadyOperate()
    {
        mPlayer->GetComponent<CAudioSource>()->Play(L"song_main_bgm", true);
        mPomp2->RayExceptWallOn();
        mLaserTurret1->AdjustLaserTransform();
        mLaserTurret2->AdjustLaserTransform();
        mLaserTurret3->AdjustLaserTransform();
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
            RightOutWall->SetPos(Vector3(10.f, 0.f, 4.999f));
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
            CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-0.4f, -5.f, 3.f));
            Floor->SetColliderScale({ 11.5f, 0.4f });
        }
        {
            CFloor2* Floor = object::Instantiate<CFloor2>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(6.3f, -5.f, 3.f));
            Floor->SetColliderScale({ 2.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(2.5f, -2.2f, 3.f));
            Ceiling->SetColliderScale({ 12.f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(1.1f, -3.0f, 3.f));
            Ceiling->SetColliderScale({ 0.5f, 0.4f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(1.1f, -2.4f, 3.f));
            Wall->SetColliderScale({ 0.75f, 1.5f });
        }

        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(-5.45f, -15.5f, 3.f));
            Wall->SetColliderScale({ 0.3f, 30.f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(-3.55f, -1.4f, 3.f));
            Wall->SetColliderScale({ 0.3f, 1.75f });
        }      
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(5.35f, -6.f, 3.f));
            Wall->SetColliderScale({ 0.3f, 2.25f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(7.275f, -5.f, 3.f));
            Wall->SetColliderScale({ 0.3f, 12.25f });
        }

    }

    void CStage3::CreateThirdFloor()
    {
        {
            mLaserFloor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            mLaserFloor->SetPos(Vector3(2.2f, -9.825f, 3.f));
            mLaserFloor->SetColliderScale({ 11.5f, 0.4f });

            mLaserTurret1 = object::Instantiate<CTurret>(eLayerType::None, L"Laser");
            mLaserTurret1->SetPos(Vector3(3.9f, -7.35f, 3.f));
            mLaserTurret1->SetScale({ 0.25f, 0.25f, 0.f });
            mLaserTurret1->SetDestinationFloor(mLaserFloor);

            mLaserTurret2 = object::Instantiate<CTurret>(eLayerType::None, L"Laser");
            mLaserTurret2->SetPos(Vector3(3.5f, -7.35f, 3.f));
            mLaserTurret2->SetScale({ 0.25f, 0.25f, 0.f });
            mLaserTurret2->SetDestinationFloor(mLaserFloor);

            mLaserTurret3 = object::Instantiate<CTurret>(eLayerType::None, L"Laser");
            mLaserTurret3->SetPos(Vector3(3.1f, -7.35f, 3.f));
            mLaserTurret3->SetScale({ 0.25f, 0.25f, 0.f });
            mLaserTurret3->SetDestinationFloor(mLaserFloor);
        }
        {
            CFloor2* Floor = object::Instantiate<CFloor2>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(-4.5f, -9.825f, 3.f));
            Floor->SetColliderScale({ 2.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(-0.4f, -7.f, 3.f));
            Ceiling->SetColliderScale({ 11.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(1.1f, -7.8f, 3.f));
            Ceiling->SetColliderScale({ 0.5f, 0.4f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(1.1f, -7.2f, 3.f));
            Wall->SetColliderScale({ 0.75f, 1.5f });
        }

        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(-3.525f, -10.75f, 3.f));
            Wall->SetColliderScale({ 0.3f, 2.1f });
        }

    }

    void CStage3::CreateFourthFloor()
    {
        {
            CFloor* Floor = object::Instantiate<CFloor>(eLayerType::Platforms, L"floor");
            Floor->SetPos(Vector3(3.f, -14.595f, 3.f));
            Floor->SetColliderScale({ 20.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(-1.25f, -11.8f, 3.f));
            Ceiling->SetColliderScale({ 4.5f, 0.4f });
        }
        {
            CCeiling* Ceiling = object::Instantiate<CCeiling>(eLayerType::Platforms, L"ceiling");
            Ceiling->SetPos(Vector3(1.1f, -12.6f, 3.f));
            Ceiling->SetColliderScale({ 0.5f, 0.4f });
        }
        {
            CWall* Wall = object::Instantiate<CWall>(eLayerType::Platforms, L"wall");
            Wall->SetPos(Vector3(1.1f, -12.f, 3.f));
            Wall->SetColliderScale({ 0.75f, 1.5f });
        }


        SetClearCollider({ 9.75f, -14.f, 0.f });

    }


}