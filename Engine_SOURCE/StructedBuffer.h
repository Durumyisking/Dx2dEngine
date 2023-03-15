#pragma once
#include "Entity.h"
#include "Graphics.h"

namespace dru::graphics
{
	class CStructedBuffer : public GpuBuffer
	{
	public:
		CStructedBuffer();
		~CStructedBuffer();

		bool Create(UINT _size, UINT _stride, graphics::eSRVType _type, void* _data);
		void Bind(void* _data, UINT _bufferCount);
		void SetPipeline(graphics::eShaderStage _stage, UINT _slot);

		UINT GetSize() { return mSize; }
		UINT GetStrideSize() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		graphics::eSRVType mType;

		UINT mSize;
		UINT mStride;

	};
}

