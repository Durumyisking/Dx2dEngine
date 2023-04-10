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
		// �޽� �׸����� �������� �ε��� ������ ������ ��
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;


		UINT			mIndexCount;

	};
}