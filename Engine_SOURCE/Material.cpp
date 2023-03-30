#include "Material.h"

namespace dru::graphics
{
	CMaterial::CMaterial()
		:CResource(eResourceType::Material)
		, mMode(eRenderingMode::Transparent)

	{
	}
	CMaterial::CMaterial(std::wstring _TextureName, std::wstring _ShaderName)
		: CResource(eResourceType::Material) 
		, mMode(eRenderingMode::Transparent) 
	{
		mTexture[(UINT)eTextureSlot::T0] = CResources::Find<CTexture>(_TextureName);
		mShader = CResources::Find<CShader>(_ShaderName);
	}
	CMaterial::CMaterial(std::wstring _TextureName, eTextureSlot _Slot, std::wstring _ShaderName)
		: CResource(eResourceType::Material)
		, mMode(eRenderingMode::Transparent)
	{
		mTexture[(UINT)_Slot] = CResources::Find<CTexture>(_TextureName);
		mShader = CResources::Find<CShader>(_ShaderName);
	}
	CMaterial::~CMaterial()
	{
	}
	HRESULT CMaterial::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void CMaterial::SetData(eGPUParam _Param, void* _Data)
	{
		switch (_Param)
		{
		case dru::graphics::eGPUParam::Int:
			mConstantBuffer.iData1 = *static_cast<int*>(_Data);
			break;
		case dru::graphics::eGPUParam::Float:
			mConstantBuffer.fData1 = *static_cast<float*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector2:
			mConstantBuffer.xy1 = *static_cast<Vector2*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector3:
			mConstantBuffer.xyz1 = *static_cast<Vector3*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector4:
			mConstantBuffer.xyzw1 = *static_cast<Vector4*>(_Data);
			break;
		case dru::graphics::eGPUParam::Matrix:
			mConstantBuffer.matrix1 = *static_cast<Matrix*>(_Data);
			break;
		default:
			break;
		}

	}
	void CMaterial::Bind()
	{
		for (UINT i = 0; i < (UINT)eTextureSlot::End; i++)
        {
            if (mTexture[i] == nullptr)
                continue;

            mTexture[i]->BindShader(eShaderStage::VS, i);
            mTexture[i]->BindShader(eShaderStage::HS, i);
            mTexture[i]->BindShader(eShaderStage::DS, i);
            mTexture[i]->BindShader(eShaderStage::GS, i);
            mTexture[i]->BindShader(eShaderStage::PS, i);
            mTexture[i]->BindShader(eShaderStage::CS, i);
        }
		CConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];

		pCB->SetData(&mConstantBuffer);	
		pCB->Bind(eShaderStage::VS);
		pCB->Bind(eShaderStage::GS);
		pCB->Bind(eShaderStage::PS);

		mShader->Bind();
	}
	void CMaterial::Clear()
	{
		for (size_t i = 0; i < (UINT)eTextureSlot::End; i++)
		{
			if (mTexture[i] == nullptr)
				continue;

			mTexture[i]->Clear();
		}
	}
}
