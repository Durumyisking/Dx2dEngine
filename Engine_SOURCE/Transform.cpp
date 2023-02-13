#include "Transform.h"
#include "Camera.h"

namespace dru
{
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mFoward(Vector3::Forward)
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
		// ���� ���� ���� obj �̵�ó��
	}

	void CTransform::fixedupdate()
	{
		// �������� ���� ��ġ�� ������Ʈ


		// ���� ��� ����
		SetWorldMatrix();


		// ������� ����
		SetConstantBuffer();


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

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation); // �������� ���� ���������ش�.
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

	}


	void CTransform::SetConstantBuffer()
	{
		// ������� ������ �ش� ������ۿ� �� ����

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];

		// ����� ����
		TransformCB transformCB = {};
		transformCB.world = mWorld;
		transformCB.view = CCamera::GetViewMatrix();
		transformCB.projection = CCamera::GetProjectionMatrix();


		cb->Bind(&transformCB);
		cb->SetPipeline(eShaderStage::VS);

	}


}