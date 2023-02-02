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
								// ����̴�			//�Ÿ��
		void BindSamplers(eShaderStage _Stage, UINT _Slot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplerState);
		void BindSamplers(UINT _Slot, UINT _NumSamplers, ID3D11SamplerState** _ppSamplerState);


		void SetConstantBuffer(eShaderStage _Stage, enums::eCBType _Type, ID3D11Buffer* _Buffer); // ���̴��� ������� ������ ������

		void Draw();
		void DrawIndexed(UINT _IndexCount, UINT StartIndexLocation, INT BaseVertexLocation = 0);

		void Clear();
		void AdjustViewPorts();
		void Present();

		Microsoft::WRL::ComPtr <ID3D11Device>		 GetdxDevice() const { return mDevice; }
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> GetDeviceContext() const { return mContext; }


	private:
		// GPU ��ü ���� �׷���ī��� ����Ǵ� �⺻���� ��ü 
		Microsoft::WRL::ComPtr <ID3D11Device> mDevice; // ComPtr : �� ����� ������ �ִ� Ŭ������ �Ҹ��ڰ� ȣ��ɶ� �ش� ����� Ÿ���� �Ҹ��ڰ� �ڵ����� ȣ��ȴ�.
		// GPU read write ����̽��� ���� �������� �ʰ� �̰�ü�� ���ؼ� gpu�� ����� ������.
		// ����̽��� ������ �κп� ������ �Ȱ��� �Լ���� �����Ǿ��ִ�.
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> mContext;

		// ���������� �׷����� ��ȭ��
		Microsoft::WRL::ComPtr <ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr <ID3D11RenderTargetView> mRenderTargetView; // �굵 context�� ��������
		Microsoft::WRL::ComPtr <ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr <ID3D11DepthStencilView> mDepthStencilView; // �굵 context�� ��������

		// ȭ�鿡 ���������� �׷����� 
		// �����(Frame Buffer)�� �����ϰ�, ������ ȭ�鿡 ������ �ϴ� 
		// ������ ����ϴ� ��ü
		Microsoft::WRL::ComPtr <IDXGISwapChain> mSwapChain;

		//�ؽ�ó �ε��Ҷ� ���ȴ�.
		//ID3D11SamplerState* mSampler[];

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice*& GetDevice()
	{
		static CGraphicDevice* device = nullptr; // static�̶� ó�� �ѹ��� �ʱ�ȭ �ϰ� �㿡�� ��������
		return device;
	}
}	
