#include "Pomp.h"
#include "PompScript.h"

namespace dru
{
	CPomp::CPomp()
		: mAnimOffset(Vector2{0.f , -3.f})
	{
		SetName(L"Pomp");
		SetScale(Vector3(1.15f, 1.15f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"pomp", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PompMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Pomp_Idle", Material->GetTexture(), { 7040.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Patrol", Material->GetTexture(), { 12032.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Run", Material->GetTexture(), { 10240.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Attack", Material->GetTexture(), { 960.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 6, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_KnockedDown", Material->GetTexture(), { 7552.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 18, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadAirUp", Material->GetTexture(), { 5952.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadAirDown", Material->GetTexture(), { 6016.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadGround", Material->GetTexture(), { 6080.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 15, { 50.f, 50.f }, 0.1f);

		mAnimator->Play(L"Pomp_Idle");

		AddComponent<CPompScript>(eComponentType::Script)->Initialize();
	}

	CPomp::~CPomp()
	{
	}

	void CPomp::Initialize()
	{
		mRayScale = Vector3(6.f, 0.f, 1.f);
		AddRay(mRayScale);
		CMonster::Initialize();
	}

	void CPomp::update()
	{
		CMonster::update();
	}

	void CPomp::fixedUpdate()
	{
		CMonster::fixedUpdate();
	}

	void CPomp::render()
	{
		CMonster::render();
	}

	void CPomp::rewindRender()
	{
		CMonster::rewindRender();
	}

}