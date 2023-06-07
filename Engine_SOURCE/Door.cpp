#include "Door.h"
#include "DoorScript.h"

namespace dru
{
	CDoor::CDoor()
	{
		SetName(L"Door");
		SetLayerType(eLayerType::Objects);
		SetScale(Vector3(1.55f, 1.55f, 1.f));
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);

		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"door", L"SpriteShader");
		CResources::Insert<CMaterial>(L"DoorMat", Material);
		SpriteRenderer->SetMaterial(Material);

		Vector2 Offset = { 24.f, 0.f };
		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"DoorClosed", Material->GetTexture(), { 0.f, 0.f },		{ 80.f, 64.f },	Offset, 1, { 90.f, 64.f }, 0.1f);
		mAnimator->Create(L"DoorOpen", Material->GetTexture(), { 0.f, 0.f },		{ 80.f, 64.f },	Offset, 20,{ 90.f, 64.f }, 0.1f);
		mAnimator->Create(L"DoorOpened", Material->GetTexture(), { 1520.f, 0.f },	{ 80.f, 64.f },	Offset, 1, { 90.f, 64.f }, 0.1f);

		mAnimator->Play(L"DoorClosed");

		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_door");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.1f, 1.f));


		AddComponent<CDoorScript>(eComponentType::Script)->Initialize();

	}

	CDoor::~CDoor()
	{
	}

	void CDoor::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CDoor::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}
		CLiveGameObj::update();
	}

	void CDoor::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CDoor::render()
	{
		CLiveGameObj::render();
	}

	void CDoor::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

	bool CDoor::IsOpen() 
	{
		return GetScript<CDoorScript>()->IsOpen();
	}

}