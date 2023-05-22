#include "Material.h"

namespace dru::graphics
{
	CMaterial::CMaterial()
		:CResource(eResourceType::Material)
		, mMode(eRenderingMode::Transparent)
		, mConstantBuffer{}

	{
	}
	CMaterial::CMaterial(std::wstring _TextureName, std::wstring _ShaderName)
		: CResource(eResourceType::Material) 
		, mMode(eRenderingMode::Transparent) 
	{
		mTexture[(UINT)eTextureSlot::T0] = CResources::Find<CTexture>(_TextureName);
		mShader = CResources::Find<CShader>(_ShaderName);
		mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
	}
	CMaterial::CMaterial(std::wstring _TextureName, eTextureSlot _Slot, std::wstring _ShaderName)
		: CResource(eResourceType::Material)
		, mMode(eRenderingMode::Transparent)
	{
		mTexture[(UINT)_Slot] = CResources::Find<CTexture>(_TextureName);
		mShader = CResources::Find<CShader>(_ShaderName);
		mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
		mConstantBuffer.xyzw2 = Vector4{ 0.f, 0.f, 0.f, 0.f };
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
		case graphics::eGPUParam::Int_1:
			mConstantBuffer.iData1 = *static_cast<int*>(_Data);
			break;
		case graphics::eGPUParam::Int_2:
			mConstantBuffer.iData2 = *static_cast<int*>(_Data);
			break;
		case graphics::eGPUParam::Int_3:
			mConstantBuffer.iData3 = *static_cast<int*>(_Data);
			break;
		case graphics::eGPUParam::Int_4:
			mConstantBuffer.iData4 = *static_cast<int*>(_Data);
			break;
		case graphics::eGPUParam::Float_1:
			mConstantBuffer.fData1 = *static_cast<float*>(_Data);
			break;
		case graphics::eGPUParam::Float_2:
			mConstantBuffer.fData2 = *static_cast<float*>(_Data);
			break;
		case graphics::eGPUParam::Float_3:
			mConstantBuffer.fData3 = *static_cast<float*>(_Data);
			break;
		case graphics::eGPUParam::Float_4:
			mConstantBuffer.fData4 = *static_cast<float*>(_Data);
			break;
		case graphics::eGPUParam::Vector2_1:
			mConstantBuffer.xy1 = *static_cast<Vector2*>(_Data);
			break;
		case graphics::eGPUParam::Vector2_2:
			mConstantBuffer.xy2 = *static_cast<Vector2*>(_Data);
			break;
		case graphics::eGPUParam::Vector2_3:
			mConstantBuffer.xy3 = *static_cast<Vector2*>(_Data);
			break;
		case graphics::eGPUParam::Vector2_4:
			mConstantBuffer.xy4 = *static_cast<Vector2*>(_Data);
			break;
		case graphics::eGPUParam::Vector3_1:
			mConstantBuffer.xyz1 = *static_cast<Vector3*>(_Data);
			break;
		case graphics::eGPUParam::Vector3_2:
			mConstantBuffer.xyz2 = *static_cast<Vector3*>(_Data);
			break;
		case graphics::eGPUParam::Vector3_3:
			mConstantBuffer.xyz3 = *static_cast<Vector3*>(_Data);
			break;
		case graphics::eGPUParam::Vector3_4:
			mConstantBuffer.xyz4 = *static_cast<Vector3*>(_Data);
			break;
		case graphics::eGPUParam::Vector4_1:
			mConstantBuffer.xyzw1 = *static_cast<Vector4*>(_Data);
			break;
		case graphics::eGPUParam::Vector4_2:
			mConstantBuffer.xyzw2 = *static_cast<Vector4*>(_Data);
			break;
		case graphics::eGPUParam::Vector4_3:
			mConstantBuffer.xyzw3 = *static_cast<Vector4*>(_Data);
			break;
		case graphics::eGPUParam::Vector4_4:
			mConstantBuffer.xyzw4 = *static_cast<Vector4*>(_Data);
			break;
		case graphics::eGPUParam::Matrix_1:
			mConstantBuffer.matrix1 = *static_cast<Matrix*>(_Data);
			break;
		case graphics::eGPUParam::Matrix_2:
			mConstantBuffer.matrix2 = *static_cast<Matrix*>(_Data);
			break;
		case graphics::eGPUParam::Matrix_3:
			mConstantBuffer.matrix3 = *static_cast<Matrix*>(_Data);
			break;
		case graphics::eGPUParam::Matrix_4:
			mConstantBuffer.matrix4 = *static_cast<Matrix*>(_Data);
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

            mTexture[i]->BindShaderResource(eShaderStage::VS, i);
            mTexture[i]->BindShaderResource(eShaderStage::HS, i);
            mTexture[i]->BindShaderResource(eShaderStage::DS, i);
            mTexture[i]->BindShaderResource(eShaderStage::GS, i);
            mTexture[i]->BindShaderResource(eShaderStage::PS, i);
            mTexture[i]->BindShaderResource(eShaderStage::CS, i);
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

		CConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
		pCB->Clear();

	}
	void CMaterial::SetShaderByKey(std::wstring _Key)
	{
		std::shared_ptr<CShader> shader = CResources::Find<CShader>(_Key);
		mShader = shader;
	}
}
