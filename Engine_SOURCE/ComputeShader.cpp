#include "ComputeShader.h"
#include "GraphicDevice.h"

namespace dru::graphics
{
	CComputeShader::CComputeShader(UINT threadGroupX, UINT threadGroupY, UINT threadGroupZ)
		: CResource(eResourceType::ComputeShader)
		, mCSBlob(nullptr)
		, mCS(nullptr)
		, mThreadGroupCountX(threadGroupX)
		, mThreadGroupCountY(threadGroupY)
		, mThreadGroupCountZ(threadGroupZ)
		, mGroupX(0)
		, mGroupY(0)
		, mGroupZ(0)
	{
	}

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

		mErrorBlob = nullptr;

		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\..\\SHADER_SOURCE\\";

		std::wstring shaderPath(path.c_str());
		shaderPath += _Path;


		D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "cs_5_0", 0, 0, mCSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
			mErrorBlob = nullptr;
		}


		graphics::GetDevice()->CreateComputeShader(mCSBlob->GetBufferPointer()
			, mCSBlob->GetBufferSize()
			, nullptr
			, mCS.GetAddressOf());

	}



	void CComputeShader::OnExcute()
	{
		Bind();	

		GetDevice()->BindCS(mCS.Get(), nullptr, 0);
		// 컴퓨트 쉐이더 돌릴거임, 인자로 쓰레드 그룹 전달
		GetDevice()->Dispatch(mGroupX, mGroupY, mGroupZ);

		Clear();
	}

	void CComputeShader::Bind()
	{
	}

	void CComputeShader::Clear()
	{
	}

}