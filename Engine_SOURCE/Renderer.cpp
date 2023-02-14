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
		
		#pragma region InputLayout
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {}; // pos, color, uv

		arrLayout[0].AlignedByteOffset = 0; // 배열의 0바이트부터 삽입하겠다.
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // pos가 12바이트 짜리니까
		arrLayout[0].InputSlot = 0; // == D3D11_INPUT_PER_VERTEX_DATA 0번슬롯은 이거임
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 16; // 위에서 12바이트 만큼 삽입해줬으니 여기서부터 삽입할거임
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // color가 16바이트 짜리니까
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

		std::shared_ptr<CShader> Meshshader = CResources::Find<CShader>(L"MeshShader");

		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Meshshader->GetVSBlobBufferPointer()
			, Meshshader->GetVSBlobBufferSize()
			, Meshshader->GetInputLayoutAddr());


		std::shared_ptr<CShader> Spriteshader = CResources::Find<CShader>(L"SpriteShader");

		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Spriteshader->GetVSBlobBufferPointer()
			, Spriteshader->GetVSBlobBufferSize()
			, Spriteshader->GetInputLayoutAddr());
#pragma endregion

		#pragma region SamplerState
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
#pragma endregion

	}


	void LoadBuffer()
	{
		std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
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
		std::shared_ptr<CShader> MeshShader = std::make_shared<CShader>();
		MeshShader->Create(graphics::eShaderStage::VS, L"VSTriangle.hlsl", "main");
		MeshShader->Create(graphics::eShaderStage::PS, L"PSTriangle.hlsl", "main");
		CResources::Insert<CShader>(L"MeshShader", MeshShader);


		std::shared_ptr<CShader> SpriteShader = std::make_shared<CShader>();
		SpriteShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		SpriteShader->Create(graphics::eShaderStage::PS, L"SpritePS.hlsl", "main");
		CResources::Insert<CShader>(L"SpriteShader", SpriteShader);

	}

	void LoadMaterial()
	{
		std::shared_ptr<CTexture> Meshtexture = CResources::Load<CTexture>(L"Default", L"default.png");


		std::shared_ptr<CShader> MeshShader = CResources::Find<CShader>(L"MeshShader");
		std::shared_ptr<CMaterial> MeshMaterial = std::make_shared<CMaterial>();
		MeshMaterial->SetShader(MeshShader);
		MeshMaterial->SetTexture(Meshtexture);
		CResources::Insert<CMaterial>(L"MeshMaterial", MeshMaterial);


		std::shared_ptr<CTexture> Spritetexture = CResources::Find<CTexture>(L"Default");

		std::shared_ptr<CShader> SpriteShader = CResources::Find<CShader>(L"SpriteShader");
		std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>();
		SpriteMaterial->SetShader(SpriteShader);
		SpriteMaterial->SetTexture(Spritetexture);
		CResources::Insert<CMaterial>(L"SpriteMaterial", SpriteMaterial);

	}

	void Initialize()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형

		arrVertex[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.f); // 사각형의 lefttop
//		arrVertex[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB 비율좌표임
		arrVertex[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		arrVertex[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.f);
//		arrVertex[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		arrVertex[1].uv = Vector2(1.f, 0.f);

		arrVertex[2].pos = Vector4(0.5f, -0.5f, 0.5f, 1.f);
//		arrVertex[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		arrVertex[2].uv = Vector2(1.f, 1.f);

		arrVertex[3].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.f);
//		arrVertex[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
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