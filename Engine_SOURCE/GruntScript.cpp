#include "GruntScript.h"

namespace dru
{
	CGruntScript::CGruntScript()
	{
	}
	CGruntScript::~CGruntScript()
	{
	}
	void CGruntScript::Initialize()
	{

		mAnimator->GetFrameEvent(GetOwner()->GetName() + L"_Attack", 4) = std::bind(&CGruntScript::attackFrame2, this);

		CMonsterScript::Initialize();
	}
	void CGruntScript::update()
	{

		CMonsterScript::update();
	}
	void CGruntScript::fixedUpdate()
	{

		CMonsterScript::fixedUpdate();
	}
	void CGruntScript::render()
	{

		CMonsterScript::render();
	
	}
	void CGruntScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{
			CMonsterScript::attack();
		}
	}

	void CGruntScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}
	void CGruntScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}
	void CGruntScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}
	void CGruntScript::attackFrame2()
	{
		makeSlash({ 7296.f, 0.f }, { 64.f, 64.f }, 4, { 64.f, 64.f });
	}
}
