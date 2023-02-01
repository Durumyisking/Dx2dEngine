#include "ConstantBuffer.h"
#include "GraphicDevice.h"
#include "druMath.h"

using namespace dru::math;

namespace dru::graphics
{

	CConstantBuffer::CConstantBuffer()
		: mType(eCBType::Transform)
	{
	}

	CConstantBuffer::CConstantBuffer(eCBType _Type)
		: mType(_Type)
	{
	}

	CConstantBuffer::~CConstantBuffer()
	{
	}

	bool CConstantBuffer::Create(size_t _Size)
	{
		Desc.ByteWidth = _Size; // 들고있을 데이터 크기만큼 (일단은 위치 정보만)
		Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		Desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		if (!GetDevice()->CreateBuffer(&Desc, nullptr, Buffer.GetAddressOf()))
			return false;

		return true;
	}

	void CConstantBuffer::Bind(void* _Data)
	{
		GetDevice()->BindConstantBuffer(Buffer.Get(), _Data, Desc.ByteWidth);
	}

	void CConstantBuffer::SetPipeline(eShaderStage _Stage)
	{
		GetDevice()->SetConstantBuffer(_Stage, mType, Buffer.Get());
	}

}
