#include "Renderer.h"
#include "Resources.h"
#include "Material.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "PaintShader.h"
#include "ParticleShader.h"
#include "TimeMgr.h"
#include "Application.h"
#include "AudioClip.h"

namespace dru::renderer
{
	// vertex data

	CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)graphics::eSamplerType::End];
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState[(UINT)graphics::eRasterizerType::End];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState[(UINT)graphics::eDepthStencilType::End];
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendState[(UINT)graphics::eBlendStateType::End];

	CCamera* mainCamera = nullptr;
	std::vector<CCamera*> Cameras[static_cast<UINT>(CSceneMgr::eSceneType::End)];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	CStructedBuffer* lightBuffer = nullptr;

	std::shared_ptr<CTexture> postProcessTexture = nullptr;

	void LoadMesh()
	{

		#pragma region PointMesh

		Vertex PointVertex = {};
		std::shared_ptr<CMesh> pointMesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Pointmesh", pointMesh);
		pointMesh->CreateVertexBuffer(&PointVertex, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
		
		#pragma endregion

		#pragma region LineMesh

		Vertex LineVertex[2] = {};

		LineVertex[0].pos = Vector4(-0.5f, 0.25f, 0.f, 1.f); // 사각형의 lefttop
		LineVertex[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB 비율좌표임
		LineVertex[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		LineVertex[1].pos = Vector4(0.5f, 0.25f, 0.f, 1.f);
		LineVertex[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		LineVertex[1].uv = Vector2(1.f, 0.f);


		std::shared_ptr<CMesh> lineMesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Linemesh", lineMesh);
		lineMesh->CreateVertexBuffer(&LineVertex, 2);
		std::vector<UINT> lineindexes;
		lineindexes.push_back(0);
		lineindexes.push_back(1);
		lineMesh->CreateIndexBuffer(lineindexes.data(), static_cast<UINT>(lineindexes.size()));

		#pragma endregion

		#pragma region RectMesh

		Vertex	RectVertexes[4] = {};

		RectVertexes[0].pos = Vector4(-0.5f, 0.5f, 0.f, 1.f); // 사각형의 lefttop
		RectVertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB 비율좌표임
		RectVertexes[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		RectVertexes[1].pos = Vector4(0.5f, 0.5f, 0.f, 1.f);
		RectVertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		RectVertexes[1].uv = Vector2(1.f, 0.f);

		RectVertexes[2].pos = Vector4(0.5f, -0.5f, 0.f, 1.f);
		RectVertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		RectVertexes[2].uv = Vector2(1.f, 1.f);

		RectVertexes[3].pos = Vector4(-0.5f, -0.5f, 0.f, 1.f);
		RectVertexes[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		RectVertexes[3].uv = Vector2(0.f, 1.f);

		std::shared_ptr<CMesh> Rectmesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Rectmesh", Rectmesh);
		Rectmesh->CreateVertexBuffer(RectVertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		Rectmesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));

		#pragma endregion

		#pragma region RectMesh_Debug

		Vertex	DebugRectVertexes[4] = {};

		DebugRectVertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.f); // 사각형의 lefttop
		DebugRectVertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f); // RGB 비율좌표임
		DebugRectVertexes[0].uv = Vector2(0.f, 0.f); // uv좌표의 left top

		DebugRectVertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.f);
		DebugRectVertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		DebugRectVertexes[1].uv = Vector2(1.f, 0.f);

		DebugRectVertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.f);
		DebugRectVertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		DebugRectVertexes[2].uv = Vector2(1.f, 1.f);

		DebugRectVertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.f);
		DebugRectVertexes[3].color = Vector4(0.f, 0.f, 0.f, 1.f);
		DebugRectVertexes[3].uv = Vector2(0.f, 1.f);

		indexes.clear();
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		std::shared_ptr<CMesh> DebugRectmesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"DebugRectmesh", DebugRectmesh);
		DebugRectmesh->CreateVertexBuffer(DebugRectVertexes, 4);
		DebugRectmesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));

		#pragma endregion

		#pragma region CircleMesh

		std::vector<Vertex>	CircleVertexes;
		Vertex center = {};
		center.pos = Vector4(0.f, 0.f, -0.00001f, 1.f);
		center.color= Vector4(0.f, 1.f, 0.f, 1.f);
		center.uv = Vector2::Zero;

		CircleVertexes.push_back(center);

		int slice = 80;
		float radius = 0.5f;
		float theta = XM_2PI / (float)slice;

		for (int i = 0; i < slice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4(radius * cosf(theta * (float)i)
							, radius * sinf(theta * (float)i)
							, -0.00001f, 1.f
			);
			vtx.color = center.color;

			CircleVertexes.push_back(vtx);
		}
		indexes.clear();
		for (int i = 1; i <= slice; i++) // center 정점 제외
		{
			indexes.push_back(i);
		}
		indexes.push_back(1);

		std::shared_ptr<CMesh> Circlemesh = std::make_shared<CMesh>();
		CResources::Insert<CMesh>(L"Circlemesh", Circlemesh);	
		Circlemesh->CreateVertexBuffer(CircleVertexes.data(), static_cast<UINT>(CircleVertexes.size()));
		Circlemesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));


		#pragma endregion

	}


	void SetUpState()
	{
		
		#pragma region InputLayout
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {}; // mPos, color, uv

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

		std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> afterimageShader = CResources::Find<CShader>(L"AfterImageShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, afterimageShader->GetVSBlobBufferPointer()
			, afterimageShader->GetVSBlobBufferSize()
			, afterimageShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> postProcessShader = CResources::Find<CShader>(L"PostProcessShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, postProcessShader->GetVSBlobBufferPointer()
			, postProcessShader->GetVSBlobBufferSize()
			, postProcessShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> waveShader = CResources::Find<CShader>(L"WaveShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, waveShader->GetVSBlobBufferPointer()
			, waveShader->GetVSBlobBufferSize()
			, waveShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> greyScaleShader = CResources::Find<CShader>(L"GreyScaleShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, greyScaleShader->GetVSBlobBufferPointer()
			, greyScaleShader->GetVSBlobBufferSize()
			, greyScaleShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> snowShader = CResources::Find<CShader>(L"SnowShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, snowShader->GetVSBlobBufferPointer()
			, snowShader->GetVSBlobBufferSize()
			, snowShader->GetInputLayoutAddr());

		std::shared_ptr<CShader> LaserHitShader = CResources::Find<CShader>(L"LaserHitShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, LaserHitShader->GetVSBlobBufferPointer()
			, LaserHitShader->GetVSBlobBufferSize()
			, LaserHitShader->GetInputLayoutAddr());

#pragma endregion

		#pragma region SamplerState
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
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
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilState[(UINT)graphics::eDepthStencilType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilState[(UINT)graphics::eDepthStencilType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilState[(UINT)graphics::eDepthStencilType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthStencilState[(UINT)graphics::eDepthStencilType::None].GetAddressOf());

		#pragma endregion

		#pragma region BlendState

		blendState[(UINT)graphics::eBlendStateType::Default] = nullptr;

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
		GetDevice()->CreateBlendState(&bsDesc, blendState[(UINT)graphics::eBlendStateType::AlphaBlend].GetAddressOf());	

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		GetDevice()->CreateBlendState(&bsDesc, blendState[(UINT)graphics::eBlendStateType::OneOne].GetAddressOf());


		#pragma endregion

	}


	void LoadBuffer()
	{
		// Const buffer	
		constantBuffers[static_cast<UINT>(eCBType::Transform)] = new CConstantBuffer(eCBType::Transform);
		constantBuffers[static_cast<UINT>(eCBType::Transform)]->Create(sizeof(TransformCB));
	
		constantBuffers[static_cast<UINT>(eCBType::Material)] = new CConstantBuffer(eCBType::Material);
		constantBuffers[static_cast<UINT>(eCBType::Material)]->Create(sizeof(MaterialCB));

		constantBuffers[static_cast<UINT>(eCBType::Grid)] = new CConstantBuffer(eCBType::Grid);
		constantBuffers[static_cast<UINT>(eCBType::Grid)]->Create(sizeof(GridCB));

		constantBuffers[static_cast<UINT>(eCBType::Color)] = new CConstantBuffer(eCBType::Color);
		constantBuffers[static_cast<UINT>(eCBType::Color)]->Create(sizeof(ColorCB));

		constantBuffers[static_cast<UINT>(eCBType::Animation)] = new CConstantBuffer(eCBType::Animation);
		constantBuffers[static_cast<UINT>(eCBType::Animation)]->Create(sizeof(AnimationCB));

		constantBuffers[static_cast<UINT>(eCBType::Light)] = new CConstantBuffer(eCBType::Light);
		constantBuffers[static_cast<UINT>(eCBType::Light)]->Create(sizeof(LightCB));
	
		constantBuffers[static_cast<UINT>(eCBType::ParticleSystem)] = new CConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[static_cast<UINT>(eCBType::ParticleSystem)]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new CConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		constantBuffers[(UINT)eCBType::PostProcess] = new CConstantBuffer(eCBType::PostProcess);
		constantBuffers[(UINT)eCBType::PostProcess]->Create(sizeof(PostProcessCB));

		constantBuffers[(UINT)eCBType::LaserHit] = new CConstantBuffer(eCBType::LaserHit);
		constantBuffers[(UINT)eCBType::LaserHit]->Create(sizeof(LaserHitCB));

		// structed buffer
		lightBuffer = new CStructedBuffer();
		lightBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
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
//		SpriteShader->SetBSState(eBlendStateType::AlphaBlend);
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

		std::shared_ptr<CPaintShader> paintShader = std::make_shared<CPaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		CResources::Insert<CPaintShader>(L"PaintShader", paintShader);

		{
			std::shared_ptr<CShader> particleShader = std::make_shared<CShader>();
			particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
			particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
			particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
			particleShader->SetRSState(eRasterizerType::SolidNone);
			particleShader->SetDSState(eDepthStencilType::NoWrite);
			particleShader->SetBSState(eBlendStateType::AlphaBlend);
			particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			CResources::Insert<CShader>(L"ParticleShader", particleShader);
		}
		{
			std::shared_ptr<CShader> particleShader = std::make_shared<CShader>();
			particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
			particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
			particleShader->Create(eShaderStage::PS, L"AimParticlePS.hlsl", "main");
			particleShader->SetRSState(eRasterizerType::SolidNone);
			particleShader->SetDSState(eDepthStencilType::NoWrite);
			particleShader->SetBSState(eBlendStateType::AlphaBlend);
			particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			CResources::Insert<CShader>(L"AimParticleShader", particleShader);
		}
		{
			std::shared_ptr<CShader> particleShader = std::make_shared<CShader>();
			particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
			particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
			particleShader->Create(eShaderStage::PS, L"LaserParticlePS.hlsl", "main");
			particleShader->SetRSState(eRasterizerType::SolidNone);
			particleShader->SetDSState(eDepthStencilType::NoWrite);
			particleShader->SetBSState(eBlendStateType::AlphaBlend);
			particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			CResources::Insert<CShader>(L"LaserParticleShader", particleShader);
		}
		{
			std::shared_ptr<CShader> LaserHitShader = std::make_shared<CShader>();
			LaserHitShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
			LaserHitShader->Create(graphics::eShaderStage::PS, L"LaserHitPS.hlsl", "main");
			CResources::Insert<CShader>(L"LaserHitShader", LaserHitShader);
		}

		std::shared_ptr<CParticleShader> particleCS = std::make_shared<CParticleShader>();
		CResources::Insert<CParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");

		std::shared_ptr<CParticleShader> aimParticleCS = std::make_shared<CParticleShader>();
		CResources::Insert<CParticleShader>(L"AimParticleCS", aimParticleCS);
		aimParticleCS->Create(L"AimParticleCS.hlsl", "main");

		std::shared_ptr<CParticleShader> playerParticleCS = std::make_shared<CParticleShader>();
		CResources::Insert<CParticleShader>(L"LaserParticleCS", playerParticleCS);
		playerParticleCS->Create(L"LaserParticleCS.hlsl", "main");

		std::shared_ptr<CParticleShader> batteryParticleCS = std::make_shared<CParticleShader>();
		CResources::Insert<CParticleShader>(L"BatteryParticleCS", batteryParticleCS);
		batteryParticleCS->Create(L"BatteryParticleCS.hlsl", "main");

		std::shared_ptr<CShader> AfterImageShader = std::make_shared<CShader>();
		AfterImageShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		AfterImageShader->Create(graphics::eShaderStage::PS, L"AfterImagePS.hlsl", "main"); 
		CResources::Insert<CShader>(L"AfterImageShader", AfterImageShader);

		std::shared_ptr<CShader> postProcessShader = std::make_shared<CShader>();
		postProcessShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		postProcessShader->Create(eShaderStage::PS, L"PostProcessPS.hlsl", "main");
		postProcessShader->SetDSState(eDepthStencilType::NoWrite);
		CResources::Insert<CShader>(L"PostProcessShader", postProcessShader);

		std::shared_ptr<CShader> WaveShader = std::make_shared<CShader>();
		WaveShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		WaveShader->Create(eShaderStage::PS, L"WavePS.hlsl", "main");
		WaveShader->SetDSState(eDepthStencilType::NoWrite);
		CResources::Insert<CShader>(L"WaveShader", WaveShader);

		std::shared_ptr<CShader> GreyScaleShader = std::make_shared<CShader>();
		GreyScaleShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		GreyScaleShader->Create(eShaderStage::PS, L"GreyScalePS.hlsl", "main");
		GreyScaleShader->SetDSState(eDepthStencilType::NoWrite);
		CResources::Insert<CShader>(L"GreyScaleShader", GreyScaleShader);

		std::shared_ptr<CShader> SnowShader = std::make_shared<CShader>();
		SnowShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		SnowShader->Create(eShaderStage::PS, L"SnowPS.hlsl", "main");
		SnowShader->SetDSState(eDepthStencilType::NoWrite);
		CResources::Insert<CShader>(L"SnowShader", SnowShader);

	}

	void LoadTexture()
	{

		// title
		CResources::Load<CTexture>(L"default", L"default.png");
		CResources::Load<CTexture>(L"Black", L"TitleScene/bgBlack.png");
		CResources::Load<CTexture>(L"Steel", L"TitleScene/bgSteel.png");
		CResources::Load<CTexture>(L"TitleKatana", L"TitleScene/bgTitleKatana.png");
		CResources::Load<CTexture>(L"TitleZer_1", L"TitleScene/bgTitleZer_1.png");
		CResources::Load<CTexture>(L"TitleO_1", L"TitleScene/bgTitleO_1.png");
		CResources::Load<CTexture>(L"Fence", L"TitleScene/bgFence.png");
		CResources::Load<CTexture>(L"Grass", L"TitleScene/bgGrass.png");
		CResources::Load<CTexture>(L"Grass2", L"TitleScene/bgGrass2.png");
		CResources::Load<CTexture>(L"TitleButton", L"TitleScene/TitleButtons.png");

		// main
		CResources::Load<CTexture>(L"texCursor", L"MainScene/Cursor.png");
		CResources::Load<CTexture>(L"stagetutorial", L"MainScene/Background/Tutorialbg.png");
		CResources::Load<CTexture>(L"stage1", L"MainScene/Background/Stage1bg.png");
		CResources::Load<CTexture>(L"stage2", L"MainScene/Background/Stage2bg.png");
		CResources::Load<CTexture>(L"stage3", L"MainScene/Background/Stage3bg.png");
		CResources::Load<CTexture>(L"bossStage1", L"MainScene/Background/Boss1bg.png");
		CResources::Load<CTexture>(L"bossStage2", L"MainScene/Background/Boss2_2bg.png");
		CResources::Load<CTexture>(L"mask", L"MainScene/Background/transition_mask.png");


		// Objs
		CResources::Load<CTexture>(L"tutorialtxt", L"MainScene/Font/tutorial.png");
		CResources::Load<CTexture>(L"particle_spark", L"MainScene/spark_particle.png");
		CResources::Load<CTexture>(L"bullet", L"MainScene/bullet.png");
		CResources::Load<CTexture>(L"halogen", L"MainScene/Background/Object/halogen.png");
		CResources::Load<CTexture>(L"desk", L"MainScene/Background/Object/desk.png");
		CResources::Load<CTexture>(L"plant", L"MainScene/Background/Object/plant.png");
		CResources::Load<CTexture>(L"door", L"MainScene/Background/Object/door.png");


		// player
		CResources::Load<CTexture>(L"player", L"MainScene/Player.png");
		// monster
		CResources::Load<CTexture>(L"grunt", L"MainScene/Monster/Grunt.png");
		CResources::Load<CTexture>(L"pomp", L"MainScene/Monster/Pomp.png");
		CResources::Load<CTexture>(L"cop", L"MainScene/Monster/Cop.png");
		CResources::Load<CTexture>(L"cop_gun", L"MainScene/Monster/Cop_Gun.png");

		CResources::Load<CTexture>(L"kissyface", L"MainScene/Monster/Kissyface.png");
		CResources::Load<CTexture>(L"kissyface_axe", L"MainScene/Monster/kissyface_axe.png");

		CResources::Load<CTexture>(L"headhunter", L"MainScene/Monster/HeadHunter.png");

		CResources::Load<CTexture>(L"laserTurret", L"MainScene/Monster/laserTurret.png");
		CResources::Load<CTexture>(L"laserShoot", L"MainScene/Monster/laserShoot.png");


		CResources::Load<CTexture>(L"hud_top", L"MainScene/Hud/hud_top.png");
		CResources::Load<CTexture>(L"hud_timer", L"MainScene/Hud/hud_timer.png");
		CResources::Load<CTexture>(L"hud_timerbar", L"MainScene/Hud/hud_timerbar.png");
		CResources::Load<CTexture>(L"hud_battery", L"MainScene/Hud/hud_battery.png");
		CResources::Load<CTexture>(L"hud_batterypart", L"MainScene/Hud/hud_batterypart.png");
		CResources::Load<CTexture>(L"hud_inventory", L"MainScene/Hud/hud_inventory.png");
		CResources::Load<CTexture>(L"hud_keys", L"MainScene/Hud/hud_keys.png");
		CResources::Load<CTexture>(L"icon_hand", L"MainScene/Hud/Itemicons/Hand.png");
		CResources::Load<CTexture>(L"icon_katana", L"MainScene/Hud/Itemicons/Katana.png");
		CResources::Load<CTexture>(L"icon_Butcher", L"MainScene/Hud/Itemicons/Butcher.png");


		CResources::Load<CTexture>(L"tutorialtxt", L"MainScene/Font/tutorial.png");
		CResources::Load<CTexture>(L"wall", L"MainScene/wall.png");

		CResources::Load<CTexture>(L"blood", L"MainScene/Blood/Blood.png");
		CResources::Load<CTexture>(L"smallBlood1", L"MainScene/Blood/Decal/smallBlood1.png");
		CResources::Load<CTexture>(L"smallBlood2", L"MainScene/Blood/Decal/smallBlood2.png");
		CResources::Load<CTexture>(L"smallBlood3", L"MainScene/Blood/Decal/smallBlood3.png");
		CResources::Load<CTexture>(L"smallBlood4", L"MainScene/Blood/Decal/smallBlood4.png");
		CResources::Load<CTexture>(L"bloodDecal1", L"MainScene/Blood/Decal/bigBlood1.png");
		CResources::Load<CTexture>(L"bloodDecal2", L"MainScene/Blood/Decal/bigBlood2.png");
		CResources::Load<CTexture>(L"bloodDecal3", L"MainScene/Blood/Decal/bigBlood3.png");
		CResources::Load<CTexture>(L"bloodDecal4", L"MainScene/Blood/Decal/bigBlood4.png");
		CResources::Load<CTexture>(L"bloodDecal5", L"MainScene/Blood/Decal/bigBlood5.png");
		CResources::Load<CTexture>(L"bloodDecal6", L"MainScene/Blood/Decal/bigBlood6.png");

		// FX
		CResources::Load<CTexture>(L"fx_dust", L"MainScene/FX/fx_dust.png");
		CResources::Load<CTexture>(L"fx_slashPlayer", L"MainScene/FX/fx_slash.png");
		CResources::Load<CTexture>(L"fx_slash", L"MainScene/FX/slash.png");
		CResources::Load<CTexture>(L"fx_landdust", L"MainScene/FX/fx_landdust.png");
		CResources::Load<CTexture>(L"fx_bulletReflect", L"MainScene/FX/fx_bulletReflect.png");
		CResources::Load<CTexture>(L"fx_gunSmoke", L"MainScene/FX/fx_gunSmoke.png");
		CResources::Load<CTexture>(L"fx_gunFire", L"MainScene/FX/fx_gunFire.png");


		// mission
		CResources::Load<CTexture>(L"job_corner", L"MissionScene/job_corner.png");
		CResources::Load<CTexture>(L"job_front", L"MissionScene/job_front.png");
		CResources::Load<CTexture>(L"job_frontshoadow", L"MissionScene/job_frontshoadow.png");
		CResources::Load<CTexture>(L"job_left", L"MissionScene/job_left.png");
		CResources::Load<CTexture>(L"job_right", L"MissionScene/job_right.png");
		CResources::Load<CTexture>(L"job_profile", L"MissionScene/job_profile.png");


		// noise
		CResources::Load<CTexture>(L"noise1", L"noise/noise_01.png");
		CResources::Load<CTexture>(L"noise2", L"noise/noise_02.png");
		CResources::Load<CTexture>(L"noise3", L"noise/noise_03.png");

		CResources::Load<CTexture>(L"burn", L"noise/burn.png");
		CResources::Load<CTexture>(L"glitch", L"noise/glitch.png");

		std::shared_ptr<CTexture> uavTexture = std::make_shared<CTexture>();
		uavTexture->Create(1024, 1024, 
			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 
			D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS);
		CResources::Insert<CTexture>(L"PaintTexture", uavTexture);

		postProcessTexture = std::make_shared<CTexture>();
		postProcessTexture->Create(1600, 900, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
		CResources::Insert<CTexture>(L"PostProcessTexture", postProcessTexture);
	}


	void LoadMaterial()
	{

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
		DebugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		DebugMaterial->SetShader(DebugShader);
		CResources::Insert<CMaterial>(L"DebugMaterial", DebugMaterial);

		std::shared_ptr <CTexture> Painttexture = CResources::Find<CTexture>(L"PaintTexture");
		std::shared_ptr<CShader> PaintShader = CResources::Find<CShader>(L"MeshShader");
		std::shared_ptr<CMaterial> PaintMaterial = std::make_shared<CMaterial>();
		PaintMaterial->SetShader(PaintShader);
		PaintMaterial->SetTexture(Painttexture);
		CResources::Insert<CMaterial>(L"PaintMaterial", PaintMaterial);

		std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"ParticleShader");
		std::shared_ptr<CMaterial> particleMaterial = std::make_shared<CMaterial>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		CResources::Insert<CMaterial>(L"ParticleMaterial", particleMaterial);

		std::shared_ptr<CShader> postProcessShader = CResources::Find<CShader>(L"PostProcessShader");
		std::shared_ptr<CMaterial> postProcessMaterial = std::make_shared<CMaterial>();
		postProcessMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		postProcessMaterial->SetShader(postProcessShader);
		postProcessMaterial->SetTexture(postProcessTexture);
		CResources::Insert<CMaterial>(L"PostProcessMaterial", postProcessMaterial);

		std::shared_ptr<CShader> waveShader = CResources::Find<CShader>(L"WaveShader");
		std::shared_ptr<CMaterial> waveMaterial = std::make_shared<CMaterial>();
		waveMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		waveMaterial->SetShader(waveShader);
		waveMaterial->SetTexture(postProcessTexture);
		CResources::Insert<CMaterial>(L"WaveMaterial", waveMaterial);

		std::shared_ptr<CShader> greyScaleShader = CResources::Find<CShader>(L"GreyScaleShader");
		std::shared_ptr<CMaterial> greyScaleMaterial = std::make_shared<CMaterial>();
		greyScaleMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		greyScaleMaterial->SetShader(greyScaleShader);
		greyScaleMaterial->SetTexture(postProcessTexture);
		CResources::Insert<CMaterial>(L"GreyScaleMaterial", greyScaleMaterial);

		std::shared_ptr<CShader> snowShader = CResources::Find<CShader>(L"SnowShader");
		std::shared_ptr<CMaterial> snowMaterial = std::make_shared<CMaterial>();
		snowMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		snowMaterial->SetShader(snowShader);
		snowMaterial->SetTexture(postProcessTexture);
		CResources::Insert<CMaterial>(L"SnowMaterial", snowMaterial);

		// etc
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
			CResources::Insert<CMaterial>(L"UITitleBgMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_keys", L"SpriteShader");
			CResources::Insert<CMaterial>(L"keys", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_dust", L"SpriteShader");
			CResources::Insert<CMaterial>(L"dustMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_landdust", L"SpriteShader");
			CResources::Insert<CMaterial>(L"landdustMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slashPlayer", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerSlashMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slashPlayer", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BodySlashMat", Material);
		}	
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_gunFire", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GunFireMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_gunSmoke", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GunSmokeMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_bulletReflect", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BulletReflectMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"wall", L"SpriteShader");
			CResources::Insert<CMaterial>(L"wallMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bullet", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Bullet", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"blood", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BloodMat", Material);
		} 
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerBulletTimeMat", Material);
			Vector4 color = Vector4(0.f, 2.f, 2.f, 0.5f);
			Material->SetData(eGPUParam::Vector4_1, &color);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerLaserMat", Material);
			Vector4 color = Vector4(3.f, 3.f, 0.f, 1.f);
			Material->SetData(eGPUParam::Vector4_1, &color);
		} 
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"halogen", L"SpriteShader");
			CResources::Insert<CMaterial>(L"halogenMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"desk", L"SpriteShader");
			CResources::Insert<CMaterial>(L"deskMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"plant", L"SpriteShader");
			CResources::Insert<CMaterial>(L"plantMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"grunt", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GruntMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"pomp", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PompMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop", L"SpriteShader");
			CResources::Insert<CMaterial>(L"CopMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop", L"SpriteShader");
			CResources::Insert<CMaterial>(L"CopMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"laserTurret", L"SpriteShader");
			CResources::Insert<CMaterial>(L"laserTurretMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"laserShoot", L"SpriteShader");
			CResources::Insert<CMaterial>(L"laserBeamMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal1Mat", Material);
		} 
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal2Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal3", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal3Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal4", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal4Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal5", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal5Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal6", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal6Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood1Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood2Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood3", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood3Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood4", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood4Mat", Material);
		}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood5", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood5Mat", Material);
		//}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood6", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood6Mat", Material);
		//}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood7", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood7Mat", Material);
		//}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"AimParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"LaserTurretParticleMat", Material);
		}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"LaserParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"PlayerParticleMat", Material);
		}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"LaserParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"BatteryParticleMat", Material);
		}

		for (int i = 0; i <= 100; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"AfterImageShader");
			std::wstring matName = L"PlayerMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		for (int i = 0; i <= 100; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"AfterImageShader");
			std::wstring matName = L"kissyfaceMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		for (int i = 0; i <= 50; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"AfterImageShader");
			std::wstring matName = L"AxeMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
	}

	void LoadAudio()
	{
		// song
		CResources::Load<CAudioClip>(L"song_title_bgm", L"Sound/Song/song_title.ogg");
		CResources::Load<CAudioClip>(L"song_main_bgm",  L"Sound/Song/song_main.ogg");
		CResources::Load<CAudioClip>(L"song_tutorial_bgm", L"Sound/Song/song_tutorial.ogg");
		CResources::Load<CAudioClip>(L"song_china_bgm", L"Sound/Song/song_chinatown.ogg");
		CResources::Load<CAudioClip>(L"song_boss_bgm",  L"Sound/Song/song_boss.ogg");
		////////////////////////////////////////////////////////////////////////////

		// sound effect

		// title scene
		CResources::Load<CAudioClip>(L"SE_title_neon", L"Sound/title_neon.wav");
		CResources::Load<CAudioClip>(L"SE_title_rain", L"Sound/title_rain.wav");
		CResources::Load<CAudioClip>(L"SE_title_select", L"Sound/title_select.wav");
		CResources::Load<CAudioClip>(L"SE_title_splash", L"Sound/title_splash.wav");
		CResources::Load<CAudioClip>(L"SE_title_updown", L"Sound/title_updown.wav");


		// play scene
		CResources::Load<CAudioClip>(L"SE_rewind", L"Sound/rewind.wav");
		CResources::Load<CAudioClip>(L"SE_replay", L"Sound/replay_play.wav");
		CResources::Load<CAudioClip>(L"SE_mp3rewind", L"Sound/mp3rewind.wav");
		CResources::Load<CAudioClip>(L"SE_correct", L"Sound/correct.wav");

		// player
		CResources::Load<CAudioClip>(L"player_die", L"Sound/Player/player_die.wav");
		CResources::Load<CAudioClip>(L"player_footstep", L"Sound/Player/player_footstep.wav");
		CResources::Load<CAudioClip>(L"player_jump", L"Sound/Player/player_jump.wav");
		CResources::Load<CAudioClip>(L"player_land", L"Sound/Player/player_land.wav");
		CResources::Load<CAudioClip>(L"player_prerun", L"Sound/Player/player_prerun.wav");
		CResources::Load<CAudioClip>(L"player_roll", L"Sound/Player/player_roll.wav");
		CResources::Load<CAudioClip>(L"player_roll_real", L"Sound/Player/player_roll_real.wav");
		CResources::Load<CAudioClip>(L"player_run1", L"Sound/Player/player_run1.wav");
		CResources::Load<CAudioClip>(L"player_run2", L"Sound/Player/player_run2.wav");
		CResources::Load<CAudioClip>(L"player_run3", L"Sound/Player/player_run3.wav");
		CResources::Load<CAudioClip>(L"player_run4", L"Sound/Player/player_run4.wav");
		CResources::Load<CAudioClip>(L"player_slash1", L"Sound/Player/player_slash1.wav");
		CResources::Load<CAudioClip>(L"player_slash2", L"Sound/Player/player_slash2.wav");
		CResources::Load<CAudioClip>(L"player_slash3", L"Sound/Player/player_slash3.wav");
		CResources::Load<CAudioClip>(L"player_wallkick1", L"Sound/Player/player_wallkick1.wav");
		CResources::Load<CAudioClip>(L"player_wallkick2", L"Sound/Player/player_wallkick2.wav");
		CResources::Load<CAudioClip>(L"player_wallkick3", L"Sound/Player/player_wallkick3.wav");
		CResources::Load<CAudioClip>(L"player_wallslide", L"Sound/Player/player_wallslide.wav");
	

		// monster
		CResources::Load<CAudioClip>(L"monser_walk1",			L"Sound/Monster/monser_walk1.wav");
		CResources::Load<CAudioClip>(L"monser_walk2",			L"Sound/Monster/monser_walk2.wav");
		CResources::Load<CAudioClip>(L"monser_walk3",			L"Sound/Monster/monser_walk3.wav");
		CResources::Load<CAudioClip>(L"monser_walk4",			L"Sound/Monster/monser_walk4.wav");
		CResources::Load<CAudioClip>(L"monster_death_bullet",	L"Sound/Monster/monster_death_bullet.wav");
		CResources::Load<CAudioClip>(L"monster_death1",			L"Sound/Monster/monster_death1.wav");
		CResources::Load<CAudioClip>(L"monster_death2",			L"Sound/Monster/monster_death2.wav");
		CResources::Load<CAudioClip>(L"monster_death3",			L"Sound/Monster/monster_death3.wav");
		CResources::Load<CAudioClip>(L"monster_reload",			L"Sound/Monster/monster_reload.wav");
		CResources::Load<CAudioClip>(L"monster_run1",			L"Sound/Monster/monster_run1.wav");
		CResources::Load<CAudioClip>(L"monster_run2",			L"Sound/Monster/monster_run2.wav");
		CResources::Load<CAudioClip>(L"monster_run3",			L"Sound/Monster/monster_run3.wav");
		CResources::Load<CAudioClip>(L"monster_run4",			L"Sound/Monster/monster_run4.wav");
		CResources::Load<CAudioClip>(L"monster_shot",			L"Sound/Monster/monster_shot.wav");
		CResources::Load<CAudioClip>(L"monstser_slide",			L"Sound/Monster/monstser_slide.wav");

		// kissyface
		CResources::Load<CAudioClip>(L"kissyface_axecatch", L"Sound/Kissyface/kissyface_axecatch.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeimpact", L"Sound/Kissyface/kissyface_axeimpact.wav");
		CResources::Load<CAudioClip>(L"kissyface_axelunge", L"Sound/Kissyface/kissyface_axelunge.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeprepare", L"Sound/Kissyface/kissyface_axeprepare.wav");
		CResources::Load<CAudioClip>(L"kissyface_axereturn", L"Sound/Kissyface/kissyface_axereturn.wav");
		CResources::Load<CAudioClip>(L"kissyface_axethrow", L"Sound/Kissyface/kissyface_axethrow.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeturn", L"Sound/Kissyface/kissyface_axeturn.wav");
		CResources::Load<CAudioClip>(L"kissyface_clash", L"Sound/Kissyface/kissyface_clash.wav");
		CResources::Load<CAudioClip>(L"kissyface_crouch", L"Sound/Kissyface/kissyface_crouch.wav");
		CResources::Load<CAudioClip>(L"kissyface_death", L"Sound/Kissyface/kissyface_death.wav");
		CResources::Load<CAudioClip>(L"kissyface_jump", L"Sound/Kissyface/kissyface_jump.wav");
		CResources::Load<CAudioClip>(L"kissyface_sharpen", L"Sound/Kissyface/kissyface_sharpen.wav");
		CResources::Load<CAudioClip>(L"kissyface_struggle", L"Sound/Kissyface/kissyface_struggle.wav");

		CResources::Load<CAudioClip>(L"kissyface_voice_axethrow", L"Sound/Kissyface/kissyface_voice_axethrow.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_chop", L"Sound/Kissyface/kissyface_voice_chop.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_crouch", L"Sound/Kissyface/kissyface_voice_crouch.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_hurt", L"Sound/Kissyface/kissyface_voice_hurt.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_jump", L"Sound/Kissyface/kissyface_voice_jump.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_lunge", L"Sound/Kissyface/kissyface_voice_lunge.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_prepare", L"Sound/Kissyface/kissyface_voice_prepare.wav");

		// blood
		CResources::Load<CAudioClip>(L"blood_splat1", L"Sound/Blood/blood_splat1.wav");
		CResources::Load<CAudioClip>(L"blood_splat2", L"Sound/Blood/blood_splat2.wav");
		CResources::Load<CAudioClip>(L"blood_splat3", L"Sound/Blood/blood_splat3.wav");
		CResources::Load<CAudioClip>(L"blood_splat4", L"Sound/Blood/blood_splat4.wav");
		CResources::Load<CAudioClip>(L"blood_squirt1", L"Sound/Blood/blood_squirt1.wav");
		CResources::Load<CAudioClip>(L"blood_squirt2", L"Sound/Blood/blood_squirt2.wav");
		CResources::Load<CAudioClip>(L"blood_squirt3", L"Sound/Blood/blood_squirt3.wav");

		// bullet
		CResources::Load<CAudioClip>(L"bullethit1", L"Sound/Bullet/bullethit1.wav");
		CResources::Load<CAudioClip>(L"bullethit2", L"Sound/Bullet/bullethit2.wav");
		CResources::Load<CAudioClip>(L"bullethit3", L"Sound/Bullet/bullethit3.wav");
		CResources::Load<CAudioClip>(L"bullet_die", L"Sound/Bullet/bullet_die.wav");
		CResources::Load<CAudioClip>(L"bullet_slash", L"Sound/Bullet/bullet_slash.wav");

		// laser
		CResources::Load<CAudioClip>(L"laser_blast", L"Sound/Laser/laser_blast.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate1", L"Sound/Laser/laser_evaporate1.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate2", L"Sound/Laser/laser_evaporate2.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate3", L"Sound/Laser/laser_evaporate3.wav");
		CResources::Load<CAudioClip>(L"laser_explosion", L"Sound/Laser/laser_explosion.wav");


		////////////////////////////////////////////////////////////////////////////

	}



	void Initialize()
	{
		// 중앙이 0, 0, 0이고 높이가 1인 정삼각형
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture(); 
		LoadMaterial();
		LoadAudio();
	}

	void release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
		delete lightBuffer;
		lightBuffer = nullptr;
	}

	void Render()
	{
		BindNoiseTexture();
		BindLight();

		UINT type = (UINT)CSceneMgr::mActiveScene->GetType();

		for (CCamera* cam : Cameras[type])
		{
			if (nullptr == cam)
				continue;

			cam->render();
		}
		Cameras[type].clear();
		renderer::lights.clear();
	}

	void PushLightAttribute(LightAttribute _attribute)
	{
		lights.push_back(_attribute);
	}

	void BindLight()
	{
		lightBuffer->SetData(lights.data(), static_cast<UINT>(lights.size()));
		lightBuffer->BindSRV(eShaderStage::VS, 13);
		lightBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB Lightcb = {};
		Lightcb.lightCount = static_cast<UINT>(lights.size());

		CConstantBuffer* cb = constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&Lightcb);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	float noiseTime = 10.f;
	float ElapsedTime = 0.f;

	void BindNoiseTexture()
	{
		std::shared_ptr<CTexture> noise = CResources::Find<CTexture>(L"noise1");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = static_cast<float>(noise->GetWidth()); // 노이즈 텍스처 사이즈를 상수버퍼로 전달해줌
		info.noiseSize.y = static_cast<float>(noise->GetHeight());
		noiseTime -= CTimeMgr::DeltaTime();
		info.noiseTime = noiseTime;

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
	void CopyRenderTarget()
	{
		std::shared_ptr<CTexture> renderTarget = CResources::Find<CTexture>(L"RenderTargetTexture");

		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::PS, 60, &srv);

		ID3D11Texture2D* dest = postProcessTexture->GetTexture().Get();
		ID3D11Texture2D* source = renderTarget->GetTexture().Get();

		GetDevice()->CopyResource(dest, source);

		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
	}
}
