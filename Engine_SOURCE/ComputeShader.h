#pragma once
#include "Graphics.h"
#include "Resource.h"

namespace dru::graphics
{
	class CComputeShader : public CResource
	{
	public:
		CComputeShader(UINT threadGroupX, UINT threadGroupY, UINT threadGroupZ);
		CComputeShader();
		virtual ~CComputeShader();

		virtual HRESULT Load(const std::wstring& path);
		void Create(const std::wstring& _Path, const std::string& _funcName);
		void OnExcute();

		virtual void Bind();
		virtual void Clear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob>			mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

		Microsoft::WRL::ComPtr<ID3DBlob>			mPSBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;
		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;


		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;


		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;
	};

}

