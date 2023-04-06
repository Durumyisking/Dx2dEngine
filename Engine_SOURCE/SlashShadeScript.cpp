#include "SlashShadeScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"
#include "TimeMgr.h"
#include "Collider2D.h"

namespace dru
{
	CSlashShadeScript::CSlashShadeScript()
		: CScript()
		,mTrans(nullptr)
		,mPos{}
		,mRot{}
		,mDir{}
		, mbStart(false)
		, mChangeColorTimer(0.f)
		, mbMagenta(false)
	{
	}

	CSlashShadeScript::~CSlashShadeScript()
	{
	}

	void CSlashShadeScript::Initialize()
	{
		mTrans = GetOwner()->GetComponent<CTransform>();
		mPos = mTrans->GetPosition();

		Vector3 MousePos = CInput::GetMousePosition_world();

		mDir = MousePos - mPos;
		mDir.z = 0.f;
		mDir.Normalize();
		

		Vector3 rotation = mTrans->GetRotation();

		// x축과 mousepos <-> slashobj 각도 받음 라디안
		rotation.z = atan2(MousePos.y - mPos.y, MousePos.x - mPos.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;
		// 인자로 degree 넣음
		mTrans->SetRotation(rotation);
		
		CSpriteRenderer* sprrenderer = GetOwner()->GetComponent<CSpriteRenderer>();
		sprrenderer->ChangeColor(Vector4(1.f, 0.f, 1.f, 0.5f));

		mbMagenta = true;
	}

	void CSlashShadeScript::update()
	{
	}

	void CSlashShadeScript::fixedUpdate()
	{
		// update를 지나야 기저가 변경되기 때문ㅜㅜ
		if (!mbStart)
		{
			mPos = mTrans->GetPosition();
			mPos += mTrans->Right() * -15.f;
			mTrans->SetPosition(mPos);
			mbStart = true;
		}
		else
		{
			mPos = mTrans->GetPosition();
			mPos += (mTrans->Right() * 150.f * CTimeMgr::DeltaTimeConstant());
			mTrans->SetPosition(mPos);
		}
	}

	void CSlashShadeScript::render()
	{
		mChangeColorTimer += CTimeMgr::DeltaTimeConstant();

		if (mChangeColorTimer > 0.15f)
		{
			CSpriteRenderer* sprrenderer = GetOwner()->GetComponent<CSpriteRenderer>();
			if (!mbMagenta)
			{
				sprrenderer->ChangeColor(Vector4(1.f, 0.f, 1.f, 0.5f));
				mbMagenta = true;

			}
			else
			{
				sprrenderer->ChangeColor(Vector4(0.f, 1.f, 1.f, 0.5f));
				mbMagenta = false;
			}
			mChangeColorTimer = 0.f;
		}
	}

	void CSlashShadeScript::OnCollisionEnter(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnCollisionExit(CCollider2D* _oppo)
	{
		if (L"col_maincam" == _oppo->GetName())
		{
			GetOwner()->Die();
		}
	}

	void CSlashShadeScript::OnTriggerEnter(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnTrigger(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnTriggerExit(CCollider2D* _oppo)
	{
	}


}