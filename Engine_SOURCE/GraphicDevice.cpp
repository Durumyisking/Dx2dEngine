#include "GraphicDevice.h"
#include "Application.h"
#include "Renderer.h"

extern dru::CApplication application;

namespace dru::graphics
{
	CGraphicDevice::CGraphicDevice(eValidationMode _ValidationMode)
	{
		/*
			 <summary>
			 1. Device 와 SwapChain를 생성한다.
			 2. 백버퍼에 실제로 렌더링할 렌더타겟 뷰를 생성한다.
			 3. 화면을 클리어 해줘야한다. 뷰포트를 생성해줘야 한다.
			 4. 매프레임마다 위에서 생성한 렌더타겟 뷰에 렌더링해준다.
			 5. Swapchain을 이용하여 최종 디바이스(디스플레이)에 화면을 그려준다.
		*/


		HWND hwnd = application.GetHwnd(); // 윈도우 핸들 얻어옴

		// Device, Device Context
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG; // 디버그모드로 만들거임 릴리즈모드는 0
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		// 그냥 bool 형 반환값과 같음 SUCCEEDED / FAILED로 나뉨
		// 함수 반환 성공하면 suc 아니면 fail 나옴
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag
			, nullptr, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf()
			, &FeatureLevel, mContext.GetAddressOf());

		// SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd; // 렌더될 윈도우의 핸들
		swapChainDesc.Windowed = true; // 창모드 전체화면
		swapChainDesc.BufferCount = 2; // 사용할 렌더링 버퍼개수 최대 8
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 렌더타겟으로 쓸거임
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; // 컬러 포멧 타입
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 240; // 프레임 비율 분자
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // 프레임 비율 분모
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		/*
			sample desciption은 Direct3D의 멀티 샘플링 속성을 정의한다. 
			멀티 샘플링은 렌더된 픽셀들의 평균 샘플을 사용하여 최종 컬러를 좀더 부드럽게 하는 기술이다.
			샘플러와 관련된게 맞다.
		*/
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		// Get rendertarget for swapchain
		//						0번 버퍼가 렌더타겟	도화지니까텍스처			목적지
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		// Create Rendertarget View
		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		// Depth/Stencil Buffer
		D3D11_TEXTURE2D_DESC depthBuffer = {};
		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Usage = D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;

		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Width = application.GetWidth();
		depthBuffer.Height = application.GetHeight();
		depthBuffer.ArraySize = 1; // 깊이버퍼 하나만 쓸거니까

		depthBuffer.SampleDesc.Count = 1;
		depthBuffer.SampleDesc.Quality = 0;

		depthBuffer.MipLevels = 1;
		depthBuffer.MiscFlags = 0;

		if (!CreateTexture(&depthBuffer, mDepthStencilBuffer.GetAddressOf()))
			return;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return;

		
		// Setting Viewport
		
		// ndc -> window
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.f, 0.f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.f, 1.f };
		BindViewports(&mViewPort);

		// RenderTarget Set
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	CGraphicDevice::~CGraphicDevice()
	{
	}

	bool CGraphicDevice::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* _Desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr; 
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr; 
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr; 

													// hwnd같이 gpu접근객체
		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
													// 내 그래픽 카드 정보가져옴
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;
													// 전체화면 전환 관리 (swapchain 만들기 위해 필요)
		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
			return false;

		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), _Desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateTexture(D3D11_TEXTURE2D_DESC* _Desc, ID3D11Texture2D** _ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(_Desc, nullptr, _ppTexture2D)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _NumElements, const void* _Bytecode, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(_Desc, _NumElements, _Bytecode, _BytecodeLength, _ppInputLayout)))
		{
			return false;
		}

		return true;
	}


	bool CGraphicDevice::CreateBuffer(D3D11_BUFFER_DESC* _DESC, D3D11_SUBRESOURCE_DATA* _Data, ID3D11Buffer** _Buffer)
	{
		// ram -> gpu 
		// input assembly 단계로 버퍼 넘겨주는행위

		if (FAILED(mDevice->CreateBuffer(_DESC, _Data, _Buffer)))
			return false;

		return true;
	}


	bool CGraphicDevice::CreateShader()
	{
		ID3DBlob* errorBlob = nullptr;

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path(); // 현재 path의 부모 path 얻기
		shaderPath += "\\SHADER_SOURCE\\";

		// Vertex Shader
		std::wstring vsPath(shaderPath.c_str());
		vsPath += L"VSTriangle.hlsl"; // hlsli는 inline 함수로 쓰는것들 모아놓으려고 만든것
		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "VS", "vs_5_0", 0, 0, &renderer::triangleVSBlob, &errorBlob); // hlsl파일의 코드를 그래픽카드 언어로 컴파일 해줌
		mDevice->CreateVertexShader(renderer::triangleVSBlob->GetBufferPointer()
			, renderer::triangleVSBlob->GetBufferSize()
			, nullptr, &renderer::triangleVS);
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}

		// Pixel Shader
		std::wstring psPath(shaderPath.c_str());
		psPath += L"PSTriangle.hlsl"; 
		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "PS", "ps_5_0", 0, 0, &renderer::trianglePSBlob, &errorBlob); 
		mDevice->CreatePixelShader(renderer::trianglePSBlob->GetBufferPointer()
			, renderer::trianglePSBlob->GetBufferSize()
			, nullptr, &renderer::trianglePS);
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}
		
		return true;
	}

	void CGraphicDevice::BindViewports(D3D11_VIEWPORT* _ViewPort)
	{
		mContext->RSSetViewports(1, _ViewPort);
	}

	void CGraphicDevice::BindConstantBuffer(ID3D11Buffer* _Buffer, void* _Data, UINT _Size)
	{
		// gpu에 값 줄거니까 데이터 바꿔서 보내야해
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, _Data, _Size);
		mContext->Unmap(_Buffer, 0);
	}

	
	void CGraphicDevice::SetConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _Buffer)
	{
		switch (_eStage)
		{
		case dru::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)_eType, 1, &_Buffer);
			break;
		default:
			break;
		}
	}

	void CGraphicDevice::Draw()
	{
		// bind resource
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(renderer::triangleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub); // renderer::triangleBuffer와 sub를 연결 후
																				// D3D11_MAPPED_SUBRESOURCE 타입으로 데이터를 매핑한다.
		memcpy(sub.pData, renderer::arrVertex, sizeof(renderer::Vertex) * 4); // sub에 arrVertex 데이터 복사
		mContext->Unmap(renderer::triangleBuffer, 0); // 매핑 해제

		// clear target
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor); // 지우고 다시그림
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0); // 깊이버퍼도 클리어 해줘야해

		// 상수버퍼를 쉐이더에 전달
		SetConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer);

		// resize viewport
		RECT winRect;	
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.f, 0.f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.f, 1.f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());


		// input assembler 버텍스정보를 지정
		UINT vertexSize = sizeof(renderer::Vertex);
		UINT offset = 0;
		mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexSize, &offset); // vertex buffer set
		mContext->IASetIndexBuffer(renderer::triangleIndexBuffer, DXGI_FORMAT_R32_UINT, 0); // index buffer set
		mContext->IASetInputLayout(renderer::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 생성한 쉐이더 세팅
		mContext->VSSetShader(renderer::triangleVS, 0, 0);
		mContext->PSSetShader(renderer::trianglePS, 0, 0);

		mContext->DrawIndexed(6, 0, 0);

		// Draw!!
		mSwapChain->Present(0, 0); // 두번째 인자는 윈도우가 아예 표시되지않을때 렌더링 할까말까 고르는거
	}

}