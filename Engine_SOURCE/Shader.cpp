#include "Shader.h"
#include "GraphicDevice.h"
#include "Renderer.h"

namespace dru
{
	CShader::CShader()
		: CResource(eResourceType::GraphicShader)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, mRSType(eRasterizerType::SolidBack)
		, mDSType(eDepthStencilType::Less)
		, mBSType(eBlendStateType::AlphaBlend)
		, mCurrentStage(eShaderStage::End)
	{
	}
	CShader::~CShader()
	{
	}

	HRESULT CShader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}



	void CShader::Create(graphics::eShaderStage _eStage, const std::wstring& _Path, const std::string& _funcName)
	{
		mErrorBlob = nullptr;

		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\..\\SHADER_SOURCE\\";

		std::wstring shaderPath(path.c_str());
		shaderPath += _Path;


		switch (_eStage)
		{
		case dru::graphics::eShaderStage::VS:
			CreateVS(shaderPath, _funcName);
			break;
		case dru::graphics::eShaderStage::HS:
			CreateHS(shaderPath, _funcName);
			break;
		case dru::graphics::eShaderStage::DS:
			CreateDS(shaderPath, _funcName);
			break;
		case dru::graphics::eShaderStage::GS:	
			CreateGS(shaderPath, _funcName);
			break;
		case dru::graphics::eShaderStage::PS:
			CreatePS(shaderPath, _funcName);
			break;
		case dru::graphics::eShaderStage::CS:
			break;
		case dru::graphics::eShaderStage::End:
			break;
		default:
			break;
		}

	}

	void CShader::CreateVS(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
			mErrorBlob = nullptr;
		}
		
		graphics::GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
			, mVSBlob->GetBufferSize()
			, nullptr
			, mVS.GetAddressOf());

	}

	void CShader::CreateHS(const std::wstring& _Path, const std::string& _funcName)
	{

	}

	void CShader::CreateDS(const std::wstring& _Path, const std::string& _funcName)
	{

	}

	void CShader::CreateGS(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "gs_5_0", 0, 0, mGSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
			mErrorBlob = nullptr;
		}


		GetDevice()->CreateGeometryShader(mGSBlob->GetBufferPointer()
			, mGSBlob->GetBufferSize()
			, nullptr
			, mGS.GetAddressOf());
	}

	void CShader::CreatePS(const std::wstring& _Path, const std::string& _funcName)
	{
		D3DCompileFromFile(_Path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

		if (mErrorBlob)
		{
			OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			mErrorBlob->Release();
			mErrorBlob = nullptr;
		}

		graphics::GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
			, mPSBlob->GetBufferSize()
			, nullptr
			, mPS.GetAddressOf());
	}


	void CShader::Bind()
	{
		graphics::GetDevice()->BindPrimitiveTopology(mTopology);
		graphics::GetDevice()->BindInputLayout(mInputLayout.Get());

		graphics::GetDevice()->BindVS(mVS.Get(), nullptr, 0);
		graphics::GetDevice()->BindHS(mHS.Get(), nullptr, 0);
		graphics::GetDevice()->BindDS(mDS.Get(), nullptr, 0);
		graphics::GetDevice()->BindGS(mGS.Get(), nullptr, 0);
		graphics::GetDevice()->BindPS(mPS.Get(), nullptr, 0);

		Microsoft::WRL::ComPtr<ID3D11RasterizerState>	rs = renderer::rasterizerState[(UINT)mRSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	ds = renderer::depthStencilState[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState>		bs = renderer::blendState[(UINT)mBSType];

		GetDevice()->BindRasterizerState(rs.Get());
		GetDevice()->BindDepthStencilState(ds.Get());
		GetDevice()->BindBlendState(bs.Get());


	}

}