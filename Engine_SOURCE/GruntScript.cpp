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
			if (mTarget && !mbDead)
			{
				if (mAttackTimer >= 1.f)
				{
					makeSlash({ 7296.f, 0.f }, { 64.f, 64.f }, 4, { 64.f, 64.f });
	
				}

			}
		}

		CMonsterScript::attack();
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
}
