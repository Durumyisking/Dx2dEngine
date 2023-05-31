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

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PompMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Pomp_Idle", Material->GetTexture(), { 4480.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Patrol", Material->GetTexture(), { 12032.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Run", Material->GetTexture(), { 6016.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_Attack", Material->GetTexture(), { 0.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 8, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadAirUp", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadAirDown", Material->GetTexture(), { 3392.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 1, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Pomp_DeadGround", Material->GetTexture(), { 3328.f, 0.f }, { 64.f, 64.f }, mAnimOffset, 18, { 50.f, 50.f }, 0.1f);

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