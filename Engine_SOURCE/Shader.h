#pragma once
#include "Resource.h"
#include "GraphicDevice.h"

namespace dru
{
	class CShader : CResource
	{
	public:
		CShader();
		~CShader();

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		bool Create(graphics::eShaderStage _eStage, const std::wstring& _Path, const std::wstring& _funcName);

		void CreateVS(const std::wstring& _Path, const std::wstring& _funcName);
		void CreateHS(const std::wstring& _Path, const std::wstring& _funcName);
		void CreateDS(const std::wstring& _Path, const std::wstring& _funcName);
		void CreateGS(const std::wstring& _Path, const std::wstring& _funcName);
		void CreatePS(const std::wstring& _Path, const std::wstring& _funcName);

		void Update();

		ID3D11InputLayout* GetInputLayOut() const { return mInputLayout.Get(); }
//		ID3D11InputLayout** GetInputLayOutAddr() const { return mInputLayout.GetAddressOf(); }

	private:
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		graphics::eShaderStage mCurrentStage;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;

		// Shaders
		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

	};

}


