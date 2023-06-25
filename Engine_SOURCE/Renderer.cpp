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

		LineVertex[0].pos = Vector4(-0.5f, 0.25f, 0.f, 1.f); 
		LineVertex[0].color = Vector4(0.f, 1.f, 0.f, 1.f); 
		LineVertex[0].uv = Vector2(0.f, 0.f); 

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

		RectVertexes[0].pos = Vector4(-0.5f, 0.5f, 0.f, 1.f); 
		RectVertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f); 
		RectVertexes[0].uv = Vector2(0.f, 0.f); 

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

		DebugRectVertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.f); 
		DebugRectVertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f); 
		DebugRectVertexes[0].uv = Vector2(0.f, 0.f); 

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
		center.color = Vector4(0.f, 1.f, 0.f, 1.f);
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
		for (int i = 1; i <= slice; i++) 
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
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {}; 

		arrLayout[0].AlignedByteOffset = 0; 
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; 
		arrLayout[0].InputSlot = 0; 
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 16; 
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; 
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
		
		CResources::Insert<CShader>(L"SpriteShader", SpriteShader);


		std::shared_ptr<CShader> UIShader = std::make_shared<CShader>();
		UIShader->Create(graphics::eShaderStage::VS, L"SpriteVS.hlsl", "main");
		UIShader->Create(graphics::eShaderStage::PS, L"UIPS.hlsl", "main");
		CResources::Insert<CShader>(L"UIShader", UIShader);


		std::shared_ptr<CShader> GridShader = std::make_shared<CShader>();
		GridShader->Create(graphics::eShaderStage::VS, L"GridVS.hlsl", "main");
		GridShader->Create(graphics::eShaderStage::PS, L"GridPS.hlsl", "main");
		GridShader->SetRSState(eRasterizerType::SolidNone); 
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
		CResources::Load<CTexture>(L"loading", L"Loading.png");

		
		CResources::Load<CTexture>(L"noise1", L"noise/noise_01.png");
		CResources::Load<CTexture>(L"noise2", L"noise/noise_02.png");
		CResources::Load<CTexture>(L"noise3", L"noise/noise_03.png");


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
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"loading", L"SpriteShader");
			CResources::Insert<CMaterial>(L"loadingMat", Material);
		}

		std::shared_ptr<CShader> DebugShader = CResources::Find<CShader>(L"DebugShader");
		std::shared_ptr<CMaterial> DebugMaterial = std::make_shared<CMaterial>();
		DebugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		DebugMaterial->SetShader(DebugShader);
		CResources::Insert<CMaterial>(L"DebugMaterial", DebugMaterial);

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


	}




	void Initialize()
	{
		
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
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
		info.noiseSize.x = static_cast<float>(noise->GetWidth());
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
