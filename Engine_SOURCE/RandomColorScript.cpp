#include "RandomColorScript.h"


namespace dru
{
	CRandomColorScript::CRandomColorScript()
	{
	}

	CRandomColorScript::~CRandomColorScript()
	{
	}

	void CRandomColorScript::Initialize()
	{
	}

	void CRandomColorScript::update()
	{
	}

	void CRandomColorScript::fixedUpdate()
	{
	}

	void CRandomColorScript::render()
	{
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Material];
		renderer::MaterialCB data = {};

		int* p = new int;
		srand((unsigned int)p);

		data.fData2 = (float)(rand() % 10001) / 10000;


		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::CS);
	}

}