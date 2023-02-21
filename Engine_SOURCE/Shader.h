#pragma once
#include "Resource.h"
#include "Graphics.h"

namespace dru
{
	using namespace graphics;
	class CShader : public CResource
	{
	public:
		CShader();
		virtual ~CShader();

		virtual HRESULT Load(const std::wstring& path) override;


		void Create(graphics::eShaderStage _eStage, const std::wstring& _Path, const std::string& _funcName);
		void Bind();
		ID3D11InputLayout* GetInputLayOut() { return mInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddr()  { return mInputLayout.GetAddressOf(); }

		void* GetVSBlobBufferPointer() { return mVSBlob->GetBufferPointer(); }
		SIZE_T GetVSBlobBufferSize() { return mVSBlob->GetBufferSize(); }

		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { mTopology = _Topology; }

		void SetRSState(eRasterizerType _state) { mRSType = _state; }
		void SetDSState(eDepthStencilType _state) { mDSType = _state; }
		void SetBSState(eBlendStateType _state) { mBSType = _state; }

	private:
		void CreateVS(const std::wstring& _Path, const std::string& _funcName);
		void CreateHS(const std::wstring& _Path, const std::string& _funcName);
		void CreateDS(const std::wstring& _Path, const std::string& _funcName);
		void CreateGS(const std::wstring& _Path, const std::string& _funcName);
		void CreatePS(const std::wstring& _Path, const std::string& _funcName);
		


	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		graphics::eShaderStage mCurrentStage;


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

		eRasterizerType		mRSType;
		eDepthStencilType	mDSType;
		eBlendStateType		mBSType;

	};

}


