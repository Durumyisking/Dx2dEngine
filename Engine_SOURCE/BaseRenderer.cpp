#include "BaseRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObj.h"

namespace dru
{
	CBaseRenderer::CBaseRenderer(eComponentType _Type)
		:CComponent(_Type)
		, mChanged(false)
	{
		// 디폴트 매시 지정
		std::shared_ptr<CMesh> mesh = CResources::Find<CMesh>(L"Rectmesh");

		SetMesh(mesh);
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
	void CBaseRenderer::fixedUpdate()
	{
		if (mChanged)
		{
			CTransform* transform = GetOwner()->GetComponent<CTransform>();

			Vector3 scale = transform->GetScale();
			Vector3 scaleTemp = transform->GetScale();

			scale.x = mWidthRatio;
			scale.y = mHeightRatio;

			scale *= scaleTemp;

			transform->SetScale(scale);

			mChanged = false;
		}
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

		if (nullptr == texture)
			return;

		int width = texture->GetScratchImage().GetMetadata().width;
		int height = texture->GetScratchImage().GetMetadata().height;
		int widthcount = 0;
		int heightcount = 0;

		int GCD = std::gcd(width, height);

		float fwidth = width /= GCD;
		float fheight = height /= GCD;


		while (width > 0.f)
		{
			fwidth /= 10.f;
			width /= 10.f;
			++widthcount;
		}
		while (height > 0.f)
		{
			fheight /= 10.f;
			height /= 10.f;
			++heightcount;
		}


		if (widthcount == heightcount)
		{
			fwidth *= 10.f;
			fheight *= 10.f;
		}
		else if (widthcount < heightcount)
		{
			fwidth *= 10.f;
			fheight *= 100.f;
		}
		else
		{
			fwidth *= 100.f;
			fheight *= 10.f;
		}

		mWidthRatio = fwidth;
		mHeightRatio = fheight;

	}
}
