#include "Cop.h"
#include "CopScript.h"

namespace dru
{
	CCop::CCop()
	{
		SetName(L"Cop");
		SetScale(Vector3(1.15f, 1.15f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop", L"SpriteShader");
		CResources::Insert<CMaterial>(L"CopMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Cop_Idle", Material->GetTexture(), { 2112.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_Run", Material->GetTexture(), { 2622.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_Attack", Material->GetTexture(), { 0.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadAirUp", Material->GetTexture(), { 1152.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadAirDown", Material->GetTexture(), { 1216.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadGround", Material->GetTexture(), { 1280.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 13, { 50.f, 50.f }, 0.1f);

		mAnimator->Play(L"Cop_Idle");

		this->AddComponent<CCopScript>(eComponentType::Script)->Initialize();
	}

	CCop::~CCop()
	{
	}

	void CCop::Initialize()
	{
		mRayScale = Vector3(8.f, 0.f, 1.f);
		AddRay(mRayScale);
		CMonster::Initialize();
	}
	void CCop::update()
	{
		CMonster::update();
	}
	void CCop::fixedUpdate()
	{

		CMonster::fixedUpdate();
	}
	void CCop::render()
	{

		CMonster::render();
	}
	void CCop::rewindRender()
	{
		CMonster::rewindRender();
	}
}
