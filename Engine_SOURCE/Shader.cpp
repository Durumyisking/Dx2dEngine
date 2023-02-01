#include "Shader.h"


namespace dru
{
	CShader::CShader()
		: CResource(eResourceType::GraphicShader)
		, mTopology (D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	CShader::~CShader()
	{
	}

	HRESULT CShader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}


	void CShader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _NumElements)
	{
		graphics::GetDevice()->CreateInputLayout(_Desc, _NumElements
			, mVSBlob->GetBufferPointer()
			, mVSBlob->GetBufferSize()
			, mInputLayout.GetAddressOf());

	}

	void CShader::Create(graphics::eShaderStage _eStage, const std::wstring& _Path, const std::string& _funcName)
	{
		mErrorBlob = nullptr;

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += "\\SHADER_SOURCE\\";
		std::wstring Path(shaderPath.c_str());
		Path += _Path;


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

	}

	void CShader::CreateVS(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		graphics::GetDevice()->GetdxDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
			, mVSBlob->GetBufferSize()
			, nullptr, mVS.GetAddressOf());

	}

	void CShader::CreateHS(const std::wstring& _Path, const std::string& _funcName)
	{

	}

	void CShader::CreateDS(const std::wstring& _Path, const std::string& _funcName)
	{

	}

	void CShader::CreateGS(const std::wstring& _Path, const std::string& _funcName)
	{

	}

	void CShader::CreatePS(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, (LPCSTR)_funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());
		graphics::GetDevice()->GetdxDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
			, mPSBlob->GetBufferSize()
			, nullptr, mPS.GetAddressOf());
	}
	

	void CShader::Bind()
	{
		graphics::GetDevice()->BindPrimitiveTopology(mTopology);
		graphics::GetDevice()->BindInputLayout(mInputLayout);

		graphics::GetDevice()->BindVS(mVS, nullptr, 0);
		graphics::GetDevice()->BindPS(mPS, nullptr, 0);
	}

}