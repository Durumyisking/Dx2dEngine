#pragma once
#include "Resource.h"
#include "Shader.h"
//#include "ConstantBuffer.h"
#include "Renderer.h"

using namespace dru::renderer;

namespace dru::graphics
{
	class CMaterial : public CResource
	{
	public:
		CMaterial();
		virtual ~CMaterial();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam _Param, void* _Data);
		void Bind();

		void SetShader(CShader* _Shader) { mShader = _Shader; }
		CShader* GetShader() const { return mShader; }

	private:
		CShader*			mShader;
		MaterialCB			mConstantBuffer;


	};

}


