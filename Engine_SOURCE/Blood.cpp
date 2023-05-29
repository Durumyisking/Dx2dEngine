#include "Blood.h"
#include "Stage.h"
#include "SceneMain.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "BloodScript.h"
#include "Object.h"

namespace dru
{
	CBlood::CBlood()
		:mMoveDirection(Vector3::Zero)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mSpeed(0.5f)
		, mbBloodDead(false)
	{
		SetLayerType(eLayerType::FX);
		CSpriteRenderer* SpriteRenderer = AddComponent<CSpriteRenderer>(eComponentType::Renderer);
		std::shared_ptr<CMaterial> Material = CResources::Find<CMaterial>(L"BloodMat");
		SpriteRenderer->SetMaterial(Material);

		CAnimator* mAnimator = AddComponent<CAnimator>(eComponentType::Animator);
		mAnimator->Create(L"Blood1", Material->GetTexture(), { 0.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Blood2", Material->GetTexture(), { 300.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);
		mAnimator->Create(L"Blood3", Material->GetTexture(), { 600.f, 0.f }, { 50.f, 50.f }, Vector2::Zero, 6, { 50.f, 50.f }, 0.1f);

		mRigidbody = AddComponent<CRigidBody>(eComponentType::RigidBody);
		mRigidbody->SetGravity(-5.f);

		int randomNumber = GetRandomNumber(3);

		switch (randomNumber)	
		{
		case 0:
			mAnimator->Play(L"Blood1", false);
			break;
		case 1:
			mAnimator->Play(L"Blood2", false);
			break;
		case 2:
			mAnimator->Play(L"Blood3", false);
			break;
		default:
			break;
		}

		if (mAnimator)
		{
			mAnimator->GetCompleteEvent(L"Blood1") = [this]
			{
				AnimCompleteEvent();
			};
			mAnimator->GetCompleteEvent(L"Blood2") = [this]
			{
				AnimCompleteEvent();
			};
			mAnimator->GetCompleteEvent(L"Blood3") = [this]
			{
				AnimCompleteEvent();
			};
		}
		
		AddComponent<CBloodScript>(eComponentType::Script);



	}
	CBlood::~CBlood()
	{
	}
	void CBlood::Initialize()
	{
		CSceneMain* mainScene = dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
		mainScene->GetCurrentStage()->PushRewindObject(this);

		mTransform = GetComponent<CTransform>();
		CLiveGameObj::Initialize();
	}
	 
	void CBlood::update()
	{
		if (!mbBloodDead)
		{
			mRigidbody->AddForceX(mMoveDirection.x * mSpeed);
			mRigidbody->AddForceY(mMoveDirection.y * mSpeed);
		}

		if (FrameCaptureCheck())
		{
			FrameCaptureOperate();
		}

		CLiveGameObj::update();
	}

	void CBlood::fixedUpdate()
	{
		CLiveGameObj::fixedUpdate();
	}

	void CBlood::render()
	{
		CLiveGameObj::render();
	}

	void CBlood::rewindRender()
	{
		CLiveGameObj::rewindRender();
	}

	void CBlood::SetBloodPosition_Direction(Vector3 _Standard, Vector3 _Direction)
	{

		mMoveDirection = _Direction;
	
		Vector3 Right = mTransform->Right();

		float Degree = GetAngleFromDirection(mMoveDirection, Right);
		
		mTransform->SetRotationZ(Degree);

		Vector3 newPos = {};
		newPos.z = _Standard.z;

		Vector2 Standard2D = { _Standard.x, _Standard.y };

		Vector2 Range = {};
		Range.x = _Standard.x + _Direction.x * 3.5f;
		Range.y = _Standard.y + _Direction.y * 3.5f;

		// standard, range 사이의 랜덤한 점을 구한다
		float RandomRatio = static_cast<float>(GetRandomNumber(100, 1)) * 0.01f;
		float RandomStartRatio = static_cast<float>(GetRandomNumber(50, 51)) * 0.01f;
		Vector2 RandomStandard = {};
		RandomStandard.x = Standard2D.x + (RandomStartRatio * _Direction.x) + RandomRatio * (Range.x - Standard2D.x);
		RandomStandard.y = Standard2D.y + (RandomStartRatio * _Direction.y) + RandomRatio * (Range.y - Standard2D.y);

		// 해당 점에서 랜덤한 위치로 이동시킨다. direction 비율로 해야함 
		Vector2 RandomOffset = {};

		// 보간 계산
		float Distance = Vector2::Distance(RandomStandard, Range); // 0 ~ 3
		int offsetX = Interpolation<int>(0.f, 3.f, Distance, 100, 1);
		int offsetY = Interpolation<int>(0.f, 3.f, Distance, 100, 1);

		RandomOffset.x = static_cast<float>(GetRandomNumber(offsetX, -50)) * 0.01f;
		RandomOffset.y = static_cast<float>(GetRandomNumber(offsetY, -50)) * 0.01f;

		RandomStandard += RandomOffset;
		newPos.x = RandomStandard.x;
		newPos.y = RandomStandard.y;

		SetPos(newPos);

	}

	void CBlood::SetBloodPosition_Round(Vector3 _Standard)
	{
		float randX = static_cast<float>(GetRandomNumber(20, -10) * 0.01f);
		float randY = static_cast<float>(GetRandomNumber(20, -10) * 0.01f);

		Vector3 center = _Standard;
		Vector3 randomPoint = { center.x + randX, center.y + randY, 3.f };

		SetPos(randomPoint);
	}

	void CBlood::AnimCompleteEvent()
	{
		if (!mbRewind && !mbReplay)
		{
			RenderingBlockOn();
			mbBloodDead = true;
			GetComponent<CRigidBody>()->SetGravity(0.f);
		}
	}


}