#pragma once
#include "Resource.h"
#include "Resources.h"
#include "../External/DirectXTex/include/DirectXTex.h"
#include "GraphicDevice.h"

#ifdef _DEBUG
#pragma comment(lib, "../External/DirectXTex/lib/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "../External/DirectXTex/lib/Release/DirectXTex.lib")
#endif

namespace dru::graphics
{

	class CTexture : public CResource
	{
	public:
		CTexture();
		virtual ~CTexture();

		virtual HRESULT Load(const std::wstring& path) override;

		void BindShader(eShaderStage _Stage, UINT _Slot);


	private:
		ScratchImage									mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>mShaderResourceView;
		D3D11_TEXTURE2D_DESC							mDesc;

	};

}

