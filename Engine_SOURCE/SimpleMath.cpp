#include "SimpleMath.h"

namespace dru::math
{

	Vector3 RotateZ(const Vector3& V, const float degree)
	{

		float rad = toRadian(degree); // ���� ������ ��ȯ
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

		// x��� mousepos <-> slashobj ���� ���� ����
		rotation.z = atan2(V1.y - V2.y, V1.x - V2.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;
		// ���ڷ� degree ����

		return rotation.z;
	}

}
