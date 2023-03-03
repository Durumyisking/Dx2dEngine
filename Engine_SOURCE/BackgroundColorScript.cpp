#include "BackgroundColorScript.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "BackgroundColor.h"

namespace dru
{
	CBackgroundColorScript::CBackgroundColorScript()
		: mColor(math::Vector4::Zero)
	{
	}

	CBackgroundColorScript::~CBackgroundColorScript()
	{
	}

	void CBackgroundColorScript::Initialize()
	{
	}

	void CBackgroundColorScript::update()
	{
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Color];
		renderer::ColorCB data = {};

		data.RGBA = mColor;

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);
	}

	void CBackgroundColorScript::fixedUpdate()
	{
	}

	void CBackgroundColorScript::render()
	{
	}

}