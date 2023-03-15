#include "StructedBuffer.h"
#include "GraphicDevice.h"

namespace dru::graphics
{
	CStructedBuffer::CStructedBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::End)
		, mSize(0)
		, mStride(0)
	{

	}

	CStructedBuffer::~CStructedBuffer()
	{
	}

	bool CStructedBuffer::Create(UINT _size, UINT _stride, eSRVType _type, void* _data)
	{
		mType = _type;
		mSize = _size;
		mStride = _stride;

		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (_data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = _data;

			if (FAILED(GetDevice()->CreateBuffer(&desc, &tSub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (FAILED(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (FAILED(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		return true;
	}

	void CStructedBuffer::Bind(void* _data, UINT _bufferCount)
	{
		if (mStride < _bufferCount)
		{
			Create(mSize, _bufferCount, eSRVType::End, _data);
		}
		else
		{
			GetDevice()->BindBuffer(buffer.Get(), _data, mSize * _bufferCount);
		}
	}

	void CStructedBuffer::SetPipeline(eShaderStage _stage, UINT _slot)
	{
		GetDevice()->SetShaderResource(_stage, _slot, mSRV.GetAddressOf());
	}
}