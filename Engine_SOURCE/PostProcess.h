#pragma once
#include "GameObj.h"

namespace dru
{
	class CPostProcess :
		public CGameObj
	{
	public:
		CPostProcess();
		virtual ~CPostProcess();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void Bind();
		void Clear();

	private:
		std::shared_ptr<CMaterial> mPostProcessMaterial;
		PostProcessCB mConstantBuffer;
	};

}