#pragma once
#include "GameObj.h"


namespace dru
{
	class CPostProcessRenderer;
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

		virtual void Bind();
		void Clear();

		void SetMaterial(std::wstring _Key);

	protected:
		std::shared_ptr<CMaterial> mPostProcessMaterial;
		PostProcessCB mConstantBuffer;
		CPostProcessRenderer* mRenderer;
	};

}