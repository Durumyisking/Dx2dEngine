#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace dru
{
	 
	class CSpriteRenderer : public CComponent
	{
	public:
		CSpriteRenderer();
		virtual ~CSpriteRenderer();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedupdate() override;
		virtual void render() override;

		void SetMesh	(std::shared_ptr <CMesh> _Mesh) { mMesh = _Mesh; }
		void SetMaterial(std::shared_ptr <CMaterial> _Material) { mMaterial = _Material; }


	private:
		std::shared_ptr <CMesh> mMesh;
		std::shared_ptr <CMaterial> mMaterial;
	};

}