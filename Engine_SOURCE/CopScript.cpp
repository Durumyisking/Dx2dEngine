#include "CopScript.h"

namespace dru
{
	CCopScript::CCopScript()
	{
	}
	CCopScript::~CCopScript()
	{
	}
	void CCopScript::Initialize()
	{
		
		CMonsterScript::Initialize();
	}
	void CCopScript::update()
	{
		CMonsterScript::update();
	}
	void CCopScript::fixedUpdate()
	{
		CMonsterScript::fixedUpdate();
	}
	void CCopScript::render()
	{
		CMonsterScript::render();
	}
	void CCopScript::attack()
	{
		if (mState[(UINT)eMonsterState::Attack] == true)
		{


			CMonsterScript::attack();
		}
	}
	void CCopScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionEnter(_oppo);
	}
	void CCopScript::OnCollision(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollision(_oppo);
	}
	void CCopScript::OnCollisionExit(CCollider2D* _oppo)
	{
		CMonsterScript::OnCollisionExit(_oppo);
	}
}
