#include "LightObject.h"
#include "Animator.h"
#include "Object.h"
#include "TimeMgr.h"

namespace dru
{
	CLightObject::CLightObject()
		:mSpriteRenderer(nullptr)
		, mMaterial(nullptr)
		, mAnimator(nullptr)
		, mPointLight(nullptr)
		, mSwitchTime(0.f)
		, mElapsedTime(0.f)
		, mIsBlinked(false)
	{
		mSpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
		
		mPointLight = object::Instantiate<CGameObj>(eLayerType::None, this, L"PointLight");
		CLight* lightComp = mPointLight->AddComponent<CLight>(eComponentType::Light);
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse({ 1.f, 1.f, 1.f, 0.5f });

		mSwitchTime = static_cast<float>(GetRandomNumber(5));
	}

	CLightObject::~CLightObject()
	{
	}

	void CLightObject::Initialize()
	{
		CGameObj::Initialize();
	}

	void CLightObject::update()
	{
		mElapsedTime += CTimeMgr::DeltaTime();
		if (mIsBlinked && (mElapsedTime > 0.25f))
		{
			mAnimator->Play(L"Halogen_On");
			mPointLight->GetComponent< CLight>()->SetDiffuse({ 1.f, 1.f, 1.f, 0.5f });
			mSwitchTime = static_cast<float>(GetRandomNumber(5));
			mElapsedTime = 0.f;
			mIsBlinked = false;
		}

		if (!mIsBlinked && (mElapsedTime > mSwitchTime))
		{
			mAnimator->Play(L"Halogen_Off");
			mPointLight->GetComponent<CLight>()->SetDiffuse({ 0.f, 0.f, 0.f, 0.f });
			mElapsedTime = 0.f;
			mIsBlinked = true;
		}

		CGameObj::update();
	}

	void CLightObject::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CLightObject::render()
	{
		CGameObj::render();
	}

	void CLightObject::SetMaterial(std::wstring _MaterialName, Vector2 _MaterialSize)
	{
		mMaterial = CResources::Find<CMaterial>(_MaterialName);
		mSpriteRenderer->SetAnimMaterial(mMaterial, _MaterialSize);
	}

	void CLightObject::PlayAnim(Vector2 _SpriteSize)
	{
		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Halogen_Off", mMaterial->GetTexture(), { 0.f, 0.f }, _SpriteSize, Vector2::Zero, 1, { _SpriteSize.x, _SpriteSize.y / 2.f }, 0.1f);
		mAnimator->Create(L"Halogen_On", mMaterial->GetTexture(), { _SpriteSize.x, 0.f }, { 46.f, 15.f }, Vector2::Zero, 1, { _SpriteSize.x, _SpriteSize.y / 2.f }, 0.1f);
		mAnimator->Play(L"Halogen_On");
	}


}