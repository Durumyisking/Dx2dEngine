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

								// ����̴�			//�Ÿ��
		void SetConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _Buffer); // ���̴��� ������� ������ ������

		void Draw();
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
