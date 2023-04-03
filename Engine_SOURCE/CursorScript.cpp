#include "CursorScript.h"
#include "Input.h"
#include "GameObj.h"

namespace dru
{
	CCursorScript::CCursorScript()
		: CScript(),
		mTrans(nullptr),
		mPos{},
		mRot{}
	{
	}

	CCursorScript::~CCursorScript()
	{
	}

	void CCursorScript::Initialize()
	{
		mTrans = GetOwner()->GetComponent<CTransform>();
	}

	void CCursorScript::update()
	{
	

	}

	void CCursorScript::fixedUpdate()
	{
		mPos = CInput::GetMousePosition();
		Vector3 newpos = mPos / 100.f;

		mTrans->SetPosition(newpos);
	}

	void CCursorScript::render()
	{
	}

}