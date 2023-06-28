#include "FontWrapper.h"
#include "GraphicDevice.h"
#include "Renderer.h"

namespace dru
{
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> renderer::samplerState[];

	IFW1Factory* CFontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* CFontWrapper::mFontWrapper = nullptr;

	bool CFontWrapper::Initialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = graphics::GetDevice()->GetID3D11Device();
		if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper)))
			return false;

		return true;
	}

	void CFontWrapper::DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
	{
		//RGB();
		ID3D11DeviceContext* pContext = graphics::GetDevice()->GetDeviceContext().Get();
		mFontWrapper->DrawString(
			pContext,
			str, // String
			size,// Font size
			x,// X position
			y,// Y position
			rgb,// Text color, 0xAaBbGgRr
			0      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);

		graphics::GetDevice()->BindSamplers((UINT)graphics::eSamplerType::Point, 1, renderer::samplerState[(UINT)eSamplerType::Point].GetAddressOf());
	}

	void CFontWrapper::DrawFont(const wchar_t* str, dru::math::Vector3 pos, float size, UINT rgb)
	{
		POINT pt = WorldToWindowPos(pos);

		//RGB();
		ID3D11DeviceContext* pContext = graphics::GetDevice()->GetDeviceContext().Get();
		mFontWrapper->DrawString(
			pContext,
			str, 
			size,
			pt.x,
			pt.y,
			rgb,
			0 
		);

		graphics::GetDevice()->BindSamplers((UINT)graphics::eSamplerType::Point, 1, renderer::samplerState[(UINT)eSamplerType::Point].GetAddressOf());
	}

	void CFontWrapper::Release()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}
}