#include "Grunt.h"


namespace dru
{
	CGrunt::CGrunt()
	{
		CSpriteRenderer* SpriteRenderer = this->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"grunt", L"SpriteShader");
		CResources::Insert<CMaterial>(L"GruntMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = this->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Grunt_Idle", Material->GetTexture(), { 4480.f, 0.f }, { 64.f, 64.f }, Vector2::Zero, 8, { 50.f, 50.f }, 0.1f);

		mAnimator->Play(L"Grunt_Idle");
	}

	CGrunt::~CGrunt()
	{
	}

	void CGrunt::Initialize()
	{
		CMonster::Initialize();
	}

	void CGrunt::update()
	{
		CMonster::update();
	}

	void CGrunt::fixedUpdate()
	{
		CMonster::fixedUpdate();
	}

	void CGrunt::render()
	{
		CMonster::render();
	}

}