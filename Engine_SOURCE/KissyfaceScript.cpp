#include "KissyfaceScript.h"
#include "Kissyface.h"
#include "Axe.h"
#include "AxeScript.h"
#include "TimeMgr.h"
#include "Object.h"

namespace dru
{
	CKissyfaceScript::CKissyfaceScript()
		: mKissyface(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mPattern2_RecieveWaitingTime(1.f)
		, mbNoAxe(false)
	{
	}

	CKissyfaceScript::~CKissyfaceScript()
	{
	}

	void CKissyfaceScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();

		mAnimator->GetCompleteEvent(L"kissyface_Block") = [this] { SetSingleState(eBossState::Idle);	};
		mAnimator->GetCompleteEvent(L"kissyface_WaitingEnd") = [this] { SetSingleState(eBossState::Idle);	};
		mAnimator->GetCompleteEvent(L"kissyface_RecieveAxe") = [this] { PatternEnd(2);	};
		mAnimator->GetCompleteEvent(L"kissyface_Land") = [this]
		{
			mKissyface->SetAfterImageCount(0);
			PatternEnd(1);
		};
		mAnimator->GetCompleteEvent(L"kissyface_ThrowAxe") = [this]
		{
			mAnimator->Play(L"kissyface_ThrowAxeEnd");
			SetStatePattern2On(ePattern2::ThrowEnd);
		};


		mAnimator->GetCompleteEvent(L"kissyface_JumpStart") = std::bind(&CKissyfaceScript::jumpStartComplete, this);
		mAnimator->GetCompleteEvent(L"kissyface_AirThrowAxe") = std::bind(&CKissyfaceScript::airThrowAxeComplete, this);
		mAnimator->GetEndEvent(L"kissyface_AirThrowEnd") = std::bind(&CKissyfaceScript::airThrowAxeEndEnd, this);

		mAnimator->GetFrameEvent(L"kissyface_ThrowAxe", 5) = std::bind(&CKissyfaceScript::throwAxeFrame5, this);
		

		mKissyface = dynamic_cast<CKissyface*>(GetOwner());

		CBossScript::Initialize();
	}

	void CKissyfaceScript::update()
	{
		if (!GetOwner_LiveObject()->IsRewindRePlaying())
		{
			mKissyface->GetAxeScript()->SetKissyfaceCenter(mKissyface->GetWorldPos());

			CBossScript::update();
		}
	}

	void CKissyfaceScript::fixedUpdate()
	{
		CBossScript::fixedUpdate();
	}

	void CKissyfaceScript::render()
	{
		CBossScript::render();
	}


	void CKissyfaceScript::OnCollisionEnter(CCollider2D* _oppo)
	{
		if (L"col_floor" == _oppo->GetName())
		{
			if (GetState(eBossState::Pattern1))
			{
				mAnimator->Play(L"kissyface_Land", false);
				SetStatePattern1On(ePattern1::Land);
			}
		}
		else if (L"col_kissyFaceAxe" == _oppo->GetName())
		{
			if (mKissyface->GetAxeScript()->GetState(eState::Recieve))
			{
				SetStatePattern2On(ePattern2::Recieve);
				mAnimator->Play(L"kissyface_RecieveAxe", false);
				AxeOff();
			}
		}
		else if (L"col_Player_Slash" == _oppo->GetName())
		{
			if (!mbNoAxe)
			{
				SetSingleState(eBossState::Block);
				Block();
			}
		}

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

	void CKissyfaceScript::Reset()
	{
		AxeOff();
		mKissyface->GetAxeScript()->Reset();
		mStatePattern1.reset();
		mStatePattern2.reset();
		mPattern2_RecieveWaitingTime = 1.f;
		GetOwner_LiveObject()->RemoveAfterImage();

		CBossScript::Reset();
	}

	void CKissyfaceScript::Pattern1()
	{
		if (!GetStatePattern1(ePattern1::Jump))
		{
			mAnimator->Play(L"kissyface_JumpStart", false);
			SetStatePattern1On(ePattern1::Jump);
			mKissyface->SetAfterImageCount(30);
		}
		if (GetStatePattern1(ePattern1::Throw) && !GetStatePattern1(ePattern1::ThrowEnd))
		{
			mRigidbody->AddForceY(50.f);
		}
	}

	void CKissyfaceScript::Pattern2()
	{
		if (!GetStatePattern2(ePattern2::Throw))
		{
			mAnimator->Play(L"kissyface_ThrowAxe", false);
			SetStatePattern2On(ePattern2::Throw);
			SetAxeDir();
		}
		if (GetStatePattern2(ePattern2::Throw))
		{
			if (mKissyface->GetAxeScript()->GetState(eState::Stuck))
			{
				mPattern2_RecieveWaitingTime -= CTimeMgr::DeltaTime();
				if (0.f >= mPattern2_RecieveWaitingTime)
				{
					mKissyface->GetAxeScript()->SetStateOff(eState::Stuck);
					mKissyface->GetAxeScript()->SetStateOn(eState::Recieve);
					mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);
					mPattern2_RecieveWaitingTime = 1.f;
				}
			}
		}


	}

