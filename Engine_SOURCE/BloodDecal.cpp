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

		CSpriteRenderer* spriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::wstring textureName = L"bloodDecal";
		std::wstring number = std::to_wstring(GetRandomNumber(9, 1));
		textureName += number;
		textureName += L"Mat";
		spriteRenderer->SetMaterialByKey(textureName);
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