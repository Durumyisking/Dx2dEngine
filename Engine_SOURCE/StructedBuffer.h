#pragma once
#include "Entity.h"
#include "Graphics.h"

namespace dru::graphics
{
	class CStructedBuffer : public GpuBuffer // 구조체 상속 클래스?
	{
	public:
		CStructedBuffer();
		~CStructedBuffer();

		bool Create(UINT _size, UINT _stride, graphics::eSRVType _type, void* _data, bool cpuAccess = false);
		void SetData(void* _data, UINT _stride);
		void GetData(void* data, UINT size = 0); 
		void BindSRV(graphics::eShaderStage _stage, UINT _slot);
		void BindUAV(eShaderStage stage, UINT slot);

		void Clear();

		UINT GetSize() { return mSize; } // 버퍼의 크기 (넘겨줄 데이터의? 크기)
		UINT GetStride() { return mStride; } // 버퍼의 개수

	private:
		void setDiscription();
		bool createBuffer(void* data);
		bool createView();
		bool createRWBuffer();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer; private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		graphics::eSRVType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVSlot;

	};
}