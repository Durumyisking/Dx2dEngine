#include "Axe.h"

namespace dru
{

	CAxe::CAxe()
	{
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		SetScale({ 0.125f, 0.125f, 1.f });
		SetPosAbs({ 0.5f, 0.f, 0.f });

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"SpriteShader");
		CResources::Insert<CMaterial>(L"kissyface_axeMat", Material);
		SpriteRenderer->SetMaterial(Material);

		//RenderingBlockOn();

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_kissyFaceAxe");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.4f, 0.6f));

		//coll->Off();
		//coll->RenderingOff();

		mAfterImageCount = 50;
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