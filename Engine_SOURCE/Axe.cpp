#include "Axe.h"
#include "TimeMgr.h"

namespace dru
{

	CAxe::CAxe()
		: mTransform(nullptr)
		, mDefaultPos(Vector3::Zero)
		, mKissyfaceCenter(Vector3::Zero)
		, mAngle(0.f)
		, mInitialRadius(0.f)
		, mRadiusIncrement(0.05f)
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

		mAfterImageCount = 0;
	}

	CAxe::~CAxe()
	{
	}

	void CAxe::Initialize()
	{
		mTransform = GetComponent<CTransform>();
		mTransform->SetRotation({ 0.f, 0.f, 270.f });

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
		mAngle += CTimeMgr::DeltaTime() * 20.f;

		float radius = 0.f;

		if (mAngle >= 20.f && 0.f == mInitialRadius)
		{
			mInitialRadius = 2.f;
			mRadiusIncrement = -mRadiusIncrement;
		}
		radius = mInitialRadius + mRadiusIncrement * mAngle;


		Vector3 Pos = mDefaultPos;
		Pos.x = radius * cos(mAngle);
		Pos.y = radius * sin(mAngle);

		SetPos(Pos);
	}

	void CAxe::Reset()
	{
		SetPosAbs(mDefaultPos);
		mTransform->SetRotation({ 0.f, 0.f, 270.f });
		mAngle = 0.f;
		mInitialRadius = 0.f;
		mRadiusIncrement = 0.05f;
	}

	float CAxe::CalculateRadius(float angle, float initialRadius, float radiusIncrement, bool reverse)
	{
		float radius = initialRadius + angle * radiusIncrement;
		if (reverse)
		{
			// 현재 위치의 반지름 값 계산
			float currentRadius = initialRadius + (20.f * radiusIncrement) - (angle * radiusIncrement);
			radius = currentRadius - radiusIncrement;
		}
		return radius;
	}

}