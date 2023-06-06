#include "HorizonGauge.h"
#include "HorizonGaugeScript.h"

namespace dru
{
	CHorizonGauge::CHorizonGauge()
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
		CResources::Insert<CMaterial>(L"HorizonGauge", Material);
		SpriteRenderer->SetMaterial(Material);
		SpriteRenderer->ChangeColor({ 1.f,1.f,1.f,1.f });

		AddComponent<CHorizonGaugeScript>(eComponentType::Script);
	}

	CHorizonGauge::~CHorizonGauge()
	{
	}

	void CHorizonGauge::Initialize()
	{ 
		CGameObj::Initialize();
	}

	void CHorizonGauge::update()
	{
		CGameObj::update();
	}

	void CHorizonGauge::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CHorizonGauge::render()
	{
		CGameObj::render();
	}

	void CHorizonGauge::Play()
	{
		GetScript<CHorizonGaugeScript>()->Play();
	}

	void CHorizonGauge::SetTimer(float _Timer)
	{
		GetScript<CHorizonGaugeScript>()->SetTimer(_Timer);
	}

}