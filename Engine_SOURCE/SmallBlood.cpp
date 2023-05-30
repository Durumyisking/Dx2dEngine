#include "SmallBlood.h"
#include "SceneMain.h"
#include "SceneMgr.h"
#include "Scene.h"

namespace dru
{
	CSmallBlood::CSmallBlood()
	{
		SetLayerType(eLayerType::BackGround);

		CSpriteRenderer* spriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::wstring textureName = L"smallBlood";
		std::wstring number = std::to_wstring(GetRandomNumber(4, 1));
		textureName += number;
		textureName += L"Mat";
		spriteRenderer->SetMaterialByKey(textureName);

	}

	CSmallBlood::~CSmallBlood()
	{
	}

	void CSmallBlood::Initialize()
	{
		CSceneMain* mainScene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
		mainScene->GetCurrentStage()->PushRewindObject(this);


		CLiveGameObj::Initialize();
	}

	void CSmallBlood::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}
		CLiveGameObj::update();
	}

	void CSmallBlood::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CSmallBlood::render()
	{
		CLiveGameObj::render();
	}

	void CSmallBlood::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

}