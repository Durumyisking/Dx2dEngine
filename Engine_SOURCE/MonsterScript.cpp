#include "MonsterScript.h"
#include "Transform.h"
#include "TimeMgr.h"
#include "Object.h"
#include "SlashScript.h"
#include "BodyShadeScript.h"
#include "Input.h"
#include "Monster.h"
#include "SceneMain.h"
#include "Blood.h"

namespace dru
{
	CMonsterScript::CMonsterScript()
		: mState{}
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mTransform(nullptr)
		, mTarget(nullptr)
		, mPos(Vector3::Zero)
		, mMoveDir(Vector3::Zero)
		, mHitDir(Vector3::Zero)
		, mbOnWall(false)
		, mbDead(false)
		, mbDeleteOn(false)
		, mHitTimer(0.f)
		, mAttackTimer(1.f)
		, mMonsterName{}
		, mDetectRadius(7.f)
		, mAttackRadius(4.f)
	{

	}

	CMonsterScript::~CMonsterScript()
	{
	}

	void CMonsterScript::Initialize()
	{
		mState[(UINT)eMonsterState::Idle] = true;

		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		mTransform = GetOwner()->GetComponent<CTransform>();
		mMonsterName = GetOwner()->GetName();

		mAnimator->GetCompleteEvent(mMonsterName + L"_DeadGround") = std::bind(&CMonsterScript::deadgroundComplete, this);
		mAnimator->GetCompleteEvent(mMonsterName + L"_Attack") = std::bind(&CMonsterScript::attackComplete, this);

	}

