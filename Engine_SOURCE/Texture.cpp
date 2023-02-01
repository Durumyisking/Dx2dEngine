#include "Texture.h"


namespace dru::graphics
{
	CTexture::CTexture()
		: CResource(eResourceType::Texture)
		, mDesc{}
		
	{
	}

	CTexture::~CTexture()
	{
	}

	HRESULT CTexture::Load(const std::wstring& path)
	{
		wchar_t szExtension[256] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 256); // 경로에서 확장자만 뽑아오는 녀석

		std::wstring extension(szExtension);

		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		std::wstring ext(szExtension);

		if (true)
		{
			// 복붙합시다~


		}

		CreateShaderResourceView(GetDevice()->GetdxDevice().Get(), mImage.GetImages(), mImage.GetImageCount(), mImage.GetMetadata(), mShaderResourceView.GetAddressOf());

		mShaderResourceView->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return E_NOTIMPL;
	}

	void CTexture::BindShader(eShaderStage _Stage, UINT _Slot)
	{
		GetDevice()->SetShaderResource(_Stage, _Slot, mShaderResourceView.GetAddressOf());
	}

}

