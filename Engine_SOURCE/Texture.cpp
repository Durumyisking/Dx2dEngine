#include "Texture.h"


namespace dru::graphics
{
	CTexture::CTexture()
		: CResource(eResourceType::Texture)
		, mDesc{}
		, mTexture(nullptr)
		
	{
	}

	CTexture::~CTexture()
	{
	}

	void CTexture::Clear(UINT startSlot)
	{
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->SetShaderResource(eShaderStage::VS, startSlot, &srv);
		GetDevice()->SetShaderResource(eShaderStage::DS, startSlot, &srv);
		GetDevice()->SetShaderResource(eShaderStage::GS, startSlot, &srv);
		GetDevice()->SetShaderResource(eShaderStage::HS, startSlot, &srv);
		GetDevice()->SetShaderResource(eShaderStage::CS, startSlot, &srv);
		GetDevice()->SetShaderResource(eShaderStage::PS, startSlot, &srv);
	}

	bool CTexture::Create(UINT _width, UINT _height, DXGI_FORMAT _format, UINT _bindflag)
	{
		mDesc.BindFlags = _bindflag;
		mDesc.Usage = D3D11_USAGE_DEFAULT;
		mDesc.CPUAccessFlags = 0;
		mDesc.Format = _format;
		mDesc.Width = _width;
		mDesc.Height = _height;
		mDesc.ArraySize = 1;

		mDesc.SampleDesc.Count = 1;
		mDesc.SampleDesc.Quality = 1;

		mDesc.MipLevels = 1;
		mDesc.MiscFlags = 0;

		if (!GetDevice()->CreateTexture(&mDesc, mTexture.GetAddressOf()))
			return false;

		if (_bindflag & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()));
				return false;
		}
		if (_bindflag & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVdesc = {};
			tSRVdesc.Format = _format;
			tSRVdesc.Texture2D.MipLevels = 1;
			tSRVdesc.Texture2D.MostDetailedMip = 0;
			tSRVdesc.ViewDimension = D3D11_SRV_DIMENSION::D3D_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), nullptr, mSRV.GetAddressOf()));
				return false;
		}
		if (_bindflag & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()));
				return false;
		}
		if (_bindflag & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVdesc = {};
			tUAVdesc.Format = _format;
			tUAVdesc.Texture2D.MipSlice = 0;
			tUAVdesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2DARRAY;

			if (!GetDevice()->CreateUnorderedAccessView(mTexture.Get(), nullptr, mUAV.GetAddressOf()));
				return false;
		}

		return true;
	}

	HRESULT CTexture::Load(const std::wstring& path)
	{
		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring fullPath = parentPath.wstring() + L"\\..\\Resources\\" + path;
			

		wchar_t szExtension[256] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 256); // 경로에서 확장자만 뽑아오는 녀석

		std::wstring extension(szExtension);

		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(fullPath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(fullPath.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(fullPath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView(
			GetDevice()->GetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	void CTexture::BindShader(eShaderStage _Stage, UINT _Slot)
	{
		GetDevice()->SetShaderResource(_Stage, _Slot, mSRV.GetAddressOf());
	}

	void CTexture::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->SetShaderResource(eShaderStage::VS, 0, &srv);
		GetDevice()->SetShaderResource(eShaderStage::DS, 0, &srv);
		GetDevice()->SetShaderResource(eShaderStage::GS, 0, &srv);
		GetDevice()->SetShaderResource(eShaderStage::HS, 0, &srv);
		GetDevice()->SetShaderResource(eShaderStage::CS, 0, &srv);
		GetDevice()->SetShaderResource(eShaderStage::PS, 0, &srv);
	}

}

