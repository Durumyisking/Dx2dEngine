#include "SimpleMath.h"

namespace dru::math
{

	Vector3 RotateZ(const Vector3& V, const float degree)
	{

		float rad = toRadian(degree); // 라디안 단위로 변환
		float s = sin(rad);
		float c = cos(rad);

		Vector3 rotated = {};

		rotated.x = V.x * c - V.y * s;
		rotated.y = V.x * s + V.y * c;
		rotated.z = V.z;

		return rotated;
	}

	float toRadian(float _degree)
	{
		return _degree * XM_PI / 180.f;
	}

	float toDegree(float _radian)
	{
		return _radian * 180 / XM_PI;
	}

	float GetRadianFromTwoPointZ(const Vector3& V1, const Vector3& V2)
	{
		Vector3 rotation = {};

		// x축과 mousepos <-> slashobj 각도 받음 라디안
		rotation.z = atan2(V1.y - V2.y, V1.x - V2.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;
		// 인자로 degree 넣음

		return rotation.z;
	}

}
