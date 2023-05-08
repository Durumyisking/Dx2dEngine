#include "Axe.h"
#include "TimeMgr.h"

namespace dru
{

	CAxe::CAxe()
		: mTransform(nullptr)
		, mDefaultPos(Vector3::Zero)
		, mFramePass(0)
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		SetScale({ 0.125f, 0.125f, 1.f });
		mDefaultPos = { 0.5f, 0.f, 0.f };
		SetPosAbs(mDefaultPos);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyface_axeMat", Material);
		SpriteRenderer->SetMaterial(Material);

		RenderingBlockOn();

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_kissyFaceAxe");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.4f, 0.6f));

		coll->Off();
		coll->RenderingOff();

		mAfterImageCount = 50;
	}

	CAxe::~CAxe()
	{
	}

	void CAxe::Initialize()
	{
		mTransform = GetComponent<CTransform>();
		mTransform->SetRotation({ 0.f, 0.f, -90.f });

		CLiveGameObj::Initialize();
	}

	void CAxe::update()
	{
		if (10 == mFramePass)
		{
			if (FrameCaptureCheck())
			{
				FrameCaptureOperate();
				MakeAfterImage(false);
			}
		}
		else
		{
			++mFramePass;
		}

		CLiveGameObj::update();
	}

	void CAxe::fixedUpdate()
	{


		CLiveGameObj::fixedUpdate();
	}

	void CAxe::render()
	{


		CLiveGameObj::render();
	}

	void CAxe::Spin()
	{
//		mTransform->AddRotationZ(50.f * CTimeMgr::DeltaTime());


	}

	void CAxe::Reset()
	{
		SetPosAbs(mDefaultPos);
		mTransform->SetRotation({ 0.f, 0.f, -90.f });
		SetAfterImageCount(50);
		RemoveAfterImage();

	}

}