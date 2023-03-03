#include "Collider2D.h"
#include "GameObj.h"
#include "Renderer.h"

namespace dru
{
	CCollider2D::CCollider2D()
		: CComponent(eComponentType::Collider)
		, mType(eColliderType::End)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mbTrigger(false) // 이거 공부하자
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
		Vector3 scale = mTransform->GetScale();
		scale *= Vector3(mSize.x, mSize.y, 1.f);

		Vector3 rotation = mTransform->GetRotation();

		Vector3 position = mTransform->GetPosition();
		Vector3 collilderPos = position + Vector3(mCenter.x, mCenter.y, 0.f);

		Matrix scaleMatrix = Matrix::CreateScale(scale);

		Matrix rotationMatrix;
		rotationMatrix = Matrix::CreateRotationX(rotation.x);
		rotationMatrix *= Matrix::CreateRotationY(rotation.y);
		rotationMatrix *= Matrix::CreateRotationZ(rotation.z);

		Matrix positionMatrix;
		positionMatrix.Translation(Vector3(collilderPos.x, collilderPos.y, collilderPos.z));

		Matrix worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;

		DebugMesh meshAttribute = {};
		meshAttribute.position = Vector3(collilderPos.x, collilderPos.y, collilderPos.z);
		meshAttribute.radius = 1.f;
		meshAttribute.rotation = rotation;
		meshAttribute.scale = scale;
		meshAttribute.type = mType;
		
		renderer::DebugMeshes.push_back(meshAttribute);
	}

	void CCollider2D::render()
	{
	}

}