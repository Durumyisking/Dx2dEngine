#include "GraphicDevice.h"
#include "Application.h"

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
		swapChainDesc.BufferCount = 2; // ����� ������ ���۰��� �ִ� 8��

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

		D3D11_TEXTURE2D_DESC depthBuffer = {};
		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Usage = D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;
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
		return true;
	}

	void CGraphicDevice::Draw()
	{
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor); // ����� �ٽñ׸�

		mSwapChain->Present(1, 0); // �ι�° ���ڴ� �����찡 �ƿ� ǥ�õ��������� ������ �ұ�� ���°�
	}

}