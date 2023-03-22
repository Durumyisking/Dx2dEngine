#include "ComputeShader.h"
#include "GraphicDevice.h"

namespace dru::graphics
{
	CComputeShader::CComputeShader()
		: CResource(eResourceType::ComputeShader)
		, mCSBlob(nullptr)
		, mCS(nullptr)
		, mThreadGroupCountX(0)
		,mThreadGroupCountY(0)
		,mThreadGroupCountZ(0)
		,mGroupX(0)
		,mGroupY(0)
		,mGroupZ(0)
	{
		mThreadGroupCountX = 32;
		mThreadGroupCountY = 32;
		mThreadGroupCountZ = 1;
	}

	CComputeShader::~CComputeShader()
	{
	}

	HRESULT CComputeShader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void CComputeShader::Create(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "cs_5_0", 0, 0, mCSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		graphics::GetDevice()->CreateComputeShader(mCSBlob->GetBufferPointer()
			, mCSBlob->GetBufferSize()
			, nullptr
			, mCS.GetAddressOf());


	}

	void CComputeShader::OnExcute()
	{
		Bind();

		GetDevice()->BindCS(mCS.Get(), nullptr, 0);
		GetDevice()->Dispatch(mThreadGroupCountX, mThreadGroupCountY, mThreadGroupCountZ);

		Clear();
	}

	void CComputeShader::Bind()
	{
	}

	void CComputeShader::Clear()
	{
	}

}