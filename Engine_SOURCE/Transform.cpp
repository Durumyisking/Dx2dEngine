#include "Transform.h"

namespace dru
{
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mPosition{}
		, mRotation{}
		, mScale{}
	{
	}

	CTransform::~CTransform()
	{
	}

	void CTransform::Initialize()
	{
	}

	void CTransform::update()
	{
	}

	void CTransform::fixedupdate()
	{
		SetConstantBuffer();
	}

	void CTransform::render()
	{

	}

	void CTransform::SetConstantBuffer()
	{
		// 상수버퍼 가져와 해당 상수버퍼에 값 세팅

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		
		Vector4 pos(mPosition.x, mPosition.y, mPosition.z, 0.0f);
		cb->Bind(&pos);
		cb->SetPipeline(eShaderStage::VS);
			
	}


}