#pragma once
#include "CommonInclude.h"
#include "druMath.h"
#include "GraphicDevice.h"

#include "Mesh.h"
#include "Shader.h"

using namespace dru::math;
using namespace dru::graphics;

namespace dru::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4	color;
	};


	// vertex data
	extern Vertex	arrVertex[4];

	extern CMesh*	Mesh;
	extern CShader* Shader;
	extern Vector4* mpos;


	extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	

	void init();
	void release(); // �׸��� ����� �������϶� �������� �Ҵ��ϴ°� �ƴ϶�
					// �׸��� ����� �����Ҷ� �Ҵ�� ���� �׸��� ����� ��ü���� ��ü�� ���ش� -> �����ɸ�
					// ���� gpu�� vram�� �뷮�� ram���� ���� �۾Ƽ��׷�
	
}

