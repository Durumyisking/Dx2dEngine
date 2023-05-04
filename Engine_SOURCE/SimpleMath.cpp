#include "SimpleMath.h"

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

	Vector3 RotateVector(Vector3 vec, float theta)
	{

		// ȸ�� �� ���͸� �����մϴ�. �� ��� Z���� ȸ�������� ����մϴ�.
		Vector3 axis = { 0.f, 0.f, 1.f };

		// �־��� ����(theta)�� �������� ��ȯ�մϴ�.
		float radians = toRadian(theta);

		// ȸ�� ����� �����մϴ�.
		XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, radians);

		// ���͸� XMVECTOR �������� ��ȯ�մϴ�.
		XMVECTOR vecToRotate = XMLoadFloat3(&vec);

		// ȸ�� ��İ� ���͸� ���� ȸ����ŵ�ϴ�.
		XMVECTOR rotatedVec = XMVector3Transform(vecToRotate, rotationMatrix);

		// ȸ���� ���͸� Vector3 �������� �ٽ� ��ȯ�մϴ�.
		XMStoreFloat3(&vec, rotatedVec);

		return vec;
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
		Result.Normalize();
		return Result;
	}

	int GetRandomNumber(int _Range, int _StartNumber)
	{
		SM_srand(seed);
		int randvalue = (SM_rand() % (_Range + 1)) + _StartNumber;;

		return randvalue;
	}


	float RotateToHead(Vector3 _Direction, Vector3 _Basis)
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
