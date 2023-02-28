#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace dru
{
	class CBaseRenderer : public CComponent
	{

	public:
		CBaseRenderer(eComponentType _Type);
		virtual ~CBaseRenderer();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		void SetMesh(std::shared_ptr <CMesh> _Mesh) { mMesh = _Mesh; }
		void SetMaterial(std::shared_ptr <CMaterial> _Material);

		std::shared_ptr<CMesh> GetMesh() { return mMesh; }
		std::shared_ptr<CMaterial> GetMaterial() { return mMaterial; }

		void ChangeSize() { mChanged = true; }

	private:
		void adjustTexture();


	private:
		std::shared_ptr <CMesh> mMesh;
		std::shared_ptr <CMaterial> mMaterial;

		float mWidthRatio;
		float mHeightRatio;

		bool mChanged;

	};

}

