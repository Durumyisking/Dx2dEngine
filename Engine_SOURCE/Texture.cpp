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
		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring fullPath = parentPath.wstring() + L"\\Resources\\" + path;
			

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
			, mShaderResourceView.GetAddressOf()
		);

		mShaderResourceView->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	void CTexture::BindShader(eShaderStage _Stage, UINT _Slot)
	{
		GetDevice()->SetShaderResource(_Stage, _Slot, mShaderResourceView.GetAddressOf());
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

