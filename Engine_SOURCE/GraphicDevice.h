#pragma once
#include "Graphics.h"

namespace dru::graphics
{
	class CGraphicDevice
	{
	public:
		CGraphicDevice(eValidationMode _ValidationMode = eValidationMode::Disabled);
		~CGraphicDevice();

		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* _Desc);
		bool CreateTexture(D3D11_TEXTURE2D_DESC* _Desc, ID3D11Texture2D** _ppTexture2D);
		bool CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _NumElements, const void* _Bytecode, SIZE_T _BytecodeLength, ID3D11InputLayout** _ppInputLayout);
		bool CreateBuffer(D3D11_BUFFER_DESC* _DESC, D3D11_SUBRESOURCE_DATA* _Data, ID3D11Buffer** _Buffer);
		bool CreateShader();
		void BindViewports(D3D11_VIEWPORT* _ViewPort);
		void BindConstantBuffer(ID3D11Buffer* _Buffer, void* _Data, UINT _Size);

								// 어떤쉐이더			//어떤타입
		void SetConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _Buffer); // 쉐이더에 상수버퍼 데이터 보내줌

		void Draw();
	private:
		// GPU 객체 생성 그래픽카드와 연결되는 기본적인 객체 
		Microsoft::WRL::ComPtr <ID3D11Device> mDevice; // ComPtr : 이 멤버를 가지고 있는 클래스의 소멸자가 호출될때 해당 멤버의 타입의 소멸자가 자동으로 호출된다.
		// GPU read write 디바이스에 직접 접근하지 않고 이객체를 통해서 gpu에 명령을 내린다.
		// 디바이스의 위험한 부분에 영향이 안가는 함수들로 구성되어있다.
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> mContext;

		// 최종적으로 그려지는 도화지
		Microsoft::WRL::ComPtr <ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr <ID3D11RenderTargetView> mRenderTargetView; // 얘도 context와 같은개념
		Microsoft::WRL::ComPtr <ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr <ID3D11DepthStencilView> mDepthStencilView; // 얘도 context와 같은개념

		// 화면에 최종적으로 그려지는 
		// 백버퍼(Frame Buffer)를 관리하고, 실제로 화면에 렌더링 하는 
		// 역할을 담당하는 객체
		Microsoft::WRL::ComPtr <IDXGISwapChain> mSwapChain;

		//텍스처 로딩할때 사용된다.
		//ID3D11SamplerState* mSampler[];

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice*& GetDevice()
	{
		static CGraphicDevice* device = nullptr; // static이라서 처음 한번만 초기화 하고 담에는 안지나감
		return device;
	}
}	
