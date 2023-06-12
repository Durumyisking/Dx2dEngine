#include "GraphicDevice.h"
#include "Application.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Input.h"
#include "Texture.h"
#include "Resources.h"

#include <wincodec.h>
//#include <winrt/Windows.Storage.Pickers.h>
//#include <winrt/Windows.Storage.Streams.h>
//#include <winrt/Windows.Foundation.Collections.h>

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

		graphics::GetDevice() = this;

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
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;// 프레임 비율 분자
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

		mRenderTargetTexture = std::make_shared<CTexture>();

		Microsoft::WRL::ComPtr <ID3D11Texture2D> renderTarget;
		// Get rendertarget for swapchain
		//						0번 버퍼가 렌더타겟							렌더타겟 포인터
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)renderTarget.GetAddressOf());
		mRenderTargetTexture->Create(renderTarget);
		CResources::Insert<CTexture>(L"RenderTargetTexture", mRenderTargetTexture);
		// Create Rendertarget View

		mDepthStencilBufferTexture = std::make_shared<CTexture>();
		mDepthStencilBufferTexture->Create(1600, 900, DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL);
	
		// Setting Viewport		
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.f, 0.f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.f, 1.f };
		BindViewports(&mViewPort);

		// RenderTarget Set
		mContext->OMSetRenderTargets(1, mRenderTargetTexture->GetRTV().GetAddressOf(), mDepthStencilBufferTexture->GetDSV().Get());
	}

	CGraphicDevice::~CGraphicDevice()
	{
		renderer::release();

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

	bool CGraphicDevice::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{

		if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDSView)
	{
		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDSView)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
	{
		if (FAILED(mDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader)
	{
		if (FAILED(mDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader)))
			return false;

		return true;
	}



	bool CGraphicDevice::CreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(_pSamplerDesc, _ppSamplerState)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateRasterizerState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(_pRasterizerDesc, _ppRasterizerState)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc, ID3D11DepthStencilState** _ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(_pDepthStencilDesc, _ppDepthStencilState)))
			return false;

		return true;
	}

	bool CGraphicDevice::CreateBlendState(const D3D11_BLEND_DESC* _pBlendStateDesc, ID3D11BlendState** _ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(_pBlendStateDesc, _ppBlendState)))
			return false;

		return true;
	}


	void CGraphicDevice::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
	{
		mContext->IASetPrimitiveTopology(_Topology);
	}

	void CGraphicDevice::BindInputLayout(ID3D11InputLayout* _InputLayout)
	{
		mContext->IASetInputLayout(_InputLayout	);
	}

	void CGraphicDevice::BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets); // vertex buffer set
	}

	void CGraphicDevice::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset); // index buffer set
	}

	void CGraphicDevice::BindVS(ID3D11VertexShader* _VS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->VSSetShader(_VS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::BindHS(ID3D11HullShader* _HS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->HSSetShader(_HS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::BindDS(ID3D11DomainShader* _DS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->DSSetShader(_DS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::BindGS(ID3D11GeometryShader* _GS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->GSSetShader(_GS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::BindPS(ID3D11PixelShader* _PS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->PSSetShader(_PS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::BindCS(ID3D11ComputeShader* _CS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst)
	{
		mContext->CSSetShader(_CS, _ClassInst, NumClassInst);
	}

	void CGraphicDevice::Dispatch(UINT _mThreadGroupCountX, UINT _mThreadGroupCountY, UINT _mThreadGroupCountZ)
	{
		mContext->Dispatch(_mThreadGroupCountX, _mThreadGroupCountY, _mThreadGroupCountZ);
	}



	void CGraphicDevice::BindViewports(D3D11_VIEWPORT* _ViewPort)
	{
		mContext->RSSetViewports(1, _ViewPort);
	}

	void CGraphicDevice::GetData(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_READ, 0, &sub);
		memcpy(data, sub.pData, size);
		mContext->Unmap(buffer, 0);
	}

	void CGraphicDevice::SetData(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void CGraphicDevice::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
	{
		mContext->CopyResource(pDstResource, pSrcResource);
	}

	void CGraphicDevice::BindBuffer(ID3D11Buffer* _Buffer, void* _Data, UINT _Size)
	{
		// gpu에 값 줄거니까 데이터 바꿔서 보내야해
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub); // 다른 애들이 Buffer를 사용 못하게 점유하도록 함		
		memcpy(sub.pData, _Data, _Size); // GPU로 값 복사해줌
		mContext->Unmap(_Buffer, 0); // 점유 해제
	}

	void CGraphicDevice::ClearConstantBuffer(ID3D11Buffer* buffer, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memset(sub.pData, 0, size);
		mContext->Unmap(buffer, 0);
	}

	void CGraphicDevice::BindConstantBuffer(eShaderStage _Stage, eCBType _Type, ID3D11Buffer* _Buffer)
	{
		switch (_Stage)
		{
		case dru::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		case dru::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)_Type, 1, &_Buffer);
			break;
		default:
			break;
		}
	}

	void CGraphicDevice::BindShaderResource(eShaderStage _Stage, UINT _Slot, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
	{
		switch (_Stage)
		{
		case dru::graphics::eShaderStage::VS:
			mContext->VSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		case dru::graphics::eShaderStage::HS:
			mContext->HSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		case dru::graphics::eShaderStage::DS:
			mContext->DSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		case dru::graphics::eShaderStage::GS:
			mContext->GSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		case dru::graphics::eShaderStage::PS:
			mContext->PSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		case dru::graphics::eShaderStage::CS:
			mContext->CSSetShaderResources(_Slot, 1, _ppShaderResourceViews);
			break;
		default:
			break;
		}
	}

	void CGraphicDevice::BindUnorderedAccessView(UINT _Slot, UINT _NumUAVs, ID3D11UnorderedAccessView* const* _ppUnorderedAccessView, const UINT* _pUAVInitialCount)
	{
		mContext->CSSetUnorderedAccessViews(_Slot, _NumUAVs, _ppUnorderedAccessView, _pUAVInitialCount);
	}

	void CGraphicDevice::BindSamplers(eShaderStage _Stage, UINT _Slot, UINT _NumSamplers, ID3D11SamplerState* const* _ppSamplerState)
	{
		switch (_Stage)
		{
		case dru::graphics::eShaderStage::VS:
			mContext->VSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
			break;
		case dru::graphics::eShaderStage::HS:
			mContext->HSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
			break;
		case dru::graphics::eShaderStage::DS:
			mContext->DSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
			break;
		case dru::graphics::eShaderStage::GS:
			mContext->GSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
			break;
		case dru::graphics::eShaderStage::PS:
			mContext->PSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
			break;
		default:
			break;
		}
	}

	void CGraphicDevice::BindSamplers(UINT _Slot, UINT _NumSamplers, ID3D11SamplerState* const* _ppSamplerState)
	{
		mContext->VSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
		mContext->HSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
		mContext->DSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
		mContext->GSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);
		mContext->PSSetSamplers(_Slot, _NumSamplers, _ppSamplerState);		
	}

	void CGraphicDevice::BindRasterizerState(ID3D11RasterizerState* _pRasterizerState)
	{
		mContext->RSSetState(_pRasterizerState);
	}

	void CGraphicDevice::BindDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
	{
		mContext->OMSetDepthStencilState(_pDepthStencilState, 0);
	}

	void CGraphicDevice::BindBlendState(ID3D11BlendState* _pBlendState)
	{
		mContext->OMSetBlendState(_pBlendState, nullptr, 0xffffff);
	}


	void CGraphicDevice::Clear()
	{
		// clear target
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetTexture->GetRTV().Get(), backgroundColor); // 지우고 다시그림
		mContext->ClearDepthStencilView(mDepthStencilBufferTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0); // 깊이버퍼도 클리어 해줘야해
	}

	void CGraphicDevice::AdjustViewPorts()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.f, 0.f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.f, 1.f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetTexture->GetRTV().GetAddressOf(), mDepthStencilBufferTexture->GetDSV().Get());
	}

	void CGraphicDevice::Draw()
	{
		mContext->Draw(0, 0);
	}


	void CGraphicDevice::DrawIndexed(UINT _IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexed(_IndexCount, StartIndexLocation, StartIndexLocation);
	}

	void CGraphicDevice::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
	{
		mContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
	}

	void CGraphicDevice::Present()
	{
		mSwapChain->Present(0, 0); // 두번째 인자는 윈도우가 아예 표시되지않을때 렌더링 할까말까 고르는거
		//mSwapChain->Present(1, 0); // 수직동기화 on
	}



}