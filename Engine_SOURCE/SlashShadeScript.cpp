#include "SlashShadeScript.h"
#include "Transform.h"
#include "GameObj.h"
#include "Input.h"

namespace dru
{
	CSlashShadeScript::CSlashShadeScript()
		: CScript()
		,mTrans(nullptr)
		,mPos{}
		,mRot{}
		,mDir{}
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

		// x��� mousepos <-> slashobj ���� ���� ����
		rotation.z = atan2(MousePos.y - mPos.y, MousePos.x - mPos.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;
		// ���ڷ� degree ����
		mTrans->SetRotation(rotation);

	}

	void CSlashShadeScript::update()
	{

	}

	void CSlashShadeScript::fixedUpdate()
	{


	}

	void CSlashShadeScript::render()
	{
	}

	void CSlashShadeScript::OnCollisionEnter(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnCollision(CCollider2D* _oppo)
	{
	}

	void CSlashShadeScript::OnCollisionExit(CCollider2D* _oppo)
	{
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