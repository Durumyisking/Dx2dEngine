#include "Monster.h"
#include "Object.h"
#include "TimeMgr.h"
#include "MonsterRayScript.h"

namespace dru
{
	CMonster::CMonster()
		: mRay(nullptr)
	{
		SetLayerType(eLayerType::Monster);

		CRigidBody* rigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);

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

		AddRay();
		CLiveGameObj::Initialize();
	}

	void CMonster::update()
	{
		SetRayPos();
		 
		CLiveGameObj::update();

	}

	void CMonster::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CMonster::render()
	{

		CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);

		if ((eStageState::LoadEnd == scene->GetCurrentStage()->GetReadyState()) && !mbRewind)
		{
			PushFrameCpaturedData();
		}
		CLiveGameObj::render();
	}

	void CMonster::PushFrameCpaturedData()
	{
		FrameCapturedData Data = {};
		Data.Position = GetComponent<CTransform>()->GetPosition();
		Data.Texture = GetComponent<CSpriteRenderer>()->GetMaterial()->GetTexture();
		Data.AnimData = GetComponent<CAnimator>()->GetCurrentAnimation()->GetAnimationData();

		mFrameCaptureData.push(Data);
	}

	void CMonster::RewindOperate(float _ElapsedTime)
	{

		if (mFrameCaptureData.empty())
			mbRewind = false;
		else
		{
			Vector3 p = mFrameCaptureData.top().Position;
			mCurrentAnimData = mFrameCaptureData.top().AnimData; 
			SetPos(p);


			if (_ElapsedTime > 3.f)
			{
				int a = (_ElapsedTime / 3.f) + 1;

				for (int i = 0; i < a; i++)
				{
					if (!mFrameCaptureData.empty())
						mFrameCaptureData.pop();
				}
			}
			else
			{
				mFrameCaptureData.pop();
			}
		}
	}

	void CMonster::AddRay()
	{
		if (!mRay)
		{
			mRay = object::Instantiate<CMonsterRay>(eLayerType::Ray, this, L"MonsterRay");
			mRay->GetScript<CMonsterRayScript>()->SetMonster(this);
		}
	}
	void CMonster::SetRayPos()
	{
		if (mRay)
		{
			Vector3 vPos = GetPos();
			float ScaleX = mRay->GetScale().x;
			if (IsLeft())
			{
				vPos += ScaleX / 2.f * -GetComponent<CTransform>()->Right();
			}
			else
			{
				vPos += ScaleX / 2.f * GetComponent<CTransform>()->Right();
			}
			mRay->SetPos(vPos);
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
}