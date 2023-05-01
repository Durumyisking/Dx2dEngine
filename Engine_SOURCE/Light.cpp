#include "Light.h"
#include "Transform.h"
#include "GameObj.h"
#include "Renderer.h"

namespace dru
{
	CLight::CLight()
		: CComponent(eComponentType::Light)
	{

	}

	CLight::~CLight()
	{
	}

	void CLight::Initialize()
	{
	}

	void CLight::update()
	{
	}

	void CLight::fixedUpdate()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		math::Vector3 position = tr->GetWorldPosition();

		mAttribute.position = Vector4(position.x, position.y, position.z, 1.f);
		mAttribute.direction = Vector4(tr->Right().x, tr->Right().y, tr->Right().z, 1.f); // right를 정면으로 둔다.

		renderer::PushLightAttribute(mAttribute);
	}

	void CLight::render()
	{
	}


}