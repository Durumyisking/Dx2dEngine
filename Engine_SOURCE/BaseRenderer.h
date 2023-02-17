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
		virtual void fixedupdate() override;
		virtual void render() override;

		void SetMesh(std::shared_ptr <CMesh> _Mesh) { mMesh = _Mesh; }
		void SetMaterial(std::shared_ptr <CMaterial> _Material) { mMaterial = _Material; }

		std::shared_ptr<CMesh> GetMesh() { return mMesh; }
		std::shared_ptr<CMaterial> GetMaterial() { return mMaterial; }

	private:
		std::shared_ptr <CMesh> mMesh;
		std::shared_ptr <CMaterial> mMaterial;

	};

}

