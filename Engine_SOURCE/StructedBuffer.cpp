#include "StructedBuffer.h"
#include "GraphicDevice.h"

namespace dru::graphics
{
	CStructedBuffer::CStructedBuffer()
		: mSRV(nullptr)
		, mUAV(nullptr)
		, mType(eSRVType::SRV)
		, mSize(0)
		, mStride(0)
		, mSRVSlot(0)
		, mUAVSlot(0)
		, mWriteBuffer(nullptr)
		, mReadBuffer(nullptr)
	{

	}

	CStructedBuffer::~CStructedBuffer()
	{
	}

	bool CStructedBuffer::Create(UINT _size, UINT _stride, eSRVType _type, void* _data, bool cpuAccess)
	{
		mType = _type;
		mSize = _size;
		mStride = _stride;

		setDiscription();
		createBuffer(_data);
		createView();

		if (cpuAccess)
		{
			createRWBuffer();
		}
		return true;
	}

	void CStructedBuffer::SetData(void* _data, UINT _stride)
	{
		if (mStride < _stride) // 그니까 내가 셋데이타 해줄껀데 이 버퍼로 넘겨줄 데이터 개수가 들어온 stride보다 크면 
		{
			Create(mSize, _stride, eSRVType::SRV, _data); // 그 크기만큼 새로 buffer 만들어버림
		}
		else
		{
			GetDevice()->SetData(mWriteBuffer.Get(), _data, mSize * _stride); // 데이터 크기 * stride(개수)만큼 데이터 세팅한다.
		}
		GetDevice()->CopyResource(buffer.Get(), mWriteBuffer.Get()); // writebuffer에 있는거 내 buffer도 들고있게함
	}

	void CStructedBuffer::GetData(void* data, UINT size) // 아직? 안쓰는중
	{
		if (!mReadBuffer)
		{
			return;
		}

		GetDevice()->CopyResource(mReadBuffer.Get(), buffer.Get()); // readbuffer에서 버퍼로 카피

		//read buffer -> systemmemory
		if (size == 0)
		{
			GetDevice()->GetData(mReadBuffer.Get(), data, mSize * mStride); // 근데 왜 setdata에요?
		}
		else
		{
			GetDevice()->GetData(mReadBuffer.Get(), data, size);
		}
	}

	void CStructedBuffer::BindSRV(eShaderStage _stage, UINT _slot)
	{
		mSRVSlot = _slot;

		GetDevice()->BindShaderResource(_stage, _slot, mSRV.GetAddressOf());
	}
	void CStructedBuffer::BindUAV(eShaderStage stage, UINT slot)
	{
		mUAVSlot = slot;
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(slot, 1, mUAV.GetAddressOf(), &i);
	}
	void CStructedBuffer::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, mSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(mUAVSlot, 1, &uav, &i);

	}
	void CStructedBuffer::setDiscription()
	{
		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (mType == eSRVType::UAV)
		{
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE
				| D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
		}
		else if (mType == eSRVType::SRV)
		{
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		}
	}
	bool CStructedBuffer::createBuffer(void* data)
	{
		if (data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = data;

			if (!(GetDevice()->CreateBuffer(&desc, &tSub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (!(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}

		return true;
	}
	bool CStructedBuffer::createView()
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		if (mType == eSRVType::UAV)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = mStride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;


			if (!(GetDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, mUAV.GetAddressOf())))
				return false;
		}

		return true;
	}
	bool CStructedBuffer::createRWBuffer()
	{
		//mWriteBuffer(nullptr)
		//mReadBuffer(nullptr)

		D3D11_BUFFER_DESC wDesc = { desc };
		wDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		wDesc.Usage = D3D11_USAGE_DYNAMIC;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!(GetDevice()->CreateBuffer(&wDesc, nullptr, mWriteBuffer.GetAddressOf())))
			return false;

		D3D11_BUFFER_DESC rDesc = { desc };
		rDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		rDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		rDesc.Usage = D3D11_USAGE_DEFAULT;
		rDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (!(GetDevice()->CreateBuffer(&rDesc, nullptr, mReadBuffer.GetAddressOf())))
			return false;

		return true;
	}
}
