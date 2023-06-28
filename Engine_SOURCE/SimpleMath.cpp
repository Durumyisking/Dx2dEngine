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
		// ȸ�� �� ���͸� �����մϴ�. �� ��� Z���� ȸ�������� ����մϴ�.
		Vector3 axis = { 0.f, 0.f, 1.f };

		// �־��� ����(theta)�� �������� ��ȯ�մϴ�.
		float radians = toRadian(_degree);

		// ȸ�� ����� �����մϴ�.
		XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, radians);

		// ���͸� XMVECTOR �������� ��ȯ�մϴ�.
		XMVECTOR vecToRotate = XMLoadFloat3(&_vec);

		// ȸ�� ��İ� ���͸� ���� ȸ����ŵ�ϴ�.
		XMVECTOR rotatedVec = XMVector3Transform(vecToRotate, rotationMatrix);

		// ȸ���� ���͸� Vector3 �������� �ٽ� ��ȯ�մϴ�.
		XMStoreFloat3(&_vec, rotatedVec);

		return _vec;
	}

	float GetDegreeFromTwoPointZ(const Vector3& V1, const Vector3& V2)
	{
		Vector3 rotation = {};

		// x��� mousepos <-> slashobj ���� ���� ����
		rotation.z = atan2(V1.y - V2.y, V1.x - V2.x);
		// radian to degree
		rotation.z = rotation.z * 180 / XM_PI;

		return rotation.z;
	}

	float GetDegreeFromTwoPointZ_0180(const Vector3& V1, const Vector3& V2)
	{
		Vector3 rotation = {};
		rotation.z = atan2(V2.x - V1.x, V2.y - V1.y) * 180 / XM_PI;

		// 0������ 180���� ��ȯ
		if (rotation.z < 0)
		{
			rotation.z *= -1.f;
		}

		return rotation.z;
	}

	Vector3 ProjectOnPlane(Vector3 _Direction, Vector3 _PlaneNormal)
	{
		_PlaneNormal.Normalize();
		
		// ���͸� ���� ������ ���ͷ� �����մϴ�.
		Vector3 verticalVector = _Direction.Dot(_PlaneNormal) * _PlaneNormal;

		// ���� ������ ���͸� ���� ���͸� ��鿡 �����մϴ�.
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

		// �̵� ����� forward ���� ���� ������ ���մϴ�.
		float angle = acos(_Direction.Dot(_Basis)) * 180.f / XM_PI;

		// �̵� ������ y���� ���� ���, ������ �����մϴ�.
		if (_Direction.y < 0.f)
		{
			angle = -angle;
		}
		return angle;
	}

	float RotateToHead_360(Vector3 _Direction)
	{
		Vector3 forward = { 1.f, 0.f, 0.f }; // �ʱⰪ���� x���� ����մϴ�.

		// �̵� ����� forward ���� ���� ������ ���մϴ�.
		float angle = acos(_Direction.Dot(forward)) * 180.f / XM_PI;

		return angle;
	}



}
