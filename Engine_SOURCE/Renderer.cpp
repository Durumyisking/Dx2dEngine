#include "Renderer.h"
#include "Resources.h"

namespace dru::renderer
{
	// vertex data
	Vertex				arrVertex[4] = {};



	Microsoft::WRL::ComPtr <ID3DBlob>			errorBlob = nullptr; // dx 내부에서 생긴 에러를 알려주는 친구
		
	// idx buffer
	Microsoft::WRL::ComPtr <ID3D11Buffer> triangleConstantBuffer = nullptr;


	void SetUpState()
	{
		// input Layout (정점 구조 정보)
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {}; // 우리가 vertex의 멤버로 pos, color 들고있으니까 2개만 만들자

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

		GetDevice()->CreateInputLayout(arrLayout, 2
			, triangleVSBlob->GetBufferPointer()
			, triangleVSBlob->GetBufferSize()
			, &triangleLayout);
	}

	void LoadBuffer()
	{
		Mesh = new CMesh();
		CResources::Insert<CMesh>(L"RectMesh", Mesh);

		Mesh->CreateVertexBuffer(arrVertex, 4);

		std::vector<UINT> vecIdx = {};

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(3);
		vecIdx.push_back(0);
		vecIdx.push_back(3);
		vecIdx.push_back(2);

		Mesh->CreateIndexBuffer(&vecIdx, 6);

		// Const Buffer
		D3D11_BUFFER_DESC constDesc = {};
		constDesc.ByteWidth = sizeof(Vector4); // 들고있을 데이터 크기만큼 (일단은 위치 정보만)
		constDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&constDesc, nullptr, triangleConstantBuffer.GetAddressOf());

		Vector4 pos(0.2f, 0.2f, 0.f, 0.f);
		GetDevice()->BindConstantBuffer(triangleConstantBuffer.Get(), &pos, sizeof(Vector4));
	}

	void LoadShader()
	{
		GetDevice()->CreateShader();
	}

	void init()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형

		arrVertex[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		arrVertex[0].color = Vector4(1.f, 0.f, 0.f, 1.f); // RGB 비율좌표임

		arrVertex[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		arrVertex[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		arrVertex[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		arrVertex[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		arrVertex[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		arrVertex[3].color = Vector4(0.f, 0.f, 0.f, 1.f);


		LoadShader();
		SetUpState();
		LoadBuffer();

	}

	void release()
	{
		delete Mesh;

	}
}