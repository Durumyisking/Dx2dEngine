#include "CursorScript.h"
#include "Input.h"
#include "GameObj.h"

namespace dru
{
	CCursorScript::CCursorScript()
	{
	}

	CCursorScript::~CCursorScript()
	{
	}

	void CCursorScript::Initialize()
	{
	}

	void CCursorScript::update()
	{

		mMousePos = CInput::GetMousePosition();
		GetOwner()->SetPos(mMousePos);

	}

	void CCursorScript::fixedUpdate()
	{
	}

	void CCursorScript::render()
	{
	}

}