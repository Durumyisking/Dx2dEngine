#include "Dust.h"
#include "Animator.h"
#include "RigidBody.h"

namespace dru
{

	CDust::CDust()
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"dustMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"dust", Material->GetTexture(), { 0.f, 0.f }, { 20.f, 20.f }, Vector2::Zero, 7, { 40.f, 40.f }, 0.05f);
		mAnimator->Play(L"dust", false);

		mRigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);
		mRigidbody->AffectedGravityOff();

		mRigidbody->SetMaxVelocity({ 1.f,0.5f,0.f });
		mRigidbody->SetVelocity({ 1.f,1.f,0.f });

		mAnimator->GetCompleteEvent(L"dust") = std::bind(&CDust::rundustComplete, this);
	}

	CDust::~CDust()
	{
	}

	void CDust::Initialize()
	{
		CGameObj::Initialize();
	}

	void CDust::update()
	{
		CGameObj::update();
	}

	void CDust::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CDust::render()
	{
		CGameObj::render();
	}

	void CDust::SetVelocity(Vector3 _vel)
	{
		Vector3 absVel = Vector3(fabs(_vel.x), fabs(_vel.y), 0.f);
		mRigidbody->SetMaxVelocity(absVel);
		mRigidbody->SetVelocity(_vel);
	}

	void CDust::rundustComplete()
	{
		if(this != nullptr)
			Die();
	}

}