#include "BaseRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObj.h"

namespace dru
{
	CBaseRenderer::CBaseRenderer(eComponentType _Type)
		:CComponent(_Type)
		, mbIsChanged(false)
		, mbIsAnim(false)
		, mSpriteSize(Vector2::Zero)
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
		if (mbIsChanged)
		{

			if (mWidthRatio == 0.f && mHeightRatio == 0.f)
				return;

			CTransform* transform = GetOwner()->GetComponent<CTransform>();

			Vector3 scale = transform->GetScale();
			Vector3 scaleTemp = transform->GetScale();

			scale.x = mWidthRatio;
			scale.y = mHeightRatio;

			scale *= scaleTemp;


			transform->SetScale(scale);

			mbIsChanged = false;


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

	void CBaseRenderer::SetAnimMaterial(std::shared_ptr<CMaterial> _Material, Vector2 _SpriteSize)
	{
		mMaterial = _Material;
		mbIsAnim = true;
		mSpriteSize = _SpriteSize;
		adjustTexture();
	}

	void CBaseRenderer::adjustTexture()
	{
		std::shared_ptr<CTexture> texture = GetMaterial()->GetTexture(eTextureSlot::T0);

		if (nullptr == texture)
			return;

		int width;
		int height;

		if (mbIsAnim)
		{
			width = static_cast<int>(mSpriteSize.x);
			height = static_cast<int>(mSpriteSize.y);
		}
		else
		{
			width = static_cast<int>(texture->GetScratchImage().GetMetadata().width);
			height = static_cast<int>(texture->GetScratchImage().GetMetadata().height);
		}

		if (width == 0 || height == 0)
			return;

		int widthcount = 0;
		int heightcount = 0;

		int GCD = std::gcd(width, height);

		float fwidth = static_cast<float>(width /= GCD);
		float fheight = static_cast<float>(height /= GCD);


		while (width > 0.f)
		{
			fwidth /= 10.f;
			width /= 10;
			++widthcount;
		}
		while (height > 0.f)
		{
			fheight /= 10.f;
			height /= 10;
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
