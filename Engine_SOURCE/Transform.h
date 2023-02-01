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
		virtual void fixedupdate() override;
		virtual void render() override;

		void SetConstantBuffer();

		void SetPosition(Vector4 _Value) { mPosition = _Value; }
		void SetRotation(Vector4 _Value) { mRotation = _Value; }
		void SetScale(Vector4 _Value) { mScale = _Value; }

		Vector4 GetPosition() { return mPosition; }
		Vector4 GetRotation() { return mRotation; }
		Vector4 GetScale() { return mScale; }
	private:
		Vector4 mPosition;
		Vector4 mRotation;
		Vector4 mScale;


	};
}

