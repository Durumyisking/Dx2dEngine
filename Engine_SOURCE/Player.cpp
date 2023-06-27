#include "Player.h"
#include "PlayerScript.h"
#include "CameraScript.h"
#include "PlayerAfterImage.h"
#include "GameObj.h"
#include "Stage.h"
#include "HorizonGauge.h"
#include "SceneMain.h"

namespace dru
{
	CPlayer::CPlayer()
		: mbPlayerDead(false)
		, mBlockGauge(nullptr)

	{
		SetLayerType(eLayerType::Player);
		SetScale(Vector3(1.25f, 1.25f, 1.f));

		renderer::mainCamera->GetCamScript()->SetPlayer(this);


		CRigidBody* rigidbody = this->AddComponent<CRigidBody>(eComponentType::RigidBody);

		CCollider2D* coll = this->AddComponent<CCollider2D>(eComponentType::Collider);
		coll->SetName(L"col_player");
		coll->SetType(eColliderType::Rect);
		coll->SetScale(Vector2(0.2f, 0.6f));

		AddComponent<CAudioListener>(eComponentType::AudioListener);
		CAudioSource* audioSource = AddComponent<CAudioSource>(eComponentType::AudioSource);
		audioSource->AddClipByKey(L"player_die");
		audioSource->AddClipByKey(L"player_footstep");
		audioSource->AddClipByKey(L"player_jump");
		audioSource->AddClipByKey(L"player_land");
		audioSource->AddClipByKey(L"player_prerun");
		audioSource->AddClipByKey(L"player_roll");
		audioSource->AddClipByKey(L"player_roll_real");
		audioSource->AddClipByKey(L"player_run1");
		audioSource->AddClipByKey(L"player_run2");
		audioSource->AddClipByKey(L"player_run3");
		audioSource->AddClipByKey(L"player_run4");
		audioSource->AddClipByKey(L"player_slash1");
		audioSource->AddClipByKey(L"player_slash2");
		audioSource->AddClipByKey(L"player_slash3");
		audioSource->AddClipByKey(L"player_wallkick1");
		audioSource->AddClipByKey(L"player_wallkick2");
		audioSource->AddClipByKey(L"player_wallkick3");
		audioSource->AddClipByKey(L"player_wallslide");

		audioSource->AddClipByKey(L"laser_blast");

		audioSource->AddClipByKey(L"song_main_bgm");
		audioSource->AddClipByKey(L"song_tutorial_bgm");
		audioSource->AddClipByKey(L"song_boss_bgm");

		audioSource->AddClipByKey(L"SE_rewind");
		audioSource->AddClipByKey(L"SE_correct");

//		audioSource->SetWholeVolume(0.5f);

		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"PlayerMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Player_Idle", Material->GetTexture(), { 2718.f, 0.f }, { 62.f, 50.f },		Vector2::Zero, 10, { 50.f, 50.f}, 0.1f);
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
		// mAnimator->Create(L"Player_DeadStart", Material->GetTexture(), { 1364.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 2, { 50.f, 50.f }, 0.5f);
		// mAnimator->Create(L"Player_DeadAir", Material->GetTexture(), { 1488.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 4, { 50.f, 50.f }, 0.05f);
		// mAnimator->Create(L"Player_DeadEnd", Material->GetTexture(), { 1736.f, 0.f }, { 62.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.05f);
		mAnimator->Play(L"Player_Idle");

		AddComponent<CPlayerScript>(eComponentType::Script);
	
		AddBlockGauge();

		dynamic_cast<CSceneMain*>(CSceneMgr::mScenes[(UINT)CSceneMgr::eSceneType::Main])->SetPlayer(this);
	}

	CPlayer::~CPlayer()
	{

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
			MakeAfterImage(true, 50);
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

	void CPlayer::fontRender()
	{
#ifdef _DEBUG
		if (!IsRewindRePlaying())
		{
			std::wstring str = L"Player FrameCount : ";
			std::wstring strFrameCount = std::to_wstring(mFrameCapture.FrameNumber);
			str += strFrameCount;
			const wchar_t* result = str.c_str();
			CFontWrapper::DrawFont(result, 40.f, 155.f, 30.f, FONT_RGBA(255, 255, 255, 255));
		}
		else
		{
			if (!mFrameCaptureData.empty())
			{
				if (IsRewinding())
				{
					CFontWrapper::DrawFont(L"Rewind", 40.f, 155.f, 30.f, FONT_RGBA(0, 255, 255, 255));
					std::wstring str = L"Player FrameCount : ";
					std::wstring strFrameCount = std::to_wstring(mDebugFrameNumber);
					str += strFrameCount;
					const wchar_t* result = str.c_str();
					CFontWrapper::DrawFont(result, 40.f, 185.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				}
				if (IsReplaying())
				{
					CFontWrapper::DrawFont(L"Replay", 40.f, 155.f, 30.f, FONT_RGBA(255, 0, 0, 255));
					std::wstring str = L"Player FrameCount : ";
					std::wstring strFrameCount = std::to_wstring(mDebugFrameNumber);
					str += strFrameCount;
					const wchar_t* result = str.c_str();
					CFontWrapper::DrawFont(result, 40.f, 185.f, 30.f, FONT_RGBA(255, 255, 255, 255));
				}
			}
		}
		std::wstring strAfterImageCount = std::to_wstring(mAfterImageCount);
		const wchar_t* afterImageResult = strAfterImageCount.c_str();
		CFontWrapper::DrawFont(afterImageResult, 40.f, 185.f, 10.f, FONT_RGBA(255, 255, 255, 255));

#endif


	}

	void CPlayer::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

	void CPlayer::AddBlockGauge()
	{
		mBlockGauge = object::Instantiate<CHorizonGauge>(eLayerType::None, this, L"BlockGauge");
		mBlockGauge->SetPosAbs({ 0.f, 0.65f, -1.f });
		mBlockGauge->SetScale({ 0.5f, 0.1f, 0.f });
		mBlockGauge->SetTimer(0.5f);
		mBlockGauge->RenderingBlockOn();
	}

	void CPlayer::PlayGauge()
	{
		mBlockGauge->Play();
	}

	void CPlayer::Hit(Vector3& _enemyPos, int _Type)
	{
		GetScript<CPlayerScript>()->hit(_enemyPos, _Type);

	}

	void CPlayer::SetPlayerStun()
	{
		GetScript<CPlayerScript>()->StunOn();
	}



}