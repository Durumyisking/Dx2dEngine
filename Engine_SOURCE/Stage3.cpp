#include "Stage3.h"

namespace dru
{
    CStage3::CStage3()
    {

        /////////////////////////////Obj Add /////////////////////////////////////
        {
            // ¹è°æ Stage3
            mStageBackground = object::Instantiate<CBackground>(eLayerType::BackGround, L"Stage3");
            CSpriteRenderer* SpriteRenderer = mStageBackground->AddComponent<CSpriteRenderer>(eComponentType::Renderer);

            std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"stage3", L"SpriteShader");
            CResources::Insert<CMaterial>(L"Stage3", Material);
            SpriteRenderer->SetMaterial(Material);
            mStageBackground->SetPos(Vector3(2.25f, 0.f, 5.f));
            mStageBackground->SetScale(Vector3(1.f, 1.f, 1.f));
        }

        mPlayerDefaultPos = Vector3(-6.f, -3.f, 3.f);

        mEnemyCount = 1;
        mStageState = eStageState::Ready;

        AddStartingLiveObjects();
    }

    CStage3::~CStage3()
    {
    }

    void CStage3::InitStage()
    {
    }

    void CStage3::LoadinReady()
    {
    }

    void CStage3::Update()
    {
    }

    void CStage3::Exit()
    {
    }

    void CStage3::Reset()
    {
   
        CStage::Reset();
    }

    void CStage3::AddStartingLiveObjects()
    {
        CStage::AddStartingLiveObjects();
    }

    void CStage3::NotReadyOperate()
    {
    }

    void CStage3::ReadyOperate()
    {
    }

    void CStage3::ReadyEndOperate()
    {
    }

    void CStage3::LoadUIOperate()
    {
    }

    void CStage3::LoadEndOperate()
    {
    }


}