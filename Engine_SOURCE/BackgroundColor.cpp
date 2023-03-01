#include "BackgroundColor.h"


namespace dru
{
	CBackgroundColor::CBackgroundColor()
		: mColor(Vector4::Zero)
	{

	}
	CBackgroundColor::~CBackgroundColor()
	{
	}
	void CBackgroundColor::Initialize()
	{
		CGameObj::Initialize();
	}
	void CBackgroundColor::update()
	{
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Color];
		renderer::ColorCB data = {};

		data.RGBA = mColor;
		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);

		CGameObj::update();
	}
	void CBackgroundColor::fixedUpdate()
	{
		CGameObj::fixedUpdate();
	}
	void CBackgroundColor::render()
	{
		CGameObj::render();
	}
}
