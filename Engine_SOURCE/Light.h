#pragma once
#include "Component.h"
#include "Graphics.h"

namespace dru
{
    class CLight :
        public CComponent
    {
	public:
		CLight();
		virtual ~CLight();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		graphics::LightAttribute GetAttribute() const { return mAttribute; }

		void SetDiffuse(math::Vector4 _diffuse) { mAttribute.diffuse = _diffuse; }
		void SetAmbient(math::Vector4 _ambient) { mAttribute.ambient = _ambient; }
		void SetType(enums::eLightType _type) { mAttribute.type = _type; }
		void SetRadius(float _radius) { mAttribute.radius = _radius; }
		void SetAngle(float _angle) { mAttribute.angle = _angle; }

		math::Vector4 GetDiffuse() { return mAttribute.diffuse ; }
		math::Vector4 GetAmbient() { return mAttribute.ambient; }
		enums::eLightType GetType() { return mAttribute.type; }
		float GetRadius() { return mAttribute.radius; }
		float GetAngle() { return mAttribute.angle; }



	private:
		graphics::LightAttribute mAttribute;
    };
}


