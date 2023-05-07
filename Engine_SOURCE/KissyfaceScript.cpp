#include "KissyfaceScript.h"

namespace dru
{
	CKissyfaceScript::CKissyfaceScript()
	{
	}

	CKissyfaceScript::~CKissyfaceScript()
	{
	}

	void CKissyfaceScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();
		mAnimator->GetCompleteEvent(L"kissyface_WaitingEnd") = std::bind(&CKissyfaceScript::waitingEndComplete, this);


		CBossScript::Initialize();
	}

	void CKissyfaceScript::update()
	{


		CBossScript::update();
	}

	void CKissyfaceScript::fixedUpdate()
	{
		CBossScript::fixedUpdate();
	}

	void CKissyfaceScript::render()
	{
		CBossScript::render();
	}

	void CKissyfaceScript::attack()
	{
		if (mState[(UINT)eBossState::Attack] == true)
		{
			CBossScript::attack();
		}
	}


	void CKissyfaceScript::OnCollisionEnter(CCollider2D* _oppo)
	{

		CBossScript::OnCollisionEnter(_oppo);
	}

	void CKissyfaceScript::OnCollision(CCollider2D* _oppo)
	{
	
	
		CBossScript::OnCollision(_oppo);
	}

	void CKissyfaceScript::OnCollisionExit(CCollider2D* _oppo)
	{

		CBossScript::OnCollisionExit(_oppo);
	}

	void CKissyfaceScript::ChoosePattern()
	{
	}

	void CKissyfaceScript::waitingEndComplete()
	{
		SetSingleState(eBossState::Idle);
	}


}