#include "Collider2D.h"
#include "GameObj.h"
#include "Renderer.h"
#include "Script.h"

namespace dru
{
	UINT32 CCollider2D::colliderID = 0;

	CCollider2D::CCollider2D()
		: CComponent(eComponentType::Collider)
		, mState(eCollisionState::End)
		, mType(eColliderType::End)
		, mTransform(nullptr)
		, mScale(Vector2::One)
		, mCenter(Vector2::Zero)
		, mbTrigger(false) // 이거 공부하자
		, mCollisionCount(0)
		, mRadius(0.f)
		, mColliderID(colliderID++)
	{

	}

	CCollider2D::~CCollider2D()
	{
	}

	void CCollider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<CTransform>();
	}

	void CCollider2D::update()
	{
	
	}

	void CCollider2D::fixedUpdate()
	{
		if (nullptr == mTransform)
			return;

		Vector3 scale = mTransform->GetScale();
		scale *= Vector3(mScale.x, mScale.y, 1.f);

		Vector3 rotation = mTransform->GetRotation();
		rotation = rotation * XM_PI / 180;

		Vector3 position = mTransform->GetPosition();
		mPosition = position + Vector3(mCenter.x, mCenter.y, 0.f);

		Matrix scaleMatrix = Matrix::CreateScale(scale);
		Matrix rotationMatrix;
		rotationMatrix = Matrix::CreateRotationX(rotation.x);
		rotationMatrix *= Matrix::CreateRotationY(rotation.y);
		rotationMatrix *= Matrix::CreateRotationZ(rotation.z);

		Matrix positionMatrix;
		positionMatrix.Translation(Vector3(mPosition.x, mPosition.y, mPosition.z));

		Matrix worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;

		DebugMesh meshAttribute = {};
		meshAttribute.position = Vector3(mPosition.x, mPosition.y, mPosition.z);
		meshAttribute.radius = mRadius;
		meshAttribute.rotation = rotation;
		meshAttribute.scale = scale;
		meshAttribute.type = mType;
		meshAttribute.state = mState;
		

		renderer::debugMeshes.push_back(meshAttribute);
	}

	void CCollider2D::render()
	{

	}

	void CCollider2D::OnCollisionEnter(CCollider2D* _oppo)
	{
		++mCollisionCount;
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnCollisionEnter(_oppo);
		}
	}

	void CCollider2D::OnCollision(CCollider2D* _oppo)
	{
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnCollision(_oppo);
		}
	}

	void CCollider2D::OnCollisionExit(CCollider2D* _oppo)
	{
		--mCollisionCount;
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnCollisionExit(_oppo);
		}
	}

	void CCollider2D::OnTriggerEnter(CCollider2D* _oppo)
	{
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnTriggerEnter(_oppo);
		}
	}

	void CCollider2D::OnTrigger(CCollider2D* _oppo)
	{
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnTrigger(_oppo);
		}
	}

	void CCollider2D::OnTriggerExit(CCollider2D* _oppo)
	{
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			script->OnTriggerExit(_oppo);
		}
	}

}