#include "Boss.h"
#include "BossScript.h"

namespace dru
{
	CBoss::CBoss()
		: mHp(2)
		, mMaxHp(2)
	{
		SetLayerType(eLayerType::Boss);

		CRigidBody* rigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);
	}

	CBoss::~CBoss()
	{
	}

	void CBoss::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CBoss::update()
	{
		CLiveGameObj::update();
	}

	void CBoss::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBoss::render()
	{
		CLiveGameObj::render();
	}

	void CBoss::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

	void CBoss::Disable()
	{
		GetScript<CBossScript>()->Reset();
	}

	bool CBoss::IsDeadState()
	{
		return GetScript<CBossScript>()->IsDead();
	}

}