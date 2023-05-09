#include "Axe.h"
#include "TimeMgr.h"

namespace dru
{

	CAxe::CAxe()
		: mTransform(nullptr)
		, mDefaultPos(Vector3::Zero)
		, mKissyfaceCenter(Vector3::Zero)
		, mAngle(10.f)
		, mInitialRadius(0.f)
		, mRadiusIncrement(0.05f)
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		SetScale({ 0.15f, 0.15f, 1.f });
		mDefaultPos = { 0.36f, -0.45f, 0.f };
		SetPosAbs(mDefaultPos);
		SetRotation({ 0.f, 0.f, 270.f });

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyface_axeMat", Material);
		SpriteRenderer->SetMaterial(Material);

		RenderingBlockOn();

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_kissyFaceAxe");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.8f, 1.2f));

		coll->Off();
		coll->RenderingOff();

		mAfterImageCount = 0;
	}

	CAxe::~CAxe()
	{
	}

	void CAxe::Initialize()
	{
		mTransform = GetComponent<CTransform>();

		CLiveGameObj::Initialize();
	}

	void CAxe::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage(false);
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
		// 공전
		mAngle += CTimeMgr::DeltaTime() * 20.f;

		float radius = 0.f;

		if (mAngle >= 20.f && 0.f == mInitialRadius)
		{
			mInitialRadius = 2.f;
			mRadiusIncrement = -mRadiusIncrement;
		}
		radius = mInitialRadius + mRadiusIncrement * mAngle;

		Vector3 Pos = GetPos();
		Pos.x = radius * cos(mAngle);
		Pos.y = radius * sin(mAngle);

		SetPos(Pos);

		// 자전
	 	mTransform->AddRotationZ(mAngle);
	}

	void CAxe::Reset()
	{
		SetPosAbs(mDefaultPos);
		SetRotation({ 0.f, 0.f, 270.f });
		mAngle = 10.f;
		mInitialRadius = 0.f;
		mRadiusIncrement = 0.05f;
	}



}