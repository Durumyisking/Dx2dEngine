#include "BulletScript.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "Input.h"
#include "Object.h"

namespace dru
{
	CBulletScript::CBulletScript()
		: mBullet(nullptr)
		, mBulletReflect(nullptr)
		, mElapsedTime(0.f)
		, mDefaultBulletScale(Vector3( 0.025f, 0.025f, 1.f ))
		, mbScalingDone(false)
		, mbCreated(false)
		, mDir(Vector3::Zero)
	{
	}

	CBulletScript::~CBulletScript()
	{
	}

	void CBulletScript::Initialize()
	{
		mBullet = dynamic_cast<CBullet*>(GetOwner());
	}

	void CBulletScript::update()
	{
		mElapsedTime += CTimeMgr::DeltaTime();
		BulletMove();

		if (CTimeMgr::IsBulletTimeOn())
		{
			BulletScaling();
		}
	}

	void CBulletScript::fixedUpdate()
	{
	}

	void CBulletScript::render()
	{
	}

	void CBulletScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName() || L"col_stair" == _oppo->GetName() || L"col_wall" == _oppo->GetName()
			|| L"col_outWallside" == _oppo->GetName() || L"col_outWall" == _oppo->GetName())
		{
			Disable();
		}
		else if (L"col_player" == _oppo->GetName())
		{
			if (!mBullet->IsReflect())
			{
				Disable();
			}
		}
		else if (L"col_monster" == _oppo->GetName())
		{
			if (mBullet->IsReflect())
			{
				Disable();
			}
		}
		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!mBullet->IsReflect())
			{
				BulletReflect();
				PlayBulletReflect();
			}
		}
	}

	void CBulletScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnCollisionExit(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CBulletScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}

	void CBulletScript::BulletScaling()
	{
		// 0.5초동안 줄어들게
		float Ratio = 1 - mElapsedTime / 10.5f;

		if (Ratio >= 0.0f)
		{
			float NewX = mDefaultBulletScale.x * Ratio;
			std::cout << NewX << std::endl;
			GetOwner()->SetScale({ NewX, mDefaultBulletScale.y , mDefaultBulletScale.z });
			Vector3 NewPos = Vector3( GetOwnerPos().x - (mDefaultBulletScale.x - NewX) * 0.5f, GetOwnerPos().y, GetOwnerPos().z );
			GetOwner()->SetPos(NewPos);
			
			GetOwner()->GetComponent<CCollider2D>()->SetCenter({ NewPos.x, NewPos.y });
		}
	}

	void CBulletScript::BulletMove()
	{

		mDir = mBullet->GetDir();
		Vector3 pos = GetOwnerPos();

		pos += mDir * CTimeMgr::DeltaTime() * mBullet->GetSpeed();

		GetOwner()->SetPos(pos);
	}

	void CBulletScript::BulletReflect()
	{
		mBullet->ReflectOn();

		Vector3 MousePos = CInput::GetMousePosition_world();

		Vector3 dir = MousePos;
		dir.Normalize();
		mDir = dir;
		mBullet->SetDir(mDir);

		Vector3 Right = { 1.f, 0.f, 0.f };
		float angle = GetAngleFromDirection(dir, Right);
		mBullet->GetComponent<CTransform>()->SetRotationZ(angle);

		CCollider2D* coll = mBullet->GetComponent<CCollider2D>();
		coll->SetCenter({ mBullet->GetCollPosX(), 0.f });
		Vector3 collPos = { coll->GetCenter().x, coll->GetCenter().y, 0.f };
		collPos = RotateZ(collPos, angle);
		coll->SetCenter({ collPos.x, collPos.y });
	}

	void CBulletScript::InitializeBulletReflectComponent()
	{
		CGameObj* BulletReflectObject = GetOrCreateBulletReflectObject();
		if (BulletReflectObject)
		{
			BulletReflectObject->SetScale({ 1.f, 1.f, 1.f });

			std::shared_ptr<CTexture> BulletReflectObjectTexture = nullptr;
			CSpriteRenderer* SpriteRenderer = BulletReflectObject->AddComponent<CSpriteRenderer>(eComponentType::Renderer);
			if (SpriteRenderer)
			{
				std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BulletReflectMat");
				if (Material)
				{
					BulletReflectObjectTexture = Material->GetTexture();
					SpriteRenderer->SetMaterial(Material);
				}
			}
			else
			{
				assert(false);
			}

			if (BulletReflectObjectTexture)
			{
				CAnimator* BulletReflectObjectAnimator = BulletReflectObject->AddComponent<CAnimator>(eComponentType::Animator);
				if (BulletReflectObjectAnimator)
				{
					BulletReflectObjectAnimator->Create(L"BulletReflect", BulletReflectObjectTexture, { 0.f, 0.f }, { 128.f, 64.f }, Vector2::Zero, 5, { 50.f, 50.f }, 0.1f);
					BulletReflectObjectAnimator->GetCompleteEvent(L"BulletReflect") = std::bind(&CBulletScript::BulletReflectComplete, this);
				}
				else
				{
					assert(false);
				}
			}
			BulletReflectObject->RenderingBlockOn();
		}
	}

	void CBulletScript::Disable()
	{
		GetOwner()->RenderingBlockOn();
		GetOwner()->GetComponent<CCollider2D>()->Off();
		GetOwner()->GetComponent<CCollider2D>()->RenderingOff();
	}

	void CBulletScript::BulletReflectComplete()
	{
		mBulletReflect->RenderingBlockOn();
	}

	void CBulletScript::PlayBulletReflect()
	{
		CGameObj* BulletReflectObject = GetOrCreateBulletReflectObject();
		if (BulletReflectObject)
		{
			BulletReflectPositioning();

			CAnimator* BulletReflectObjectAnimator = BulletReflectObject->GetComponent<CAnimator>();
			if (BulletReflectObjectAnimator)
			{
				BulletReflectObject->RenderingBlockOff();
				BulletReflectObjectAnimator->Play(L"BulletReflect", false);
			}
			else
			{
				assert(false);
			}
		}
	}

	void CBulletScript::BulletReflectPositioning()
	{
		Vector3 colPos = mBullet->GetComponent<CCollider2D>()->GetColliderPos();
		mBulletReflect->SetPos(colPos);
	}

	CGameObj* CBulletScript::GetOrCreateBulletReflectObject()
	{
		if (!mBulletReflect)
		{
			// create
			mBulletReflect = object::Instantiate<CGameObj>(eLayerType::FX, L"BulletReflect");
			if (mBulletReflect)
			{
				// intialize
				InitializeBulletReflectComponent();
			}
		}

		return mBulletReflect;
	}

}	