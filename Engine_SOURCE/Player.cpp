#include "Player.h"
#include "PlayerScript.h"
#include "CameraScript.h"
#include "PlayerAfterImage.h"
#include "GameObj.h"
#include "Object.h"

namespace dru
{
	CPlayer::CPlayer()
		:mAfterImages{}
		, mAfterImageCount(20)
		, mPrevAfterImageCount(20)
		, mbPlayerDead(false)

	{
		SetLayerType(eLayerType::Player);
		SetScale(Vector3(1.25f, 1.25f, 1.f));

		renderer::mainCamera->GetCamScript()->SetPlayer(this);


		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_player");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));


		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PlayerMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Player_Idle", Material->GetTexture(), { 2718.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Run", Material->GetTexture(), { 4954.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_IdleToRun", Material->GetTexture(), { 3342.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_RunToIdle", Material->GetTexture(), { 5578.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 5, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_PreCrouch", Material->GetTexture(), { 6696.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Crouch", Material->GetTexture(), { 2602.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_PostCrouch", Material->GetTexture(), { 6572.f, 0.f }, { 62.f, 50.f },Vector2::Zero, 2, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Roll", Material->GetTexture(), { 6138.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_WallSlide", Material->GetTexture(), { 5952.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_WallSlideFast", Material->GetTexture(), { 6076.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 1, { 50.f, 50.f }, 1.f);
		mAnimator->Create(L"Player_WallKick", Material->GetTexture(), { 6820.f, 0.f }, { 62.f, 50.f },	Vector2::Zero, 11, { 50.f, 50.f }, 0.02f);
		mAnimator->Create(L"Player_Jump", Material->GetTexture(), { 3584.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Fall", Material->GetTexture(), { 1108.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 4, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Player_Attack", Material->GetTexture(), { 0.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 7, { 50.f, 50.f }, 0.05f);
		mAnimator->Create(L"Player_Dead", Material->GetTexture(), { 1364.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 12, { 50.f, 50.f }, 0.05f);
		//mAnimator->Create(L"Player_DeadStart", Material->GetTexture(), { 1364.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 2, { 50.f, 50.f }, 0.5f);
		//mAnimator->Create(L"Player_DeadAir", Material->GetTexture(), { 1488.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		//mAnimator->Create(L"Player_DeadEnd", Material->GetTexture(), { 1736.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.05f);
		mAnimator->Play(L"Player_Idle");

		AddComponent<CPlayerScript>(eComponentType::Script);

	}

	CPlayer::~CPlayer()
	{
		while (!mAfterImages.empty())
		{
			mAfterImages.front()->Die();
			mAfterImages.pop_front();
		}
	}

	void CPlayer::Initialize()
	{
		CLiveGameObj::Initialize();
	}

	void CPlayer::update()
	{
		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
			MakeAfterImage();
		}

		CLiveGameObj::update();
	}

	void CPlayer::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CPlayer::render()
	{
		
		CLiveGameObj::render();
	}

	
	void CPlayer::RemoveAfterImage()
	{
		while(!mAfterImages.empty())
		{
			mAfterImages.front()->Die();
			mAfterImages.pop_front();
		}
	}


	void CPlayer::MakeAfterImage()
	{
		// 잔상 생성
		CPlayerAfterImage* afterImage = object::Instantiate<CPlayerAfterImage>(eLayerType::AfterImage, L"PlayerAfterImage");
		afterImage->SetScale(Vector3(1.25f, 1.25f, 1.f));

		SetAfterImage(afterImage);
		afterImage->SetOwner(this);
		afterImage->Initialize(); 

		// 위치 및 텍스처 데이터 삽입
		FlipAfterImage(afterImage);
	}

	void CPlayer::FlipAfterImage(CPlayerAfterImage* _AfterImage)
	{
		_AfterImage->SetFrameCapturedData(mFrameCapture);

		if (IsLeft())
		{
			_AfterImage->SetLeft();
		}
		else
		{
			_AfterImage->SetRight();
		}
		_AfterImage->Flip();
	}

	void CPlayer::SetAfterImage(CPlayerAfterImage* _AfterImage)
	{

		if (mAfterImageCount >= mAfterImages.size())
		{
			mAfterImages.push_back(_AfterImage);
		}
		else
		{
			mAfterImages.front()->Die(); // 두개씩 빼야지 50에서 10됐을때 다시 돌아감 (한번에 빼면 잔상 한번에 사라져서 안이쁨)
			mAfterImages.pop_front();

			if (!mAfterImages.empty()) // 0개가 됐을때 오류 안나게함 2개씩뺄때 1개에서 여기 진입하면 오류뜸
			{
				mAfterImages.front()->Die();
				mAfterImages.pop_front();
			}

			mAfterImages.push_back(_AfterImage);
		}
		

		for (UINT i = 0; i < mAfterImages.size(); i++)
		{
			mAfterImages[i]->SetIndex(i);
		}

	}


}