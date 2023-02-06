#include "Material.h"

namespace dru::graphics
{
	CMaterial::CMaterial()
		:CResource(eResourceType::Material)
//		, mConstantBuffer(eCBType::Material)
	{
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
			mConstantBuffer->iData = *static_cast<int*>(_Data);
			break;
		case dru::graphics::eGPUParam::Float:
			mConstantBuffer->iData = *static_cast<float*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector2:
//			mConstantBuffer->iData = *static_cast<Vector2*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector3:
//			mConstantBuffer->iData = *static_cast<Vector3*>(_Data);
			break;
		case dru::graphics::eGPUParam::Vector4:
//			mConstantBuffer->iData = *static_cast<Vector4*>(_Data);
			break;
		case dru::graphics::eGPUParam::Matrix:
//			mConstantBuffer->iData = *static_cast<Matrix*>(_Data);
			break;
		default:
			break;
		}

	}
	void CMaterial::BindConstantBuffer()
	{
		CConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];

		pCB->Bind(&mConstantBuffer);
		pCB->SetPipeline(eShaderStage::VS);
		pCB->SetPipeline(eShaderStage::PS);

		mShader->Bind();
	}
}
