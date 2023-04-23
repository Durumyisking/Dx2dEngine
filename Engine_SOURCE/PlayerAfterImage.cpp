#include "PlayerAfterImage.h"
#include "AfterImageRenderer.h"

namespace dru
{
	CPlayerAfterImage::CPlayerAfterImage()
		: mPlayerFrameCaptures{}
		, mOwner(nullptr)
	{
		CAfterImageRenderer* Renderer = this->AddComponent<CAfterImageRenderer>(eComponentType::AfterImageRenderer);
		std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
		CResources::Insert<CMaterial>(L"PlayerMat", Material);
		Renderer->SetMaterial(Material);
	}

	CPlayerAfterImage::~CPlayerAfterImage()
	{
	}

	void CPlayerAfterImage::Initialize()
	{
		CGameObj::Initialize();
	}

	void CPlayerAfterImage::update()
	{
		CGameObj::update();
	}

	void CPlayerAfterImage::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}

	void CPlayerAfterImage::render()
	{
		CGameObj::render();
	}

}