	void CKissyfaceScript::Pattern3()
	{
	}

	void CKissyfaceScript::Pattern4()
	{
	}

	void CKissyfaceScript::Pattern5()
	{
	}

	void CKissyfaceScript::PatternEnd(UINT _PatternNumber)
	{
		switch (_PatternNumber)
		{
		case 1:
			mStatePattern1.reset();
			break;
		case 2:
			mStatePattern2.reset();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}

		Reset();
	}

	void CKissyfaceScript::SetAxeDir()
	{
		float playerPosX = mPlayer->GetWorldPos().x;
		float KissyPosX = GetOwnerWorldPos().x;

		if (playerPosX > KissyPosX)
		{
			mKissyface->GetAxeScript()->SetDir({ 1.f, 0.f, 0.f });
		}
		else
		{
			mKissyface->GetAxeScript()->SetDir({ -1.f, 0.f, 0.f });
		}

	}

	void CKissyfaceScript::AxeOn()
	{
		mKissyface->GetAxe()->RenderingBlockOff();
		mKissyface->GetAxe()->SetAfterImageCount(50);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->On();
		coll->RenderingOn();
		mbNoAxe = true;
	}

	void CKissyfaceScript::AxeOff()
	{
		mKissyface->GetAxe()->RenderingBlockOn();
		mKissyface->GetAxeScript()->Reset();
		mKissyface->GetAxe()->RemoveAfterImage();
		mKissyface->GetAxe()->SetAfterImageCount(0);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->Off();
		coll->RenderingOff();
		mbNoAxe = false;
	}

	void CKissyfaceScript::Block()
	{
		SetSingleState(eBossState::Block);
		PlayBulletReflect();

	}


	void CKissyfaceScript::jumpStartComplete()
	{
		if (!GetStatePattern1(ePattern1::Throw))
		{
			SetStatePattern1On(ePattern1::Throw);
			mAnimator->Play(L"kissyface_AirThrowAxe", false);
			AxeOn();
			mKissyface->GetAxeScript()->SetStateOn(eState::Orbit);
			mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);

			mKissyface->GetAxe()->SetAfterImageCount(50);
		}
	}

	void CKissyfaceScript::airThrowAxeComplete()
	{		
		SetStatePattern1Off(ePattern1::Throw);
		SetStatePattern1On(ePattern1::ThrowEnd);
		mAnimator->Play(L"kissyface_AirThrowEnd");
	}

	void CKissyfaceScript::airThrowAxeEndEnd()
	{
		AxeOff();
		mKissyface->GetAxeScript()->SetStateOff(eState::Orbit);
		mKissyface->GetAxeScript()->SetStateOff(eState::Rotate);
	}

	void CKissyfaceScript::throwAxeFrame5()
	{
		AxeOn();
		mKissyface->GetAxe()->SetPos(Vector3::Zero);
		mKissyface->GetAxeScript()->SetStateOn(eState::Fly);
		mKissyface->GetAxeScript()->SetStateOn(eState::Rotate);
	}


	void CKissyfaceScript::InitializeBulletReflectComponent()
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
					BulletReflectObjectAnimator->GetCompleteEvent(L"BulletReflect") = [this]
					{
						mBulletReflect->RenderingBlockOn();
					};
				}
				else
				{
					assert(false);
				}
			}
			BulletReflectObject->RenderingBlockOn();
		}
	}

	void CKissyfaceScript::PlayBulletReflect()
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

	void CKissyfaceScript::BulletReflectPositioning()
	{
		mBulletReflect->SetPos(GetOwnerWorldPos());
	}

	CGameObj* CKissyfaceScript::GetOrCreateBulletReflectObject()
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