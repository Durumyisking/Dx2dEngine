#include "SimpleMath.h"
#include "Application.h"
#include "Renderer.h"
#include "GameObj.h"

extern dru::CApplication application;

namespace dru::math
{
	static unsigned long int seed = 1;
	/* rand: return pseudo-random integer on 0..32767 */
	int SM_rand()
	{
		seed = seed * 1103515245 + 12345;
		return (unsigned int)(seed / 65536) % 32768;
	}
	/* srand: set seed for rand() */
	void SM_srand(unsigned int _seed)
	{
		seed = _seed;
	}

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

	POINT WorldToWindowPos(const Vector3& worldPos)
	{
		RECT windowRect;
		GetClientRect(application.GetHwnd(), &windowRect);

		Vector2 resolutionRatio = application.GetResolutionRatio();

		Vector2 windowPos;
		if (renderer::mainCamera)
		{
			Vector3 camPos = renderer::mainCamera->GetOwner()->GetWorldPos();
			windowPos.x = (worldPos.x - camPos.x) * 100.f; 
			windowPos.y = (worldPos.y - camPos.y) * -100.f; 
			//windowPos.x = (worldPos.x) * 100.f;
			//windowPos.y = (worldPos.y) * 100.f;
		}
		windowPos.x /= resolutionRatio.x;
		windowPos.y /= resolutionRatio.y;
		windowPos.x += (windowRect.right - windowRect.left) * 0.5f;
		windowPos.y += (windowRect.bottom - windowRect.top) * 0.5f;

		POINT ptResult;
		ptResult.x = static_cast<LONG>(windowPos.x);
		ptResult.y = static_cast<LONG>(windowPos.y);

		ClientToScreen(application.GetHwnd(), &ptResult);

		return ptResult;
	}

	Vector3 RotateVector(Vector3 _vec, float _degree)
	{
		// 회전 축 벡터를 설정합니다. 이 경우 Z축을 회전축으로 사용합니다.
		Vector3 axis = { 0.f, 0.f, 1.f };

		// 주어진 각도(theta)를 라디안으로 변환합니다.
		float radians = toRadian(_degree);

		// 회전 행렬을 생성합니다.
		XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, radians);

		// 벡터를 XMVECTOR 형식으로 변환합니다.
		XMVECTOR vecToRotate = XMLoadFloat3(&_vec);

		// 회전 행렬과 벡터를 곱해 회전시킵니다.
		XMVECTOR rotatedVec = XMVector3Transform(vecToRotate, rotationMatrix);

		// 회전된 벡터를 Vector3 형식으로 다시 변환합니다.
		XMStoreFloat3(&_vec, rotatedVec);

		return _vec;
	}

	float GetDegreeFromTwoPointZ(const Vector3& V1, const Vector3& V2)
	{
		Vector3 rotation = {};

		// x축과 mousepos <-> slashobj 각도 받음 라디안
		rotation.z = atan2(V1.y - V2.y, V1.x - V2.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;

		return rotation.z;
	}

	float GetDegreeFromTwoPointZ_0180(const Vector3& V1, const Vector3& V2)
	{
		Vector3 rotation = {};
		rotation.z = atan2(V2.x - V1.x, V2.y - V1.y) * 180 / XM_PI;

		// 0도에서 180도로 변환
		if (rotation.z < 0)
		{
			rotation.z *= -1.f;
		}

		return rotation.z;
	}

	Vector3 ProjectOnPlane(Vector3 _Direction, Vector3 _PlaneNormal)
	{
		_PlaneNormal.Normalize();
		
		// 벡터를 평면과 수직인 벡터로 분해합니다.
		Vector3 verticalVector = _Direction.Dot(_PlaneNormal) * _PlaneNormal;

		// 평면과 수직인 벡터를 빼서 벡터를 평면에 투영합니다.
		Vector3 projectedVector = _Direction - verticalVector;
		projectedVector.z = 0.f;
		return projectedVector;
	}

	Vector3 AdjustDirectionToSlope(Vector3 _Direction, Vector3 _PlaneNormal)
	{
		Vector3 Result = ProjectOnPlane(_Direction, _PlaneNormal);
		//Result.Normalize();
		return Result;
	}

	int GetRandomNumber(int _Range, int _StartNumber)
	{
		SM_srand(seed);
		int randvalue = (SM_rand() % _Range) + _StartNumber;;

		return randvalue;
	}


	float GetAngleFromDirection(Vector3 _Direction, Vector3 _Basis)
	{

		// 이동 방향과 forward 벡터 간의 각도를 구합니다.
		float angle = acos(_Direction.Dot(_Basis)) * 180.f / XM_PI;

		// 이동 방향이 y축을 향할 경우, 각도를 조정합니다.
		if (_Direction.y < 0.f)
		{
			angle = -angle;
		}
		return angle;
	}

	float RotateToHead_360(Vector3 _Direction)
	{
		Vector3 forward = { 1.f, 0.f, 0.f }; // 초기값으로 x축을 사용합니다.

		// 이동 방향과 forward 벡터 간의 각도를 구합니다.
		float angle = acos(_Direction.Dot(forward)) * 180.f / XM_PI;

		return angle;
	}



}
