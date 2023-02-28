#pragma once
#include "BaseRenderer.h"
#include "Mesh.h"
#include "Material.h"

namespace dru
{
	 
	class CSpriteRenderer : public CBaseRenderer
	{
	public:
		CSpriteRenderer();
		virtual ~CSpriteRenderer();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

	};

}