	void CMonsterScript::update()
	{
		eStageState stagestate = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene)->GetCurrentStage()->GetReadyState();
		if (stagestate == eStageState::LoadEnd)
		{
			mPos = mTransform->GetPosition();

			if (!mbDead)
			{
				mAttackTimer += CTimeMgr::DeltaTime();

				patrol();
				runTrigger();
				if (mState[UINT(eMonsterState::Run)] == true)
				{
					run();
				}

				mMoveDir = mRigidbody->GetVelocity();
				mMoveDir.Normalize();

				mTransform->SetPosition(mPos);
			}
			FlipCheck();
			dead();

		}
		GetOwner()->Flip();
	}

	void CMonsterScript::fixedUpdate()
	{
	}

	void CMonsterScript::render()
	{
	}

	void CMonsterScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			mRigidbody->SetGround();

			if (mbDead)
			{
				mState[(UINT)eMonsterState::DieAirUp] = false;
				mState[(UINT)eMonsterState::DieGround] = true;
				mAnimator->Play(mMonsterName+ L"_DeadGround", false);
			}

		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			collEnter_Floor2(_oppo);
			GetOwner()->SetFloorOn();
		}
		else if (L"col_stair" == _oppo->GetName())
		{
			mRigidbody->SetGround();
			float degree = dynamic_cast<CStair*>(_oppo->GetOwner())->GetDegree();
			GetOwner_LiveObject()->SetStairOn(degree);
		}

		else if (L"col_wall" == _oppo->GetName() || L"col_outWallside" == _oppo->GetName())
		{
			mbOnWall = true;

			if (GetOwner()->IsLeft())
			{
				GetOwner()->SetRight();
			}
			else
			{
				GetOwner()->SetLeft();
			}


			wallBound(_oppo);
		}

		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			SetHitDir();
			for (size_t i = 0; i < 25; i++)
			{
				CBlood* bodySlash = object::Instantiate<CBlood>(eLayerType::FX, L"Blood");
				bodySlash->Initialize();
				bodySlash->SetBloodPosition(GetOwnerWorldPos(), mHitDir);
			}

			hitSlash(0);
		}
		else if (L"col_bullet" == _oppo->GetName())
		{
			SetHitDir();
			collEnter_BulletSlash(_oppo);
		}
		else if (L"col_outWallside" == _oppo->GetName() || L"col_outWall" == _oppo->GetName())
		{
			Vector3 vel = mRigidbody->GetVelocity();
			mRigidbody->SetVelocity({ 0.f, vel.y, 0.f });
		}
	}

	void CMonsterScript::OnCollision(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			collEnter_Floor2(_oppo);
			GetOwner()->SetFloorOn();
		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			collEnter_Floor2(_oppo);
			GetOwner()->SetFloorOn();
		}

		else if (L"col_stair" == _oppo->GetName())
		{
			float degree = dynamic_cast<CStair*>(_oppo->GetOwner())->GetDegree();
			GetOwner_LiveObject()->SetStairOn(degree);
		}
	}

	void CMonsterScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_floor2" == _oppo->GetName())
		{
			GetOwner()->GetComponent<CRigidBody>()->SetAir();
		}
		else if (L"col_stair" == _oppo->GetName())
		{
			if (!GetOwner()->IsOnFloor())
			{
				GetOwner()->GetComponent<CRigidBody>()->SetAir();
			}

			GetOwner_LiveObject()->SetStairOff();
		}
		else if (L"col_wall" == _oppo->GetName() || L"col_outWallside" == _oppo->GetName())
		{
			mbOnWall = false;

			if (mbDead)
			{
				mRigidbody->SetMaxVelocity(DEFAULT_VELOCITY);
			}
		}
	}

	void CMonsterScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

	void CMonsterScript::HitAddForce()
	{
		mRigidbody->SetMaxVelocity({ 5.f, 5.f, 0.f });
	}



	void CMonsterScript::CreateBodySlash()
	{
		CGameObj* bodySlash = object::Instantiate<CGameObj>(eLayerType::FX, L"BodySlash");
		CSpriteRenderer* SpriteRenderer = bodySlash->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		bodySlash->SetPos(GetOwner()->GetPos());

		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BodySlashMat");
		SpriteRenderer->SetMaterial(Material);
		SpriteRenderer->MulColor(Vector4(0.917f, 0.796f, 0.403f, 1.f));

		CAnimator* mAnimator = bodySlash->AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"BodySlash", Material->GetTexture(), { 500.f, 0.f }, { 100.f, 100.f }, Vector2::Zero, 5, { 80.f, 80.f }, 0.05f);
		mAnimator->Play(L"BodySlash", false);

		CBodyShadeScript* script = bodySlash->AddComponent<CBodyShadeScript>(eComponentType::Script);
		script->Initialize();
		script->SetMonster(GetOwner());
	}

	float CMonsterScript::GetPlayerDistance()
	{
		Vector3 playerPos = mTarget->GetPos();
		Vector3 monsterPos = GetOwnerPos();
		float dist = (playerPos - monsterPos).Length();

		return dist;
	}

	Vector3 CMonsterScript::GetPlayerTowardDir(CGameObj* _Obj)
	{
		Vector3 dir = mTarget->GetPos() - _Obj->GetPos();
		dir.Normalize();
		dir.z = 0.f;
		return dir;
	}

	void CMonsterScript::FlipCheck()
	{
		if (mMoveDir.x > 0.f)
		{
			GetOwner()->SetRight();
		}
		else if (mMoveDir.x < 0.f)
		{
			GetOwner()->SetLeft();
		}
		else if (mMoveDir.x == 0.f)
		{
			if (mTarget && !mbDead)
			{
				if (mTarget->GetWorldPos().x > GetOwnerWorldPos().x)
				{
					GetOwner()->SetRight();
				}
				else
				{
					GetOwner()->SetLeft();
				}
			}
		}
	}

	void CMonsterScript::Reset()
	{
		mTarget = nullptr;
		mbDead = false;
		mHitTimer = 0.f;
		SetSingleState(eMonsterState::Idle);
		GetOwner()->GetComponent<CCollider2D>()->RenderingOn();

	}

	void CMonsterScript::SetSingleState(eMonsterState _Type)
	{
		if (mState[(UINT)_Type] == false)
		{
			mState.reset();
			switch (_Type)
			{
			case dru::eMonsterState::Idle:
				mAnimator->Play(GetOwner()->GetName() + L"_Idle");
				break;
			case dru::eMonsterState::Patrol:
				mAnimator->Play(GetOwner()->GetName() + L"_Patrol");
				break;
			case dru::eMonsterState::Run:
				mAnimator->Play(GetOwner()->GetName() + L"_Run");
				break;
			case dru::eMonsterState::Attack:
				mAnimator->Play(GetOwner()->GetName() + L"_Attack");
				break;
			case dru::eMonsterState::Fall:
				break;
			case dru::eMonsterState::DieAirUp:
				break;
			case dru::eMonsterState::DieAirDown:
				break;
			case dru::eMonsterState::DieGround:
				break;
			case dru::eMonsterState::End:
				break;
			default:
				break;
			}
			mState[(UINT)_Type] = true;
		}
	}

	void CMonsterScript::SetHitDir()
	{
		Vector3 MousePos = CInput::GetMousePosition_world();
		//MousePos /= 100.f;

		Vector3 monsterPos = GetOwner()->GetPos();

		mHitDir = MousePos - monsterPos;
		mHitDir.Normalize();
	}

	void CMonsterScript::runTrigger()
	{
		if (mTarget)
		{
			float dist = GetPlayerDistance();
			if (dist < mDetectRadius)
			{
				if (dist > mAttackRadius)
				{
					if (mState[(UINT)eMonsterState::Run] == false)
					{
						mRigidbody->SetMaxVelocity(VELOCITY_RUN);
						SetSingleState(eMonsterState::Run);
					}
				}
				else
				{
					if (mState[(UINT)eMonsterState::Attack] == false)
						SetSingleState(eMonsterState::Idle);
				}
			}
			else
			{
				SetSingleState(eMonsterState::Idle);
			}
		}
	}

	void CMonsterScript::run()
	{
		bool playerDead = dynamic_cast<CPlayer*>(mTarget)->IsPlayerDead();
		if (mTarget && !mbDead && !playerDead)
		{			
			Vector3 vPos = GetOwner()->GetPos();
			Vector3 vTargetPos = mTarget->GetPos();
			Vector3 vDir = Vector3(vTargetPos.x - vPos.x, 0.f, 0.f);
			vDir.Normalize();
			mRigidbody->AddForce(vDir * 50.f);
		}
		
	}

	void CMonsterScript::attack()
	{
		mAnimator->Play(GetOwner()->GetName() + L"_Attack", false);
		mAttackTimer = 0.f;
	}

	void CMonsterScript::patrol()
	{
	}

	void CMonsterScript::hitSlash(int _Type)
	{
		if (!mbDead)
		{
			mState.reset();
			HitAddForce();

			mbDead = true;
			if (0 == _Type)
			{
				SetSingleState(eMonsterState::DieAirUp);

				Vector3 MousePos = CInput::GetMousePosition_world();
				CreateSlashShade(MousePos);
				CreateBodySlash();
			}
			else if (1 == _Type)
			{
				SetSingleState(eMonsterState::DieGround);
				mAnimator->Play(mMonsterName + L"_DeadGround", false);
			}

			// timeslow
			CTimeMgr::BulletTime(0.5f);

			// CamShake
			ShakeParams sp = {};
			sp.duration = 0.5f;
			sp.magnitude = 0.0500f;
			renderer::mainCamera->GetCamScript()->Shake(sp);

			GetOwnerType<CMonster>()->SetRayDie();


			// 스테이지의 몬스터카운틀를 깎는다
			CSceneMain* scene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
			CStage* stage = scene->GetCurrentStage();
			stage->MonsterDead();
		}
	}

	void CMonsterScript::collEnter_BulletSlash(CCollider2D* _oppo)
	{
		CBullet* bullet = dynamic_cast<CBullet*>(_oppo->GetOwner());
		if (bullet->IsReflect())
		{
			hitSlash(1);
		}
	}

	void CMonsterScript::wallBound(CCollider2D* _oppo)
	{

		Vector3 vel = mRigidbody->GetVelocity();
		Vector3 Mvel = mRigidbody->GetMaxVelocity();
		if (mbDead)
		{
			mRigidbody->SetMaxVelocity({ 1.f, Mvel.y, Mvel.z });
		}
			if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x > _oppo->GetColliderPos().x)
			{
				mRigidbody->SetVelocity({ 1.f, vel.y, vel.z });
			}
			else if (GetOwner()->GetComponent<CCollider2D>()->GetColliderPos().x < _oppo->GetColliderPos().x)
			{
				mRigidbody->SetVelocity({ -1.f, vel.y, vel.z });
			}
		
	}

	void CMonsterScript::dead()
	{
		if (mbDead)
		{
			if (mState[(UINT)eMonsterState::DieGround] == false)
			{
				mHitTimer += CTimeMgr::DeltaTime();

				if (mHitTimer <= 0.25f)
				{
					mRigidbody->AddVelocity({ mHitDir.x * 0.5f, mHitDir.y * 0.5f, 0.f });
				}
				mMoveDir = mRigidbody->GetVelocity();
				mMoveDir.Normalize();

				if (mMoveDir.y > 0.f)
				{
					mState[(UINT)eMonsterState::DieAirUp] = true;
					mAnimator->Play(mMonsterName + L"_DeadAirUp");
				}
				else if (mMoveDir.y < 0.f)
				{
					mState[(UINT)eMonsterState::DieAirDown] = true;
					mAnimator->Play(mMonsterName + L"_DeadAirDown");
				}
				else if (mMoveDir.y == 0.f)
				{
					mState[(UINT)eMonsterState::DieGround] = true;
					mAnimator->Play(mMonsterName + L"_DeadGround", false);
				}

			}
		}
	}

	void CMonsterScript::deadgroundComplete()
	{
		GetOwner()->GetComponent<CCollider2D>()->RenderingOff();


		if (mbDeleteOn)
		{
			dynamic_cast<CMonster*>(GetOwner())->Die();
		}
	}

	void CMonsterScript::attackComplete()
	{
		if (!mTarget)
		{
			SetSingleState(eMonsterState::Idle);
		}
	}

	void CMonsterScript::collEnter_Floor2(CCollider2D* _oppo)
	{
		CCollider2D* monsterCollier = GetOwner()->GetComponent<CCollider2D>();
		float PosCheckMonster = monsterCollier->GetColliderPos().y - monsterCollier->GetScale().y / 2.f;
		float PosCheckFloor = _oppo->GetColliderPos().y + _oppo->GetScale().y / 2.f;
		if (PosCheckMonster >= PosCheckFloor)
		{
			mRigidbody->SetGround();
		}
	}

	void CMonsterScript::makeSlash(Vector2 _vLT, Vector2 _FrameSize, UINT _AnimSize, Vector2 _Ratio)
	{
		CGameObj* SlashObj = object::Instantiate<CGameObj>(eLayerType::FX, GetOwner()->GetName() + L"_Slash");
		SlashObj->SetScale({ 1.f, 1.f, 1.f });

		CCollider2D* coll = SlashObj->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_Monster_Slash");
		coll->Initialize();
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.75f, 0.75f));


		Vector3 slashpos = {}; 
		if (mTarget->GetPos().x < GetOwnerPos().x)
		{
			SlashObj->SetLeft();
			GetOwner()->SetLeft();
			slashpos = Vector3{ GetOwner()->GetPos().x - 0.5f, GetOwner()->GetPos().y, 0.f };
		}
		else
		{
			SlashObj->SetRight();
			GetOwner()->SetRight();
			slashpos = Vector3{ GetOwner()->GetPos().x + 0.5f, GetOwner()->GetPos().y, 0.f };
		}
		SlashObj->SetPos(slashpos);

		GetOwner()->Flip();
		SlashObj->Flip();


		CSpriteRenderer* SpriteRenderer = SlashObj->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(GetOwner()->GetName() + L"Mat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = SlashObj->AddComponent<CAnimator>(eComponentType::Animator);
		std::wstring animname = GetOwner()->GetName() + L"_SlashAnim";
		mAnimator->Create(animname, Material->GetTexture(), _vLT, _FrameSize, Vector2::Zero, _AnimSize, _Ratio, 0.025f);
		mAnimator->Play(animname, false);

		SlashObj->AddComponent<CSlashScript>(eComponentType::Script)->Initialize();
	}


}