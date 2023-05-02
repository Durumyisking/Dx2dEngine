#pragma once
#include "BaseRenderer.h"

namespace dru
{
    class CPostProcessRenderer :
        public CBaseRenderer
    {
	public:
		CPostProcessRenderer();
		virtual ~CPostProcessRenderer();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		void SetPostProcessOwner(CPostProcess* _PostProcess);

	private:
		CPostProcess* mPostProcess;
    };
}
