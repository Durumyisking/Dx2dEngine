#include "Transform.h"
#include "Camera.h"
#include "GameObj.h"

namespace dru
{
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mParent(nullptr)
		, mPosition(Vector3::Zero)
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
		// ���� ���� ���� obj �̵�ó��
	}

	void CTransform::fixedUpdate()
	{
		// ���� ��� ����
		SetWorldMatrix();
	}

	void CTransform::render()
	{

	}
	void CTransform::SetWorldMatrix()
	{
		Matrix scale = Matrix::CreateScale(mScale);
	
		
		Vector3 rotation = DegreeToRadian(mRotation);
		Matrix rotationMatrix;
		rotationMatrix = Matrix::CreateRotationX(rotation.x);
		rotationMatrix *= Matrix::CreateRotationY(rotation.y);
		rotationMatrix *= Matrix::CreateRotationZ(rotation.z);

		Matrix positionMatrix;
		positionMatrix.Translation(mPosition);

		mWorld = scale * rotationMatrix * positionMatrix;

		mForward = Vector3::TransformNormal(Vector3::Forward, rotationMatrix); // �������� ���� ���������ش�.
		mRight = Vector3::TransformNormal(Vector3::Right, rotationMatrix);
		mUp = Vector3::TransformNormal(Vector3::Up, rotationMatrix);

		
		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}


	void CTransform::SetConstantBuffer()
	{
		// ����� ����
		TransformCB transformCB = {};
		transformCB.world = mWorld;
		transformCB.view = CCamera::GetGpuViewMatrix();
		transformCB.projection = CCamera::GetGpuProjectionMatrix();


		// ������� ������ �ش� ������ۿ� �� ����
		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&transformCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);

	}

	Vector3 CTransform::DegreeToRadian(Vector3 _Degree)
	{
		return _Degree * XM_PI / 180;
	}


	void CTransform::SetParent(CGameObj* _Parent)
	{
		CTransform* tr = _Parent->GetComponent<CTransform>();

		mParent = tr;
	}


}