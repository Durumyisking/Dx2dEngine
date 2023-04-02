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

		Vector3 camPos = renderer::mainCamera->GetOwner()->GetPos();
//		mPos /= 100.f;
		//mPos.x += camPos.x;
		//mPos.y += camPos.y;
		mTrans->SetPosition(mPos / 100.f);

	}

	void CCursorScript::fixedUpdate()
	{
	}

	void CCursorScript::render()
	{
	}

}