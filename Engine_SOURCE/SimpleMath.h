#pragma once
#include "druMath.h"

namespace dru::math
{
	int SM_rand();
	void SM_srand(unsigned int _seed);

	Vector3 RotateZ(const Vector3& V, const float degree);
    float toRadian(float _degree);
	float toDegree(float _radian);

	Vector3 RotateVector(Vector3 vec, float theta);


	float GetDegreeFromTwoPointZ(const Vector3& V1, const Vector3& V2);

	Vector3 ProjectOnPlane(Vector3 _Direction, Vector3 _PlaneNormal);
	Vector3 AdjustDirectionToSlope(Vector3 _Direction, Vector3 _PlaneNormal);

	int GetRandomNumber(int _Range, int _StartNumber = 0);

	float RotateToHead(Vector3 _Direction, Vector3 _Basis);

	float RotateToHead_360(Vector3 _Direction);

}

