#pragma once
#include "CommonInclude.h"
#include "druMath.h"

using namespace dru::math;

namespace dru::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4	color;
	};

	void SetUpState();
	void LoadBuffer();
	void LoadShader();

	void init();
	void release(); // �׸��� ����� �������϶� �������� �Ҵ��ϴ°� �ƴ϶�
					// �׸��� ����� �����Ҷ� �Ҵ�� ���� �׸��� ����� ��ü���� ��ü�� ���ش� -> �����ɸ�
					// ���� gpu�� vram�� �뷮�� ram���� ���� �۾Ƽ��׷�
	
}

