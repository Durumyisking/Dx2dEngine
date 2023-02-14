#pragma once
#include "Resource.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

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
		void Clear();

		void SetShader(std::shared_ptr<CShader>	 _Shader) { mShader = _Shader; }
		std::shared_ptr<CShader> GetShader() const { return mShader; }

		void SetTexture(std::shared_ptr<CTexture> _Texture) { mTexture = _Texture; }
		std::shared_ptr<CTexture> GetTexture() const { return mTexture; }


	private:
		std::shared_ptr<CShader>			mShader;
		std::shared_ptr<CTexture>			mTexture;
		MaterialCB			mConstantBuffer;


	};

}


