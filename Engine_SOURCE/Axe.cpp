#include "Axe.h"
#include "TimeMgr.h"
#include "AxeScript.h"
#include "Kissyface.h"

namespace dru
{

	CAxe::CAxe()
		: mKissyface(nullptr)
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		SetScale({ 0.15f, 0.15f, 1.f });
		Vector3 DefaultPos = { 0.36f, -0.45f, 0.f };
		SetPosAbs(DefaultPos);
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

		AddComponent<CAxeScript>(eComponentType::Script);

		mAfterImageCount = 0;
	}

	CAxe::~CAxe()
	{
	}

	void CAxe::Initialize()
	{
	
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

}