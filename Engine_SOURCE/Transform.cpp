#include "Transform.h"
#include "Camera.h"
#include "GameObj.h"

namespace dru
{
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mParent(nullptr)
		, mRelativeForward(Vector3::Forward)
		, mRelativeRight(Vector3::Right)
		, mRelativeUp(Vector3::Up)
		, mWorldForward(Vector3::Forward)
		, mWorldRight(Vector3::Right)
		, mWorldUp(Vector3::Up)
		, mRelativePosition(Vector3::Zero)
		, mRelativeRotation(Vector3::Zero)
		, mRelativeScale(Vector3::One)
		, mInheritParentScale(true)
		, mWorldPosition(Vector3::Zero)
		, mWorldRotation(Vector3::Zero)
		, mWorldScale(Vector3::One)

	{
	}

	CTransform::~CTransform()
	{
	}

	void CTransform::Initialize()
	{
	}

	void CTransform::update()
	{
	}

	void CTransform::fixedUpdate()
	{
		// 렌더링에 사용될 위치값을 업데이트.
		// 1. 월드 행렬 생성
		// - 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mRelativeScale);
		mWorldScale = mRelativeScale;

		// - 회전 변환 행렬
		Vector3 rot = mRelativeRotation * XM_PI / 180; // to radian
		Matrix rotation;
		rotation = Matrix::CreateRotationX(rot.x);
		rotation *= Matrix::CreateRotationY(rot.y);
		rotation *= Matrix::CreateRotationZ(rot.z);
		mWorldRotation = rot;


		// - 이동 변환 행렬
		Matrix position;
		position.Translation(mRelativePosition);
		mWorldPosition = mRelativePosition;

		mWorld = scale * rotation * position;
		mWorldForward = mRelativeForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mWorldRight = mRelativeRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mWorldUp = mRelativeUp = Vector3::TransformNormal(Vector3::Up, rotation);

		if (mParent)
		{
			Matrix parentWorld = mParent->GetWorldMatrix();

			if (!mInheritParentScale)
			{
				Vector3 worldPos, worldScale;
				Quaternion worldRot;
				parentWorld.Decompose(worldScale, worldRot, worldPos);
				Matrix parentWorldNoScale = Matrix::CreateScale(1.f) * Matrix::CreateFromQuaternion(worldRot) * Matrix::CreateTranslation(worldPos);
				mWorld = mWorld * parentWorldNoScale;
			}
			else
			{
				mWorld *= parentWorld;
			}

			// - 월드 좌표, 크기, 회전 갱신
			Quaternion worldRot;
			mWorld.Decompose(mWorldScale, worldRot, mWorldPosition);
			Vector3 quatToRadRot = worldRot.ToEuler();
			mWorldRotation = quatToRadRot;

			mWorldForward = Vector3::TransformNormal(mRelativeForward, rotation);
			mWorldRight = Vector3::TransformNormal(mRelativeRight, rotation);
			mWorldUp = Vector3::TransformNormal(mRelativeUp, rotation);
			mWorldForward.Normalize();
			mWorldRight.Normalize();
			mWorldUp.Normalize();
		}
	}

	void CTransform::render()
	{
	}

	void CTransform::SetConstantBuffer()
	{
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = CCamera::GetGpuViewMatrix();
		trCb.projection = CCamera::GetGpuProjectionMatrix();

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void CTransform::SetParent(CGameObj* parent)
	{
		mParent = parent->GetComponent<CTransform>();
	}


}