#include "Shader.h"



namespace dru
{
	HRESULT CShader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool CShader::Create(graphics::eShaderStage _eStage, const std::wstring& _Path, const std::wstring& _funcName)
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += "\\SHADER_SOURCE\\";
		std::wstring Path(shaderPath.c_str());
		Path += L"_Path";


		switch (_eStage)
		{
		case dru::graphics::eShaderStage::VS:
			CreateVS(Path, _funcName);
			break;
		case dru::graphics::eShaderStage::HS:
			break;
		case dru::graphics::eShaderStage::DS:
			break;
		case dru::graphics::eShaderStage::GS:
			break;
		case dru::graphics::eShaderStage::PS:
			CreatePS(Path, _funcName);
			break;
		case dru::graphics::eShaderStage::CS:
			break;
		case dru::graphics::eShaderStage::End:
			break;
		default:
			break;
		}

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
			mErrorBlob = nullptr;
		}

		return true;
	}

	void CShader::CreateVS(const std::wstring& _Path, const std::wstring& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, (LPCSTR)_funcName.c_str(), "vs_5_0", 0, 0, &mVSBlob, &mErrorBlob);

		graphics::GetDevice()->GetdxDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
			, mVSBlob->GetBufferSize()
			, nullptr, &mVS);

	}

	void CShader::CreateHS(const std::wstring& _Path, const std::wstring& _funcName)
	{

	}

	void CShader::CreateDS(const std::wstring& _Path, const std::wstring& _funcName)
	{

	}

	void CShader::CreateGS(const std::wstring& _Path, const std::wstring& _funcName)
	{

	}

	void CShader::CreatePS(const std::wstring& _Path, const std::wstring& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, (LPCSTR)_funcName.c_str(), "ps_5_0", 0, 0, &mPSBlob, &mErrorBlob);
		graphics::GetDevice()->GetdxDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
			, mPSBlob->GetBufferSize()
			, nullptr, &mPS);
	}


	void CShader::Update()
	{
		graphics::GetDevice()->GetDeviceContext()->IASetInputLayout(mInputLayout.Get());
		graphics::GetDevice()->GetDeviceContext()->IASetPrimitiveTopology(mTopology);

		graphics::GetDevice()->GetDeviceContext()->VSSetShader(mVS.Get(), 0, 0);
		graphics::GetDevice()->GetDeviceContext()->PSSetShader(mPS.Get(), 0, 0);
	}

}