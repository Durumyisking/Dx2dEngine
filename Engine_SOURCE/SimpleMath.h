#pragma once
#include "druMath.h"

namespace dru::math
{
	Vector3 RotateZ(const Vector3& V, const float degree);
    float toRadian(float _degree);
	float toDegree(float _radian);
	float GetRadianFromTwoPointZ(const Vector3& V1, const Vector3& V2);


}

