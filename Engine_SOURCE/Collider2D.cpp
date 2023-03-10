#include "Collider2D.h"
#include "GameObj.h"
#include "Renderer.h"
#include "Script.h"

namespace dru
{
	UINT CCollider2D::mColliderID = 0;
	CCollider2D::CCollider2D()
		: CComponent(eComponentType::Collider)
		, mType(eColliderType::End)
		, mTransform(nullptr)
		, mScale(Vector2::One)
		, mCenter(Vector2::Zero)
		, mbTrigger(false) // 이거 공부하자
		, mCollisionCount(0)
	{
		mColliderID = mColliderID++;
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
		scale *= Vector3(mScale.x, mScale.y, 1.f);
		mRadius = mScale.x;

		Vector3 rotation = mTransform->GetRotation();

		Vector3 position = mTransform->GetPosition();
		Vector3 colliderPos = position + Vector3(mCenter.x, mCenter.y, 0.f);
		mPosition = colliderPos;

		Matrix scaleMatrix = Matrix::CreateScale(scale);
		Matrix rotationMatrix;
		rotationMatrix = Matrix::CreateRotationX(rotation.x);
		rotationMatrix *= Matrix::CreateRotationY(rotation.y);
		rotationMatrix *= Matrix::CreateRotationZ(rotation.z);

		Matrix positionMatrix;
		positionMatrix.Translation(Vector3(colliderPos.x, colliderPos.y, colliderPos.z));

		Matrix worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;

		DebugMesh meshAttribute = {};
		meshAttribute.position = Vector3(colliderPos.x, colliderPos.y, colliderPos.z);
		meshAttribute.radius = mRadius;
		meshAttribute.rotation = rotation;
		meshAttribute.scale = scale;
		meshAttribute.type = mType;
		
		renderer::debugMeshes.push_back(meshAttribute);
	}

	void CCollider2D::render()
	{

		CConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Color];
		renderer::ColorCB data = {};

		if (mCollisionCount > 0)
		{
			data.RGBA = Vector4(255.f, 0.f, 0.f, 1.f);
		}
		else
		{
			data.RGBA = Vector4(0.f, 255.f, 0.f, 1.f);
		}

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::PS);
	}

	void CCollider2D::OnCollisionEnter(CCollider2D* _oppo)
	{
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			++mCollisionCount;
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
		const std::vector<CScript*>& scripts = GetOwner()->GetScripts();
		for (CScript* script : scripts)
		{
			--mCollisionCount;
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