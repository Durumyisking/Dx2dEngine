#include "Renderer.h"
#include "Resources.h"
#include "Material.h"
#include "SceneMgr.h"
#include "Scene.h"

namespace dru::renderer
{
	// vertex data
	Vertex	RectVertexes[4] = {};
	std::vector<Vertex>	CircleVertexes;

	CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)graphics::eSamplerType::End];
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState[(UINT)graphics::eRasterizerType::End];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState[(UINT)graphics::eDepthStencilType::End];
	Microsoft::WRL::ComPtr<ID3D11BlendState> BlendState[(UINT)graphics::eBlendStateType::End];

	std::vector<CCamera*> Cameras[static_cast<UINT>(CSceneMgr::eSceneType::End)];

	void LoadMesh()
	{

		#pragma region RectMesh

		RectVertexes[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.f); // 사각형의 lefttop
		RectVertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB 비율좌표임
		RectVertexes[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		RectVertexes[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.f);
		RectVertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		RectVertexes[1].uv = Vector2(1.f, 0.f);

		RectVertexes[2].pos = Vector4(0.5f, -0.5f, 0.5f, 1.f);
		RectVertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		RectVertexes[2].uv = Vector2(1.f, 1.f);

		RectVertexes[3].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.f);
		RectVertexes[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		RectVertexes[3].uv = Vector2(0.f, 1.f);

		std::shared_ptr<CMesh> Rectmesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Rectmesh", Rectmesh);

		std::vector<UINT> vecIdx;

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(2);

		vecIdx.push_back(0);
		vecIdx.push_back(2);
		vecIdx.push_back(3);

		Rectmesh->CreateVertexBuffer(RectVertexes, 4);
		Rectmesh->CreateIndexBuffer(vecIdx.data(), vecIdx.size());

		#pragma endregion

		#pragma region CircleMesh

		Vertex center = {};

		center.pos = Vector4(0.f, 0.f, 0.f, 1.f);
		center.color= Vector4(0.f, 1.f, 0.f, 1.f);
		center.uv = Vector2::Zero;

		CircleVertexes.push_back(center);

		int slice = 40;
		float radius = 0.5f;
		float theta = XM_2PI / (float)slice;

		for (int i = 0; i < slice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4(theta * cosf(theta * (float)i)
							, theta * sinf(theta * (float)i)
							, 0.f, 0.f
			);
			vtx.color = center.color;

			CircleVertexes.push_back(vtx);
		}

		vecIdx.clear();

		for (int i = 1; i <= slice; i++) // center 정점 제외
		{
			vecIdx.push_back(i);
		}
		vecIdx.push_back(1);

		std::shared_ptr<CMesh> Circlemesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Circlemesh", Circlemesh);

		Circlemesh->CreateVertexBuffer(CircleVertexes.data(), vecIdx.size());
		Circlemesh->CreateIndexBuffer(vecIdx.data(), vecIdx.size());


		#pragma endregion

	}


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


		std::shared_ptr<CShader> UIshader = CResources::Find<CShader>(L"UIShader");
		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, UIshader->GetVSBlobBufferPointer()
			, UIshader->GetVSBlobBufferSize()
			, UIshader->GetInputLayoutAddr());

		std::shared_ptr<CShader> Gridshader = CResources::Find<CShader>(L"GridShader");
		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Gridshader->GetVSBlobBufferPointer()
			, Gridshader->GetVSBlobBufferSize()
			, Gridshader->GetInputLayoutAddr());

		std::shared_ptr<CShader> Fadeshader = CResources::Find<CShader>(L"FadeShader");
		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Fadeshader->GetVSBlobBufferPointer()
			, Fadeshader->GetVSBlobBufferSize()
			, Fadeshader->GetInputLayoutAddr());

		std::shared_ptr<CShader> Colorshader = CResources::Find<CShader>(L"ColorShader");
		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Colorshader->GetVSBlobBufferPointer()
			, Colorshader->GetVSBlobBufferSize()
			, Colorshader->GetInputLayoutAddr());

		std::shared_ptr<CShader> Debugshader = CResources::Find<CShader>(L"DebugShader");
		graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Debugshader->GetVSBlobBufferPointer()
			, Debugshader->GetVSBlobBufferSize()
			, Debugshader->GetInputLayoutAddr());



