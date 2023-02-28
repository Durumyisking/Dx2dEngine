#pragma once
#include "BaseRenderer.h"
#include "Mesh.h"
#include "Material.h"

namespace dru
{
	class CMeshRenderer : public CBaseRenderer
	{
	public:
		CMeshRenderer();
		virtual ~CMeshRenderer();

		virtual void Initialize() override ;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

	};
}