#include "Renderer.h"
#include "Resources.h"
#include "Material.h"

namespace dru::renderer
{
	// vertex data
	Vertex	arrVertex[4] = {};
	CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)graphics::eSamplerType::End];

	void SetUpState()
	{
		// input Layout (���� ���� ����)
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {}; // pos, color, uv

		arrLayout[0].AlignedByteOffset = 0; // �迭�� 0����Ʈ���� �����ϰڴ�.
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // pos�� 12����Ʈ ¥���ϱ�
		arrLayout[0].InputSlot = 0; // == D3D11_INPUT_PER_VERTEX_DATA 0�������� �̰���
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 16; // ������ 12����Ʈ ��ŭ ������������ ���⼭���� �����Ұ���
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color�� 16����Ʈ ¥���ϱ�
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 32; 
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		CShader* shader = CResources::Find<CShader>(L"RectShader");

		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddr());


		// Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSampler(&samplerDesc, samplerState[(UINT)eSamplerType::Linear].GetAddressOf());
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		GetDevice()->BindSamplers((UINT)eSamplerType::Point, 1, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Linear, 1, samplerState[(UINT)eSamplerType::Linear].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Anisotropic, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());

	}

	void LoadBuffer()
	{
		CMesh* mesh = new CMesh();
		CResources::Insert<CMesh>(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(arrVertex, 4);

		std::vector<UINT> vecIdx;

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(2);

		vecIdx.push_back(0);
		vecIdx.push_back(2);
		vecIdx.push_back(3);

		mesh->CreateIndexBuffer(vecIdx.data(), vecIdx.size());

		Vector4 pos( 0.f, 0.f, 0.f, 0.f );
		// Const Buffer
	
		constantBuffers[static_cast<UINT>(eCBType::Transform)] = new CConstantBuffer(eCBType::Transform);
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Create(sizeof(TransformCB));
	
		constantBuffers[static_cast<UINT>(eCBType::Material)] = new CConstantBuffer(eCBType::Material);
		constantBuffers[static_cast<UINT>(eCBType::Material)]->Create(sizeof(MaterialCB));
		
	}

	void LoadShader()
	{
		CShader* Shader = new CShader();
		Shader->Create(graphics::eShaderStage::VS, L"VSTriangle.hlsl", "VS");
		Shader->Create(graphics::eShaderStage::PS, L"PSTriangle.hlsl", "PS");
		CResources::Insert<CShader>(L"RectShader", Shader);
	}

	void LoadMaterial()
	{
		CShader* shader = CResources::Find<CShader>(L"RectShader");

		CMaterial* Material = new CMaterial();
		Material->SetShader(shader);
		CResources::Insert<CMaterial>(L"DefaultMaterial", Material);

	}

	void Initialize()
	{
		// �߾��� 0, 0, 0�̰� ���̰� 1�� ���ﰢ��

		arrVertex[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.f); // �簢���� lefttop
		arrVertex[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB ������ǥ��
		arrVertex[0].uv = Vector2(0.f, 0.f); // uv��ǥ�� left top

		arrVertex[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.f);
		arrVertex[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		arrVertex[1].uv = Vector2(1.f, 0.f);

		arrVertex[2].pos = Vector4(0.5f, -0.5f, 0.5f, 1.f);
		arrVertex[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		arrVertex[2].uv = Vector2(1.f, 1.f);

		arrVertex[3].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.f);
		arrVertex[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		arrVertex[3].uv = Vector2(0.f, 1.f);


		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadMaterial();
	}

	void release()
	{

		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;

		}
	}
}