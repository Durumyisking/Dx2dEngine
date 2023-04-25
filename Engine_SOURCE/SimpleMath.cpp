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

	Vector3 RotateVector(Vector3 vec, float theta)
	{

		// 회전 축 벡터를 설정합니다. 이 경우 Z축을 회전축으로 사용합니다.
		Vector3 axis = { 0.f, 0.f, 1.f };

		// 주어진 각도(theta)를 라디안으로 변환합니다.
		float radians = toRadian(theta);

		// 회전 행렬을 생성합니다.
		XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, radians);

		// 벡터를 XMVECTOR 형식으로 변환합니다.
		XMVECTOR vecToRotate = XMLoadFloat3(&vec);

		// 회전 행렬과 벡터를 곱해 회전시킵니다.
		XMVECTOR rotatedVec = XMVector3Transform(vecToRotate, rotationMatrix);

		// 회전된 벡터를 Vector3 형식으로 다시 변환합니다.
		XMStoreFloat3(&vec, rotatedVec);

		return vec;
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

	Vector3 ProjectOnPlane(Vector3 _Direction, Vector3 _PlaneNormal)
	{
		// 벡터를 평면과 수직인 벡터로 분해합니다.
		Vector3 vertical = _Direction.Dot(_PlaneNormal) * _PlaneNormal;

		// 평면과 수직인 벡터를 빼서 벡터를 평면에 투영합니다.
		Vector3 projected = _Direction - vertical;

		return projected;
	}

	Vector3 AdjustDirectionToSlope(Vector3 _Direction, Vector3 _PlaneNormal)
	{
		Vector3 Result = ProjectOnPlane(_Direction, _PlaneNormal);
		Result.Normalize();
		return Result;
	}

	int GetRandomNumber(int _Range, int _StartNumber)
	{
		void* p = new int();
		srand((int)p);
		int randvalue = (rand() % (_Range + 1)) + _StartNumber;;
		delete p;

		return randvalue;
	}



}
