#include "Transform.h"
#include "Camera.h"

namespace dru
{
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mParent(nullptr)
		, mPosition(Vector3::One)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mForward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp (Vector3::Up)
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
		// 실제 로직 게임 obj 이동처리
	}

	void CTransform::fixedupdate()
	{
		// 월드 행렬 세팅
		SetWorldMatrix();
	}

	void CTransform::render()
	{

	}
	void CTransform::SetWorldMatrix()
	{
		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix translation;
		translation.Translation(mPosition);

		mWorld = scale * rotation * translation;

		mForward = Vector3::TransformNormal(Vector3::Forward, rotation); // 기저벡터 같이 변형시켜준다.
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);


		if (nullptr != mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}


	void CTransform::SetConstantBuffer()
	{
		// 뷰행렬 세팅
		TransformCB transformCB = {};
		transformCB.world = mWorld;
		transformCB.view = CCamera::GetViewMatrix();
		transformCB.projection = CCamera::GetProjectionMatrix();


		// 상수버퍼 가져와 해당 상수버퍼에 값 세팅
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&transformCB);
		cb->SetPipeline(eShaderStage::VS);

	}


}