#pragma endregion

		#pragma region SamplerState
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Linear].GetAddressOf());
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		GetDevice()->BindSamplers((UINT)eSamplerType::Point, 1, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Linear, 1, samplerState[(UINT)eSamplerType::Linear].GetAddressOf());
		GetDevice()->BindSamplers((UINT)eSamplerType::Anisotropic, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

		#pragma region RasterizerState
		D3D11_RASTERIZER_DESC  reDesc = {};

		reDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		reDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&reDesc, rasterizerState[(UINT)graphics::eRasterizerType::SolidBack].GetAddressOf());

		reDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		reDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&reDesc, rasterizerState[(UINT)graphics::eRasterizerType::SolidFront].GetAddressOf());

		reDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		reDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&reDesc, rasterizerState[(UINT)graphics::eRasterizerType::SolidNone].GetAddressOf());

		reDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		reDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&reDesc, rasterizerState[(UINT)graphics::eRasterizerType::WireframeNone].GetAddressOf());

		#pragma endregion

		#pragma region DepthStencilState

		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;	
		GetDevice()->CreateDepthStencilState(&dsDesc, DepthStencilState[(UINT)graphics::eDepthStencilType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, DepthStencilState[(UINT)graphics::eDepthStencilType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, DepthStencilState[(UINT)graphics::eDepthStencilType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, DepthStencilState[(UINT)graphics::eDepthStencilType::None].GetAddressOf());

		#pragma endregion

		#pragma region BlendState

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		GetDevice()->CreateBlendState(&bsDesc, BlendState[(UINT)graphics::eBlendStateType::AlphaBlend].GetAddressOf());	

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		GetDevice()->CreateBlendState(&bsDesc, BlendState[(UINT)graphics::eBlendStateType::OneOne].GetAddressOf());


		#pragma endregion


	}


	void LoadBuffer()
	{
		// Const Buffer	
		constantBuffers[static_cast<UINT>(eCBType::Transform)] = new CConstantBuffer(eCBType::Transform);
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Create(sizeof(TransformCB));
	
		constantBuffers[static_cast<UINT>(eCBType::Material)] = new CConstantBuffer(eCBType::Material);
		constantBuffers[static_cast<UINT>(eCBType::Material)]->Create(sizeof(MaterialCB));

		constantBuffers[static_cast<UINT>(eCBType::Grid)] = new CConstantBuffer(eCBType::Grid);
		constantBuffers[static_cast<UINT>(eCBType::Grid)]->Create(sizeof(GridCB));

		constantBuffers[static_cast<UINT>(eCBType::Fade)] = new CConstantBuffer(eCBType::Fade);
		constantBuffers[static_cast<UINT>(eCBType::Fade)]->Create(sizeof(FadeCB));

		constantBuffers[static_cast<UINT>(eCBType::Color)] = new CConstantBuffer(eCBType::Color);
		constantBuffers[static_cast<UINT>(eCBType::Color)]->Create(sizeof(ColorCB));

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


		std::shared_ptr<CShader> UIShader = std::make_shared<CShader>();
		UIShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		UIShader->Create(graphics::eShaderStage::PS, L"UIPS.hlsl", "main");
		CResources::Insert<CShader>(L"UIShader", UIShader);


		std::shared_ptr<CShader> GridShader = std::make_shared<CShader>();
		GridShader->Create(graphics::eShaderStage::VS, L"GridVS.hlsl", "main");
		GridShader->Create(graphics::eShaderStage::PS, L"GridPS.hlsl", "main");
		GridShader->SetRSState(eRasterizerType::SolidNone); // 항상 보임
		GridShader->SetDSState(eDepthStencilType::NoWrite);
		GridShader->SetBSState(eBlendStateType::AlphaBlend);
		CResources::Insert<CShader>(L"GridShader", GridShader);

		std::shared_ptr<CShader> FadeShader = std::make_shared<CShader>();
		FadeShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		FadeShader->Create(graphics::eShaderStage::PS, L"FadePS.hlsl", "main");
		CResources::Insert<CShader>(L"FadeShader", FadeShader);

		std::shared_ptr<CShader> ColorShader = std::make_shared<CShader>();
		ColorShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		ColorShader->Create(graphics::eShaderStage::PS, L"ColorPS.hlsl", "main");
		CResources::Insert<CShader>(L"ColorShader", ColorShader);

		std::shared_ptr<CShader> DebugShader = std::make_shared<CShader>();
		DebugShader->Create(graphics::eShaderStage::VS, L"DebugVS.hlsl", "main");
		DebugShader->Create(graphics::eShaderStage::PS, L"DebugPS.hlsl", "main");
		DebugShader->SetRSState(eRasterizerType::SolidNone);
		DebugShader->SetDSState(eDepthStencilType::NoWrite);
		DebugShader->SetBSState(eBlendStateType::AlphaBlend);
		DebugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
		CResources::Insert<CShader>(L"DebugShader", DebugShader);

	}

	void LoadTexture()
	{
		CResources::Load<CTexture>(L"default", L"default.png");
		CResources::Load<CTexture>(L"Black", L"TitleScene/bgBlack.png");
		CResources::Load<CTexture>(L"Steel", L"TitleScene/bgSteel.png");
		CResources::Load<CTexture>(L"TitleKatana", L"TitleScene/bgTitleKatana.png");
		CResources::Load<CTexture>(L"TitleZer_1", L"TitleScene/bgTitleZer_1.png");
		CResources::Load<CTexture>(L"TitleO_1", L"TitleScene/bgTitleO_1.png");
		CResources::Load<CTexture>(L"Fence", L"TitleScene/bgFence.png");
		CResources::Load<CTexture>(L"Grass", L"TitleScene/bgGrass.png");
	}


	void LoadMaterial()
	{
		LoadTexture();

		std::shared_ptr<CTexture> Meshtexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> MeshShader = CResources::Find<CShader>(L"MeshShader");
		std::shared_ptr<CMaterial> MeshMaterial = std::make_shared<CMaterial>();
		MeshMaterial->SetRenderingMode(eRenderingMode::Transparent);
		MeshMaterial->SetShader(MeshShader);
		MeshMaterial->SetTexture(Meshtexture);
		CResources::Insert<CMaterial>(L"MeshMaterial", MeshMaterial);

		std::shared_ptr<CTexture> Spritetexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> SpriteShader = CResources::Find<CShader>(L"SpriteShader");
		std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>();
		SpriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		SpriteMaterial->SetShader(SpriteShader);
		SpriteMaterial->SetTexture(Spritetexture);
		CResources::Insert<CMaterial>(L"SpriteMaterial", SpriteMaterial);

		std::shared_ptr<CTexture> UItexture = CResources::Find<CTexture>(L"Title");
		std::shared_ptr<CShader> UIShader = CResources::Find<CShader>(L"UIShader");
		std::shared_ptr<CMaterial> UIMaterial = std::make_shared<CMaterial>();
		UIMaterial->SetRenderingMode(eRenderingMode::Transparent);
		UIMaterial->SetShader(UIShader);
		UIMaterial->SetTexture(UItexture);
		CResources::Insert<CMaterial>(L"UIMaterial", UIMaterial);

		std::shared_ptr<CShader> GridShader = CResources::Find<CShader>(L"GridShader");
		std::shared_ptr<CMaterial> GridMaterial = std::make_shared<CMaterial>();
		GridMaterial->SetRenderingMode(eRenderingMode::Opaque);
		GridMaterial->SetShader(GridShader);
		CResources::Insert<CMaterial>(L"GridMaterial", GridMaterial);

		std::shared_ptr<CTexture> Fadetexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> FadeShader = CResources::Find<CShader>(L"FadeShader");
		std::shared_ptr<CMaterial> FadeMaterial = std::make_shared<CMaterial>();
		FadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		FadeMaterial->SetShader(FadeShader);
		FadeMaterial->SetTexture(Fadetexture);
		CResources::Insert<CMaterial>(L"FadeMaterial", FadeMaterial);

		std::shared_ptr<CTexture> Colortexture = CResources::Find<CTexture>(L"Black");
		std::shared_ptr<CShader> ColorShader = CResources::Find<CShader>(L"ColorShader");
		std::shared_ptr<CMaterial> ColorMaterial = std::make_shared<CMaterial>();
		ColorMaterial->SetRenderingMode(eRenderingMode::Transparent);
		ColorMaterial->SetShader(ColorShader);
		ColorMaterial->SetTexture(Colortexture);
		CResources::Insert<CMaterial>(L"ColorMaterial", ColorMaterial);

		std::shared_ptr<CShader> DebugShader = CResources::Find<CShader>(L"DebugShader");
		std::shared_ptr<CMaterial> DebugMaterial = std::make_shared<CMaterial>();
		DebugMaterial->SetRenderingMode(eRenderingMode::Opaque);
		DebugMaterial->SetShader(DebugShader);
		CResources::Insert<CMaterial>(L"DebugMaterial", DebugMaterial);

	}

	void Initialize()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형



		LoadMesh();
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

	void Render()
	{
		UINT type = (UINT)CSceneMgr::mActiveScene->GetType();

		for (CCamera* cam : Cameras[type])
		{
			if (nullptr == cam)
				continue;
			cam->render();
		}
		Cameras[type].clear();
	}
}