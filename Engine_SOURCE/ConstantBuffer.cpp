#include "ConstantBuffer.h"
#include "GraphicDevice.h"
#include "druMath.h"

using namespace dru::math;

namespace dru::graphics
{

	CConstantBuffer::CConstantBuffer()
		: mType(eCBType::End)
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
		desc.ByteWidth = _Size; // 들고있을 데이터 크기만큼 (일단은 위치 정보만)
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		if (!GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()))
			return false;

		return true;
	}

	void CConstantBuffer::Bind(void* _Data)
	{
		GetDevice()->BindBuffer(buffer.Get(), _Data, desc.ByteWidth);
	}

	void CConstantBuffer::SetPipeline(eShaderStage _Stage)
	{
		GetDevice()->SetConstantBuffer(_Stage, mType, buffer.Get());
	}

}
