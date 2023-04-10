#pragma once
#include "Resource.h"
#include "Graphics.h"

namespace dru
{
	class CMesh : public CResource
	{
	public:
		CMesh();
		virtual ~CMesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* _Data, UINT _Count);
		bool CreateIndexBuffer(void* _Data, UINT _Count);

		void BindBuffer();

		void Render();

		void RenderInstanced(UINT _Count);


//		Microsoft::WRL::ComPtr<ID3D11Buffer> GetBuffer(graphics::eBufferStage _eStage);

	private:
		// 메시 그릴때는 정점정보 인덱스 정보만 있으면 됨
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;


		UINT			mIndexCount;

	};
}