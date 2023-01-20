#include "Mesh.h"
#include "Renderer.h"
#include "GraphicDevice.h"

namespace dru
{
	CMesh::CMesh()
		: mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{
	}
	CMesh::~CMesh()
	{
	}
	HRESULT CMesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool CMesh::CreateVertexBuffer(void* _Data, UINT _Count)
	{
		mVBDesc = {};
		mVBDesc.ByteWidth = sizeof(renderer::Vertex) * _Count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0; // 상수버퍼 통해서 값 변경할꺼임

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = _Data;

		if (!GetDevice()->CreateBuffer(&mVBDesc, &triangleData, mVertexBuffer.GetAddressOf()))
			return false;
		
		return true;
	}

	bool CMesh::CreateIndexBuffer(void* _Data, UINT _Count)
	{
		mIndexCount = _Count;
		mIBDesc.ByteWidth = sizeof(UINT) * _Count;
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0; 

		D3D11_SUBRESOURCE_DATA idxData = {};
		idxData.pSysMem = _Data;

		if (!GetDevice()->CreateBuffer(&mIBDesc, &idxData, mIndexBuffer.GetAddressOf()))
			return false;

		return true;
	}

	bool CMesh::CreateConstantBuffer(UINT _Count)
	{
		mCBDesc.ByteWidth = sizeof(Vector4) * _Count; // 들고있을 데이터 크기만큼 (일단은 위치 정보만)
		mCBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		mCBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		mCBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		if (!GetDevice()->CreateBuffer(&mCBDesc, nullptr, mConstantBuffer.GetAddressOf()))
			return false;

		return true;
	}

	void CMesh::BindBuffer()
	{
		UINT vertexSize = sizeof(renderer::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &vertexSize, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void CMesh::BindConstantBuffer(void* _Data)
	{
		GetDevice()->BindConstantBuffer(mConstantBuffer.Get(), _Data, sizeof(Vector4));
	}

	void CMesh::Render()
	{
		GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}

	Microsoft::WRL::ComPtr<ID3D11Buffer> CMesh::GetBuffer(graphics::eBufferStage _eStage)
	{

		switch (_eStage)
		{
		case dru::graphics::eBufferStage::VB:
			return mVertexBuffer;
			break;
		case dru::graphics::eBufferStage::IB:
			return mIndexBuffer;
			break;
		case dru::graphics::eBufferStage::CB:
			return mConstantBuffer;
			break;
		case dru::graphics::eBufferStage::End:
			break;
		default:
			break;
		}


		return nullptr;
	}

}