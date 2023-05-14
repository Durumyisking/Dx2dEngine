#include "KissyfaceScript.h"
#include "Kissyface.h"
#include "Axe.h"
#include "AxeScript.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Stage.h"
#include "PlayerScript.h"


namespace dru
{
	CKissyfaceScript::CKissyfaceScript()
		: mKissyface(nullptr)
		, mBulletReflect(nullptr)
		, mAttackCollider(nullptr)
		, mStatePattern1{}
		, mStatePattern2{}
		, mStatePattern3{}
		, mPattern2_RecieveWaitingTime(1.f)
		, mPattern3_LungeOrigin(Vector3::Zero)
		, mPattern3_LungeDestination(Vector3::Zero)
		, mPattern3_mLungeElapsedTime(0.f)
		, mbNoAxe(false)
		, mbStruggling(false)
	{
	}

	CKissyfaceScript::~CKissyfaceScript()
	{
	}

	void CKissyfaceScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<CAnimator>();

		AddAnimationCallBack();
		AddAnimationCallBack_Lamda();

		mKissyface = dynamic_cast<CKissyface*>(GetOwner());

		CBossScript::Initialize();
	}

	void CKissyfaceScript::update()
	{
		if (!GetOwner_LiveObject()->IsRewindRePlaying())
		{
			mKissyface->GetAxeScript()->SetKissyfaceCenter(mKissyface->GetWorldPos());

			if (mbStruggling)
			{
				StruggleOperate();
			}

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
			if (GetState(eBossState::Pattern3) && GetStatePattern3(ePattern3::Lunge))
			{
				mAnimator->Play(L"kissyface_LungeAttack", false);
				SetStatePattern3On(ePattern3::LungeAttack);
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
			if (!GetState(eBossState::Hurt))
			{
				if (BlockTest())
				{
					SetSingleState(eBossState::Block);
					Block();
				}
				else
				{
					SetSingleState(eBossState::Hurt);
					mKissyface->Damaged();

					CTimeMgr::BulletTime(0.1f);
					renderer::mainCamera->GetCamScript()->MakeCamShake(0.5f, 0.1f);
				}
			}	
			else
			{
				StruggleOn();
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
		AllPatternReset();
		AttackColliderOff();
		AfterImageReset();
		mPlayer->RenderingBlockOff();

		CBossScript::Reset();
	}

	void CKissyfaceScript::AllPatternReset()
	{
		mStatePattern1.reset();
		mStatePattern2.reset();
		mStatePattern3.reset();

		mPattern2_RecieveWaitingTime = 1.f;
		mPattern3_LungeOrigin = Vector3::Zero;
		mPattern3_LungeDestination = Vector3::Zero;
		mPattern3_mLungeElapsedTime = 0.f;
	}

	void CKissyfaceScript::AfterImageReset()
	{
		mKissyface->ResetAfterImageColor();
		mKissyface->SetAfterImageCount(0);
	}

	void CKissyfaceScript::AddAnimationCallBack()
	{
		if (mAnimator)
		{
			mAnimator->GetCompleteEvent(L"kissyface_JumpStart") = std::bind(&CKissyfaceScript::jumpStartComplete, this);
			mAnimator->GetCompleteEvent(L"kissyface_AirThrowAxe") = std::bind(&CKissyfaceScript::airThrowAxeComplete, this);
			mAnimator->GetEndEvent(L"kissyface_AirThrowEnd") = std::bind(&CKissyfaceScript::airThrowAxeEndEnd, this);

			mAnimator->GetFrameEvent(L"kissyface_ThrowAxe", 5) = std::bind(&CKissyfaceScript::throwAxeFrame5, this);
		}
		else
		{
			assert(false);
		}
	}

	void CKissyfaceScript::AddAnimationCallBack_Lamda()
	{
		if (mAnimator)
		{
			mAnimator->GetCompleteEvent(L"kissyface_Block") = [this] {  Reset();	};
			mAnimator->GetCompleteEvent(L"kissyface_WaitingEnd") = [this] { SetSingleState(eBossState::Idle);	};
			mAnimator->GetCompleteEvent(L"kissyface_RecieveAxe") = [this] { PatternEnd(2);	};
			mAnimator->GetCompleteEvent(L"kissyface_Land") = [this]
			{
				PatternEnd(1);
			};
			mAnimator->GetCompleteEvent(L"kissyface_ThrowAxe") = [this]
			{
				mAnimator->Play(L"kissyface_ThrowAxeEnd");
				SetStatePattern2On(ePattern2::ThrowEnd);
			};
			mAnimator->GetCompleteEvent(L"kissyface_LungeReady") = [this]
			{
				mAnimator->Play(L"kissyface_Lunge", false);
				SetStatePattern3On(ePattern3::Lunge);
			};
			mAnimator->GetCompleteEvent(L"kissyface_LungeAttack") = [this]
			{
				PatternEnd(3);
			};
			mAnimator->GetFrameEvent(L"kissyface_LungeAttack", 3) = [this]
			{
				AttackColliderOff();
			};
			mAnimator->GetEndEvent(L"kissyface_LungeAttack") = [this]
			{
				AttackColliderOff();
			};

			mAnimator->GetCompleteEvent(L"kissyface_Hurt") = [this]
			{			
				AfterImageReset();
			};
			mAnimator->GetCompleteEvent(L"kissyface_GetUp") = [this]
			{
				Reset();
			};			
		}
		else
		{
			assert(false);
		}
	}

	void CKissyfaceScript::Pattern1()
	{
		if (!GetStatePattern1(ePattern1::Jump))
		{
			mAnimator->Play(L"kissyface_JumpStart", false);
			SetStatePattern1On(ePattern1::Jump);
			mKissyface->SetAfterImageCount(30);
			mKissyface->SetAfterImageColor(MAGENTA);

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
		if (!GetStatePattern3(ePattern3::LungeReady))
		{
			mKissyface->SetAfterImageCount(100);
			mKissyface->SetAfterImageColor(RED);

			mAnimator->Play(L"kissyface_LungeReady", false);

			mPattern3_LungeOrigin = GetOwnerWorldPos();
			mPattern3_LungeDestination = mPlayer->GetWorldPos();

			if (mbIsPlayerLeft)
			{
				mPattern3_LungeDestination.x += 1.f;
				AttackColliderPositioning(true);
			}
			else
			{
				mPattern3_LungeDestination.x -= 1.f;
				AttackColliderPositioning(false);
			}

			SetStatePattern3On(ePattern3::LungeReady);
		}
		if (GetStatePattern3(ePattern3::Lunge))
		{
			Lunge();
		}
	}

	void CKissyfaceScript::Lunge()
	{
		float newPosX = 0.f;
		mPattern3_mLungeElapsedTime += CTimeMgr::DeltaTime();
		if (mPattern3_mLungeElapsedTime <= LUNGE_TIMER)
		{
			float t = std::clamp(mPattern3_mLungeElapsedTime / LUNGE_TIMER, 0.f, 1.f); // 0~1사이의 값으로 만든다.
			newPosX = std::lerp(mPattern3_LungeOrigin.x, mPattern3_LungeDestination.x, t); // startPos와 endPos의 거리내 t비율만큼의 위치로 설정한다.
		}
		else
		{
			LungeStart();
			return;
		}
		if (mPattern3_mLungeElapsedTime <= (LUNGE_TIMER / 2.f))
		{
			mRigidbody->AddForceY(35.f);
		}

		Vector3 pos = GetOwnerWorldPos();

		pos.x = newPosX;

		GetOwner()->SetPos(pos);
	}

	void CKissyfaceScript::LungeStart()
	{
		mAnimator->Play(L"kissyface_LungeAttack", false);
		mbNoAxe = true;
		AttackColliderOn();
		SetStatePattern3On(ePattern3::LungeAttack);
		SetStatePattern3Off(ePattern3::Lunge);
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
			mStatePattern3.reset();
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
		mKissyface->GetAxe()->SetAfterImageCount(0);
		CCollider2D* coll = mKissyface->GetAxe()->GetComponent<CCollider2D>();
		coll->Off();
		coll->RenderingOff();
		mbNoAxe = false;
	}

	void CKissyfaceScript::Block()
	{
		mState.reset();
		mAnimator->Play(L"kissyface_Block", false);
		mState[(UINT)eBossState::Block] = true;

		PlayBulletReflect();

		CTimeMgr::BulletTime(0.1f);
		renderer::mainCamera->GetCamScript()->MakeCamShake(0.1f, 0.05f);
	}

	bool CKissyfaceScript::BlockTest()
	{
		if (GetOwner()->IsLeft())
		{
			if (mbIsPlayerLeft && !mbNoAxe)
			{
				return true;
			}
		}
		else
		{
			if (!mbIsPlayerLeft && !mbNoAxe)
			{
				return true;
			}
		}

		return false;
	}

	void CKissyfaceScript::StruggleOperate()
	{
		ShakeParams sp = {};
		sp.duration = 0.1f;
		sp.magnitude = 0.0250f;
		renderer::mainCamera->GetCamScript()->Shake(sp);

		if (CInput::GetKeyTap(eKeyCode::LBTN))
		{
			StruggleOff();
		}

		PushPlayer();
	}

	void CKissyfaceScript::StruggleOn()
	{
		Vector3 pos = GetOwnerWorldPos();
		pos.y += 1.f;
		CStage::KeyUI_LClickOn(pos);
		mbStruggling = true;
		mAnimator->Play(L"kissyface_Struggle");
		mPlayer->RemoveAfterImage();
		mPlayer->SetAfterImageCount(0);
		mPlayer->RenderingBlockOn();
		mPlayer->GetScript<CPlayerScript>()->InputBlocking();
	}

	void CKissyfaceScript::StruggleOff()
	{
		CStage::KeyUI_LClickOff();
		mbStruggling = false;
		Vector3 pos = mKissyface->GetWorldPos();
		pos.y = mPlayer->GetWorldPos().y;
		mPlayer->SetPos(pos);

		if (0 < mKissyface->GetHp())
		{
			mAnimator->Play(L"kissyface_GetUp", false);
			mPlayer->GetComponent<CAnimator>()->Play(L"Player_Dead", false);
			PlayerReset();
		}
		else
		{
			mAnimator->Play(L"kissyface_CutArm", false);
			mAnimator->GetCompleteEvent(L"kissyface_CutArm") = [this]
			{
				mAnimator->Play(L"kissyface_Dying");
				AxeOff();
				PlayerReset();

				Vector3 pos = mPlayer->GetWorldPos();

				if (GetOwner()->IsLeft())
				{
					pos.x -= 0.5f;
				}
				else
				{
					pos.x += 0.5f;
				}
				mPlayer->SetPos(pos);
				SetSingleState(eBossState::Dead);
			};
			mAnimator->GetFrameEvent(L"kissyface_CutArm", 3) = [this]
			{
				CTimeMgr::BulletTime(0.1f);
				renderer::mainCamera->GetCamScript()->MakeCamShake(0.1f, 1.f);
			};
			mAnimator->GetFrameEvent(L"kissyface_CutArm", 7) = [this]
			{
				CTimeMgr::BulletTime(0.1f);
				renderer::mainCamera->GetCamScript()->MakeCamShake(0.1f, 1.f);
			};

		}

	}

	void CKissyfaceScript::PushPlayer()
	{
		CAnimator* playerAnimator = mPlayer->GetComponent<CAnimator>();
		if (playerAnimator->IsPlaying(L"Player_Dead"))
		{
			CRigidBody* playerRigidBody = mPlayer->GetComponent<CRigidBody>();
			playerRigidBody->SetMaxVelocity({ 10.f, 7.f, 0.f });
			if (mbIsPlayerLeft)
			{
				playerRigidBody->AddVelocity({ 10.f, 0.f, 0.f });
			}
			else
			{
				playerRigidBody->AddVelocity({ -10.f, 0.f, 0.f });
			}
		}
	}

	void CKissyfaceScript::PlayerReset()
	{
		mPlayer->RenderingBlockOff();
		mPlayer->GetScript<CPlayerScript>()->UnInputBlocking();
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
			BulletReflectObject->SetScale({ 1.25f, 1.25f, 1.f });

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

	void CKissyfaceScript::PlayBulletReflect(Vector3 _Pos)
	{
		CGameObj* BulletReflectObject = GetOrCreateBulletReflectObject();
		if (BulletReflectObject)
		{
			CAnimator* BulletReflectObjectAnimator = BulletReflectObject->GetComponent<CAnimator>();
			if (BulletReflectObjectAnimator)
			{
				BulletReflectObject->RenderingBlockOff();
				BulletReflectObjectAnimator->Play(L"BulletReflect", false);
				BulletReflectObject->SetPos(_Pos);
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

	void CKissyfaceScript::InitializeAttackColliderComponent()
	{
		CGameObj* AttackColliderObject = GetOrCreatemAttackColliderObject();

		if (AttackColliderObject)
		{
			AttackColliderObject->SetScale({ 0.3f, 0.3f, 1.f });
			AttackColliderObject->SetPos(Vector3::Zero);

			CCollider2D* collider = AttackColliderObject->AddComponent<CCollider2D>(eComponentType::Collider);

			if (collider)
			{
				collider->SetName(L"col_Monster_Slash");
				collider->Initialize();
				collider->SetType(eColliderType::Rect);
				collider->Off();
				collider->RenderingOff();
			}
			else
			{
				assert(false);
			}
		}

	}

	void CKissyfaceScript::AttackColliderPositioning(bool _LeftLunge)
	{
		CGameObj* AttackColliderObject = GetOrCreatemAttackColliderObject();

		if (AttackColliderObject)
		{
			if (_LeftLunge)
			{
				AttackColliderObject->SetPos({-0.4f, -0.25f, 0.f});
			}
			else
			{
				AttackColliderObject->SetPos({ 0.4f, -0.25f, 0.f });
			}
		}
		else
		{
			assert(false);
		}
	}

	void CKissyfaceScript::AttackColliderOn()
	{
		CGameObj* AttackColliderObject = GetOrCreatemAttackColliderObject();

		if (AttackColliderObject)
		{
			CCollider2D* collider = mAttackCollider->GetComponent<CCollider2D>();

			if (collider)
			{
				collider->On();
				//collider->RenderingOn();
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}

	void CKissyfaceScript::AttackColliderOff()
	{
		CGameObj* AttackColliderObject = GetOrCreatemAttackColliderObject();

		if (AttackColliderObject)
		{
			CCollider2D* collider = mAttackCollider->GetComponent<CCollider2D>();

			if (collider)
			{
				collider->Off();
				//collider->RenderingOff();
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
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

	CGameObj* CKissyfaceScript::GetOrCreatemAttackColliderObject()
	{
		if (!mAttackCollider)
		{
			// create
			mAttackCollider = object::Instantiate<CGameObj>(eLayerType::FX, GetOwner(), L"Kissyface_AttackCollider");
			if (mAttackCollider)
			{
				// intialize
				InitializeAttackColliderComponent();
			}
		}

		return mAttackCollider;
	}


}
