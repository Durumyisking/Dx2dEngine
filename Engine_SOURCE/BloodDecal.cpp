#include "BloodDecal.h"
#include "Object.h"
#include "SceneMain.h"
#include "SceneMgr.h"
#include "Scene.h"

namespace dru
{
	CBloodDecal::CBloodDecal()
	{
		SetLayerType(eLayerType::BackGround);
		SetScale({2.f, 2.f, 1.f});

		CSpriteRenderer* spriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::wstring textureName = L"bloodDecal";
		std::wstring number = std::to_wstring(GetRandomNumber(6, 1));
		textureName += number;
		textureName += L"Mat";
		spriteRenderer->SetMaterialByKey(textureName);
		spriteRenderer->MulColor({ 1.f, 1.f, 1.f, 0.75f });
	}

	CBloodDecal::~CBloodDecal()
	{
	}

	void CBloodDecal::Initialize()
	{
		CSceneMain* mainScene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
		mainScene->GetCurrentStage()->PushRewindObject(this);

		CLiveGameObj::Initialize();
	}

	void CBloodDecal::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}
		CLiveGameObj::update();
	}

	void CBloodDecal::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBloodDecal::render()
	{
		CLiveGameObj::render();
	}

	void CBloodDecal::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

}