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
		bool Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture);
		virtual HRESULT Load(const std::wstring& path) override;

		void BindShaderResource(eShaderStage _Stage, UINT _Slot);
		void BindUnorderedAccessview(UINT _Slot);
		void ClearUnorderedAccessview(UINT _Slot);

		void Clear();

		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture) { mTexture = _texture; }
		void MakeCropTexture(UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox);
		ScratchImage& GetScratchImage() { return mImage; }

		UINT GetHeight() { return mDesc.Height; }
		UINT GetWidth() { return mDesc.Width; }



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

