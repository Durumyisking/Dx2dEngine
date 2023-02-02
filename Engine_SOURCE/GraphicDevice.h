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
		bool CreateSampler(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState);


		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
		void BindInputLayout(Microsoft::WRL::ComPtr <ID3D11InputLayout> _InputLayout);
		void BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindVS(Microsoft::WRL::ComPtr <ID3D11VertexShader> _VS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst);
		void BindHS(Microsoft::WRL::ComPtr <ID3D11HullShader> _HS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst);
		void BindDS(Microsoft::WRL::ComPtr <ID3D11DomainShader> _DS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst);
		void BindGS(Microsoft::WRL::ComPtr <ID3D11GeometryShader> _GS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst);
		void BindPS(Microsoft::WRL::ComPtr <ID3D11PixelShader> _PS, ID3D11ClassInstance* const* _ClassInst, UINT NumClassInst);
		void BindViewports(D3D11_VIEWPORT* _ViewPort);
		void BindConstantBuffer(ID3D11Buffer* _Buffer, void* _Data, UINT _Size);
		void SetShaderResource(eShaderStage _Stage, UINT _Slot, ID3D11ShaderResourceView* const* _ppShaderResourceViews);
								// 어떤쉐이더			//어떤타입
		void BindSamplers(eShaderStage _Stage, UINT _Slot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplerState);
		void BindSamplers(UINT _Slot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplerState);


		void SetConstantBuffer(eShaderStage _Stage, enums::eCBType _Type, ID3D11Buffer* _Buffer); // 쉐이더에 상수버퍼 데이터 보내줌

		void Draw();
		void DrawIndexed(UINT _IndexCount, UINT StartIndexLocation, INT BaseVertexLocation = 0);

		void Clear();
		void AdjustViewPorts();
		void Present();

		Microsoft::WRL::ComPtr <ID3D11Device>		 GetdxDevice() const { return mDevice; }
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> GetDeviceContext() const { return mContext; }


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
