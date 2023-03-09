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
		mPos = mTrans->GetPosition();

		mPos = CInput::GetMousePosition();

		mTrans->SetPosition(mPos / 100);

	}

	void CCursorScript::fixedUpdate()
	{
	}

	void CCursorScript::render()
	{
	}

}