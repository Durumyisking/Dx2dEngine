#include "Renderer.h"
#include "Resources.h"

namespace dru::renderer
{
	// vertex data
	Vertex	arrVertex[4] = {};
	CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)graphics::eSamplerType::End];

	void SetUpState()
	{
		// input Layout (정점 구조 정보)
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {}; // pos, color, uv

		arrLayout[0].AlignedByteOffset = 0; // 배열의 0바이트부터 삽입하겠다.
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // pos가 12바이트 짜리니까
		arrLayout[0].InputSlot = 0; // == D3D11_INPUT_PER_VERTEX_DATA 0번슬롯은 이거임
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12; // 위에서 12바이트 만큼 삽입해줬으니 여기서부터 삽입할거임
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color가 16바이트 짜리니까
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28; 
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT; 
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		CShader* shader = CResources::Find<CShader>(L"RectShader");
		shader->CreateInputLayout(arrLayout, 3);

		// Sampler State

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	}

	void LoadBuffer()
	{
		CMesh* mesh = new CMesh();
		CResources::Insert<CMesh>(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(arrVertex, 4);

		std::vector<UINT> vecIdx = {};

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(2);
		vecIdx.push_back(0);
		vecIdx.push_back(2);
		vecIdx.push_back(3);

		mesh->CreateIndexBuffer(vecIdx.data(), vecIdx.size());

		Vector4 pos;
		pos = { 0.2f, 0.2f, 0.f, 0.0f };
		// Const Buffer
		UINT i = (UINT)eCBType::Transform;

		constantBuffers[static_cast<UINT>(eCBType::Transform)] = new CConstantBuffer();
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Create(sizeof(Vector4));
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Bind(&pos);

	}

	void LoadShader()
	{
		CShader* Shader = new CShader();
		Shader->Create(graphics::eShaderStage::VS, L"VSTriangle.hlsl", "VS");
		Shader->Create(graphics::eShaderStage::PS, L"PSTriangle.hlsl", "PS");
		CResources::Insert<CShader>(L"RectShader", Shader);
	}

	void Initialize()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형

		arrVertex[0].pos = Vector3(-0.5f, 0.5f, 0.5f); // 사각형의 lefttop
		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB 비율좌표임
		arrVertex[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		arrVertex[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		arrVertex[1].color = Vector4(0.f, 1.f, 0.f, 1.f);
		arrVertex[1].uv = Vector2(1.f, 0.f);

		arrVertex[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		arrVertex[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
		arrVertex[2].uv = Vector2(1.f, 1.f);

		arrVertex[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		arrVertex[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		arrVertex[3].uv = Vector2(0.f, 1.f);


		LoadShader();
		SetUpState();
		LoadBuffer();

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