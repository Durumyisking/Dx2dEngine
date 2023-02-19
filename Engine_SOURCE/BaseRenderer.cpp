#include "BaseRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObj.h"

namespace dru
{
	CBaseRenderer::CBaseRenderer(eComponentType _Type)
		:CComponent(_Type)
	{
	}
	CBaseRenderer::~CBaseRenderer()
	{
	}
	void CBaseRenderer::Initialize()
	{
	}
	void CBaseRenderer::update()
	{
	}
	void CBaseRenderer::fixedupdate()
	{
	}
	void CBaseRenderer::render()
	{
	}
	void CBaseRenderer::SetMaterial(std::shared_ptr<CMaterial> _Material)
	{
		mMaterial = _Material;

		adjustTexture();
	}
	void CBaseRenderer::adjustTexture()
	{
		std::shared_ptr<CTexture> texture = GetMaterial()->GetTexture();

		int width = texture->GetScratchImage().GetMetadata().width;
		int height = texture->GetScratchImage().GetMetadata().height;

		int GCD = std::gcd(width, height);

		float fwidth = width /= GCD;
		float fheight = height /= GCD;

	
		CTransform* transform = GetOwner()->GetComponent<CTransform>();

		Vector3 scale = transform->GetScale();
		Vector3 scaleTemp = transform->GetScale();

		if (fwidth >= 0.f && fwidth < 10)
			fwidth = fwidth / 10;
		else if (fwidth >= 10.f && fwidth < 100)
			fwidth = fwidth / 10;
		else if (fwidth >= 100.f && fwidth < 1000)
			fwidth = fwidth / 10.f / 10;
		else if (fwidth >= 1000)
			fwidth = fwidth / 10.f / 10.f / 10;

		if (fheight >= 0.f && fheight < 10)
			fheight = fheight / 10;
		else if (fheight >= 10.f && fheight < 100)
			fheight = fheight / 10;
		else if (fheight >= 100.f && fheight < 1000)
			fheight = fheight / 10.f / 10;
		else if (fheight >= 1000)
			fheight = fheight / 10.f / 10.f / 10;


		scale.x = fwidth;
		scale.y = fheight;

		scale *= scaleTemp;

		transform->SetScale(scale);

	}
}
