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
			 1. Device �� SwapChain�� �����Ѵ�.
			 2. ����ۿ� ������ �������� ����Ÿ�� �並 �����Ѵ�.
			 3. ȭ���� Ŭ���� ������Ѵ�. ����Ʈ�� ��������� �Ѵ�.
			 4. �������Ӹ��� ������ ������ ����Ÿ�� �信 ���������ش�.
			 5. Swapchain�� �̿��Ͽ� ���� ����̽�(���÷���)�� ȭ���� �׷��ش�.
		*/


		HWND hwnd = application.GetHwnd(); // ������ �ڵ� ����

		// Device, Device Context
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG; // ����׸��� ������� ��������� 0
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		// �׳� bool �� ��ȯ���� ���� SUCCEEDED / FAILED�� ����
		// �Լ� ��ȯ �����ϸ� suc �ƴϸ� fail ����
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag
			, nullptr, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf()
			, &FeatureLevel, mContext.GetAddressOf());

		// SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd; // ������ �������� �ڵ�
		swapChainDesc.Windowed = true; // â��� ��üȭ��
		swapChainDesc.BufferCount = 2; // ����� ������ ���۰��� �ִ� 8
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ����Ÿ������ ������
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; // �÷� ���� Ÿ��
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 240; // ������ ���� ����
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // ������ ���� �и�
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		/*
			sample desciption�� Direct3D�� ��Ƽ ���ø� �Ӽ��� �����Ѵ�. 
			��Ƽ ���ø��� ������ �ȼ����� ��� ������ ����Ͽ� ���� �÷��� ���� �ε巴�� �ϴ� ����̴�.
			���÷��� ���õȰ� �´�.
		*/
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		// Get rendertarget for swapchain
		//						0�� ���۰� ����Ÿ��	��ȭ���ϱ��ؽ�ó			������
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
		depthBuffer.ArraySize = 1; // ���̹��� �ϳ��� ���Ŵϱ�

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

													// hwnd���� gpu���ٰ�ü
		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
													// �� �׷��� ī�� ����������
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;
													// ��üȭ�� ��ȯ ���� (swapchain ����� ���� �ʿ�)
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
		// input assembly �ܰ�� ���� �Ѱ��ִ�����

		if (FAILED(mDevice->CreateBuffer(_DESC, _Data, _Buffer)))
			return false;

		return true;
	}


	bool CGraphicDevice::CreateShader()
	{
		ID3DBlob* errorBlob = nullptr;

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path(); // ���� path�� �θ� path ���
		shaderPath += "\\SHADER_SOURCE\\";

		// Vertex Shader
		std::wstring vsPath(shaderPath.c_str());
		vsPath += L"VSTriangle.hlsl"; // hlsli�� inline �Լ��� ���°͵� ��Ƴ������� �����
		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "VS", "vs_5_0", 0, 0, &renderer::triangleVSBlob, &errorBlob); // hlsl������ �ڵ带 �׷���ī�� ���� ������ ����
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
		// gpu�� �� �ٰŴϱ� ������ �ٲ㼭 ��������
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
		mContext->Map(renderer::triangleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub); // renderer::triangleBuffer�� sub�� ���� ��
																				// D3D11_MAPPED_SUBRESOURCE Ÿ������ �����͸� �����Ѵ�.
		memcpy(sub.pData, renderer::arrVertex, sizeof(renderer::Vertex) * 4); // sub�� arrVertex ������ ����
		mContext->Unmap(renderer::triangleBuffer, 0); // ���� ����

		// clear target
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor); // ����� �ٽñ׸�
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0); // ���̹��۵� Ŭ���� �������

		// ������۸� ���̴��� ����
		SetConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer);

		// resize viewport
		RECT winRect;	
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.f, 0.f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.f, 1.f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());


		// input assembler ���ؽ������� ����
		UINT vertexSize = sizeof(renderer::Vertex);
		UINT offset = 0;
		mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexSize, &offset); // vertex buffer set
		mContext->IASetIndexBuffer(renderer::triangleIndexBuffer, DXGI_FORMAT_R32_UINT, 0); // index buffer set
		mContext->IASetInputLayout(renderer::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ������ ���̴� ����
		mContext->VSSetShader(renderer::triangleVS, 0, 0);
		mContext->PSSetShader(renderer::trianglePS, 0, 0);

		mContext->DrawIndexed(6, 0, 0);

		// Draw!!
		mSwapChain->Present(0, 0); // �ι�° ���ڴ� �����찡 �ƿ� ǥ�õ��������� ������ �ұ�� ���°�
	}

}