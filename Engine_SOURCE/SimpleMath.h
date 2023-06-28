#pragma once
#include "druMath.h"

namespace dru::math
{
	int SM_rand();
	void SM_srand(unsigned int _seed);

	Vector3 RotateZ(const Vector3& V, const float degree);
    float toRadian(float _degree);
	float toDegree(float _radian);

	POINT WorldToWindowPos(const Vector3& worldPos);

	Vector3 RotateVector(Vector3 _vec, float _degree);


	float GetDegreeFromTwoPointZ(const Vector3& V1, const Vector3& V2);
	float GetDegreeFromTwoPointZ_0180(const Vector3& V1, const Vector3& V2);

	Vector3 ProjectOnPlane(Vector3 _Direction, Vector3 _PlaneNormal);
	Vector3 AdjustDirectionToSlope(Vector3 _Direction, Vector3 _PlaneNormal);

	int GetRandomNumber(int _Range, int _StartNumber = 0);

	float GetAngleFromDirection(Vector3 _Direction, Vector3 _Basis);

	float RotateToHead_360(Vector3 _Direction);

	template<typename T>
	T Interpolation(float _Start, float _End, float _Elapsed, T _ResultStart, T _ResultEnd)
	{
		float t = (_Elapsed - _Start) / (_End - _Start);
		T Result = static_cast<T>(_ResultStart + (_ResultEnd - _ResultStart) * t);

		return Result;
	}
}