#include "Monster.h"
#include "Object.h"
#include "TimeMgr.h"
#include "MonsterRayScript.h"

namespace dru
{
	CMonster::CMonster()
		: mRay(nullptr)
		, mRayScale(Vector3::Zero)
	{
		SetLayerType(eLayerType::Monster);

		CRigidBody* rigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);

		CAudioSource* audioSource = AddComponent<CAudioSource>(eComponentType::AudioSource);
		audioSource->AddClipByKey(L"monser_walk1");
		audioSource->AddClipByKey(L"monser_walk2");
		audioSource->AddClipByKey(L"monser_walk3");
		audioSource->AddClipByKey(L"monser_walk4");
		audioSource->AddClipByKey(L"monster_death_bullet");
		audioSource->AddClipByKey(L"monster_death1");
		audioSource->AddClipByKey(L"monster_death2");
		audioSource->AddClipByKey(L"monster_death3");
		audioSource->AddClipByKey(L"monster_reload");
		audioSource->AddClipByKey(L"monster_run1");
		audioSource->AddClipByKey(L"monster_run2");
		audioSource->AddClipByKey(L"monster_run3");
		audioSource->AddClipByKey(L"monster_run4"); 
		audioSource->AddClipByKey(L"monster_shot");
		audioSource->AddClipByKey(L"monstser_slide");

		audioSource->AddClipByKey(L"blood_splat1");
		audioSource->AddClipByKey(L"blood_splat2");
		audioSource->AddClipByKey(L"blood_splat3");
		audioSource->AddClipByKey(L"blood_splat4");
		audioSource->AddClipByKey(L"blood_squirt1");
		audioSource->AddClipByKey(L"blood_squirt2");
		audioSource->AddClipByKey(L"blood_squirt3");


		CCollider2D* coll = AddComponent<CCollider2D>(eComponentType::Collider);
		coll->Initialize();
		coll->SetName(L"col_monster");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));

	}


	CMonster::~CMonster()
	{
	}

	void CMonster::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CMonster::update()
	{
		SetRayPos();

		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}

		CLiveGameObj::update();

	}

	void CMonster::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CMonster::render()
	{
		CLiveGameObj::render();
	}

	void CMonster::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}


	void CMonster::AddRay(Vector3 _Scale)
	{
		if (!mRay)
		{
			mRay = object::Instantiate<CMonsterRay>(eLayerType::Ray, this, L"MonsterRay");
			mRay->GetScript<CMonsterRayScript>()->SetMonster(this);

			if(_Scale != Vector3::Zero)
				mRay->SetScale(_Scale);
		}
	}
	void CMonster::SetRayPos()
	{
		if (mRay)
		{
			Vector3 Pos = GetPos();
			CTransform* RayTransform = mRay->GetComponent<CTransform>();
			Vector3 RayPos = RayTransform->GetPosition();
			Vector3 RayScale = RayTransform->GetScale();
			if (IsLeft())
			{
				RayTransform->SetPositionX(-(RayScale.x / 2.f));
			}
			else
			{
				RayTransform->SetPositionX((RayScale.x / 2.f));
			}
		}
	}
	bool CMonster::IsMonsterDead()
	{
		CMonsterScript* script = GetScript<CMonsterScript>();
		if (script)
		{
			return script->IsMonsterDead();
		}

		return false;
	}
	void CMonster::Disable()
	{
		GetScript<CMonsterScript>()->Reset();
		SetRayDie();
	}

	void CMonster::MonsterPatrolOn()
	{
		GetScript<CMonsterScript>()->PartolSwitchOn();
	}

}