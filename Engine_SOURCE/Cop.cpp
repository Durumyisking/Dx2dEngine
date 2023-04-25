#include "Cop.h"
#include "CopScript.h"

namespace dru
{
	CCop::CCop()
	{
		SetName(L"Cop");
		SetScale(Vector3(1.15f, 1.15f, 1.f));
		CSpriteRenderer* SpriteRenderer = this->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"CopMat");
		SpriteRenderer->SetMaterial(Material);


		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Cop_Idle", Material->GetTexture(), { 2112.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);
	/*	mAnimator->Create(L"Cop_Run", Material->GetTexture(), { 6016.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_Attack", Material->GetTexture(), { 0.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadAirUp", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadAirDown", Material->GetTexture(), { 3392.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Cop_DeadGround", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 18, { 50.f, 50.f }, 0.1f);*/

		mAnimator->Play(L"Cop_Idle");

		this->AddComponent<CCopScript>(eComponentType::Script)->Initialize();
	}
	CCop::~CCop()
	{
	}
	void CCop::Initialize()
	{

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
}