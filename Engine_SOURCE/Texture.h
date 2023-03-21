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

		static void Clear(UINT startSlot);

		bool Create(UINT _width, UINT _height, DXGI_FORMAT _format, UINT _bindflag);
		virtual HRESULT Load(const std::wstring& path) override;

		void BindShader(eShaderStage _Stage, UINT _Slot);
		void Clear();


		ScratchImage& GetScratchImage() { return mImage; }

		size_t GetHeight() { return mImage.GetMetadata().height; }
		size_t GetWidth() { return mImage.GetMetadata().width; }

		Microsoft::WRL::ComPtr<ID3D11Texture2D>	GetTexture()		{ return mTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV()		{ return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV()	{ return mSRV; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV()		{ return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV()	{ return mUAV; }

	private:
		ScratchImage										mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDSV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRTV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	mUAV;
		D3D11_TEXTURE2D_DESC								mDesc;

	};

}

