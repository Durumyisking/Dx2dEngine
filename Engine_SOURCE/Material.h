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
		CMaterial(std::wstring _TextureName, std::wstring _ShaderName);
		CMaterial(std::wstring _TextureName, eTextureSlot _Slot, std::wstring _ShaderName);
		virtual ~CMaterial();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam _Param, void* _Data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<CShader>	 _Shader) { mShader = _Shader; }
		void SetShaderByKey(std::wstring _Key);
		std::shared_ptr<CShader> GetShader() const { return mShader; }

		void SetTexture(std::shared_ptr<CTexture> _Texture) { mTexture[(UINT)eTextureSlot::T0] = _Texture; }
		void SetTexture(eTextureSlot slot, std::shared_ptr<CTexture> _Texture) { mTexture[(UINT)slot] = _Texture; }
		std::shared_ptr<CTexture> GetTexture() const { return mTexture[(UINT)eTextureSlot::T0]; }
		std::shared_ptr<CTexture> GetTexture(eTextureSlot slot) const { return mTexture[(UINT)slot]; }

		eRenderingMode GetRenderingMode() const { return mMode; }
		void SetRenderingMode(eRenderingMode _Mode) { mMode = _Mode; }

	private:
		std::shared_ptr<CShader>			mShader;
		std::shared_ptr<CTexture>			mTexture[(UINT)eTextureSlot::End];
		MaterialCB							mConstantBuffer;
		eRenderingMode						mMode;


	};

}


