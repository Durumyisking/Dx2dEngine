#pragma once
#include "Component.h"
#include "ConstantBuffer.h"
#include "Renderer.h"

using namespace dru::math;
using namespace dru::graphics;
using namespace dru::renderer;
namespace dru
{
	class CTransform : public CComponent
	{
	public:
		CTransform();
		virtual ~CTransform();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;


		void SetPosition(Vector3 _Value) { mPosition = _Value; }
		void SetRotation(Vector3 _Value) { mRotation = _Value; }
		void SetRotationX(float _Value) { mRotation.x = _Value; }
		void SetRotationY(float _Value) { mRotation.y = _Value; }
		void SetRotationZ(float _Value) { mRotation.z = _Value; }
		void SetScale(Vector3 _Value) { mScale = _Value; }

		void SetWorldMatrix();

		void SetConstantBuffer();


		CTransform* GetParent() const { return mParent; }
		void SetParent(CGameObj* _Parent);

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Matrix& GetWorldMatrix() { return mWorld; }
	
	private:
		CTransform* mParent;

		Vector3	mForward;
		Vector3 mRight;
		Vector3 mUp;

		Vector3 mPosition;
		Vector3	mRotation;
		Vector3	mScale;

		Matrix	mWorld;

	};
}

