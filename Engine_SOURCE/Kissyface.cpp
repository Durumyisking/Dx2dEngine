#include "Kissyface.h"
#include "KissyfaceScript.h"
#include "Input.h"
#include "Object.h"
#include "Axe.h"

namespace dru
{
	CKissyface::CKissyface()
		: mAnimator(nullptr)
		, mAxe(nullptr)
	{
		SetName(L"kissyface");
		SetScale(Vector3(2.5f, 2.5f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyfaceMat", Material);
		SpriteRenderer->SetMaterial(Material);

		CAudioSource* audioSource = AddComponent<CAudioSource>(eComponentType::AudioSource);
		audioSource->AddClipByKey(L"kissyface_axecatch");
		audioSource->AddClipByKey(L"kissyface_axelunge");
		audioSource->AddClipByKey(L"kissyface_axeprepare");
		audioSource->AddClipByKey(L"kissyface_clash");
		audioSource->AddClipByKey(L"kissyface_crouch");
		audioSource->AddClipByKey(L"kissyface_death");
		audioSource->AddClipByKey(L"kissyface_jump");
		audioSource->AddClipByKey(L"kissyface_sharpen");
		audioSource->AddClipByKey(L"kissyface_struggle");

		audioSource->AddClipByKey(L"kissyface_voice_axethrow");
		audioSource->AddClipByKey(L"kissyface_voice_chop");
		audioSource->AddClipByKey(L"kissyface_voice_crouch");
		audioSource->AddClipByKey(L"kissyface_voice_hurt");
		audioSource->AddClipByKey(L"kissyface_voice_jump");
		audioSource->AddClipByKey(L"kissyface_voice_lunge");
		audioSource->AddClipByKey(L"kissyface_voice_prepare");


		mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"kissyface_Idle", Material->GetTexture(), { 256.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Waiting", Material->GetTexture(), { 640.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_WaitingEnd", Material->GetTexture(), { 4608.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Walk", Material->GetTexture(), { 6272.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 10, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Block", Material->GetTexture(), { 128.f, 0.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Hurt", Material->GetTexture(), { 384.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 6, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Struggle", Material->GetTexture(), { 3328.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 2, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_GetUp", Material->GetTexture(), { 6656.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 7, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_CutArm", Material->GetTexture(), { 2560.f, 0.f }, { 128.f, 128.f }, Vector2::Zero, 14, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Dying", Material->GetTexture(), { 1152.f, 0.f }, { 128.f, 128.f }, Vector2::Zero, 11, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Dead", Material->GetTexture(), { 3968.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 7, { 90.f, 90.f }, 0.1f);


		// pattern 1
		mAnimator->Create(L"kissyface_JumpStart", Material->GetTexture(), { 2304.f, 128.f }, { -128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowAxe", Material->GetTexture(), { 1152.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 4, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_AirThrowEnd", Material->GetTexture(), { 1664.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 100.f);
		mAnimator->Create(L"kissyface_Land", Material->GetTexture(), { 1792.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);


		// pattern 2
		mAnimator->Create(L"kissyface_ThrowAxe", Material->GetTexture(), { 3584.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 8, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_ThrowAxeEnd", Material->GetTexture(), { 4480.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 1, { 90.f, 90.f }, 100.f);
		mAnimator->Create(L"kissyface_RecieveAxe", Material->GetTexture(), { 0.f, 256.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);

		// pattern 3
		mAnimator->Create(L"kissyface_LungeReady", Material->GetTexture(), { 4864.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 4, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_Lunge", Material->GetTexture(), { 2432.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 5, { 90.f, 90.f }, 0.1f);
		mAnimator->Create(L"kissyface_LungeAttack", Material->GetTexture(), { 3072.f, 128.f }, { 128.f, 128.f }, Vector2::Zero, 7, { 90.f, 90.f }, 0.1f);

		mAnimator->Play(L"kissyface_Waiting");

		AddComponent<CKissyfaceScript>(eComponentType::Script)->Initialize();

		mAfterImageCount = 0;

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));

		CraeteAxe();
	}

	CKissyface::~CKissyface()
	{
	}

	void CKissyface::Initialize()
	{
		mMaxHp = 1;
		mHp = 1;

		CBoss::Initialize();
	}

	void CKissyface::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(true, 90.f);
		}

		CBoss::update();
	}

	void CKissyface::fixedUpdate()
	{
		CBoss::fixedUpdate();
	}

	void CKissyface::render()
	{
		CBoss::render();
	}

	void CKissyface::rewindRender()
	{
		CBoss::rewindRender();
	}

	void CKissyface::CraeteAxe()
	{
		mAxe = object::Instantiate<CAxe>(eLayerType::Bullet, this, L"Axe");		
		mAxe->SetKissyface(this);
	}

}