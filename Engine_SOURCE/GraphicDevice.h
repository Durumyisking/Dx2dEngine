#pragma once

#include "Graphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace dru::graphics
{
	class CGraphicDevice
	{
	public:
		CGraphicDevice(eValidationMode _ValidationMode = eValidationMode::Disabled);
		~CGraphicDevice();

		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* _Desc);
		bool CreateTexture(D3D11_TEXTURE2D_DESC* _Desc, ID3D11Texture2D** _ppTexture2D);


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
	};
}
