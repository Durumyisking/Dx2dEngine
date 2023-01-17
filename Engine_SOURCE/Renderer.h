#pragma once
#include "CommonInclude.h"
#include "druMath.h"
#include "GraphicDevice.h"

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

	// vertex buffer
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;

	// idx buffer
	extern ID3D11Buffer* triangleIndexBuffer;

	// idx buffer
	extern ID3D11Buffer* triangleConstantBuffer;

	// VS
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;
	 
	 // PS
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;
		
	// Input Layout
	extern ID3D11InputLayout* triangleLayout; // ���� ���ۿ� �������� �������ִ¾�


	void init();
	void release(); // �׸��� ����� �������϶� �������� �Ҵ��ϴ°� �ƴ϶�
					// �׸��� ����� �����Ҷ� �Ҵ�� ���� �׸��� ����� ��ü���� ��ü�� ���ش� -> �����ɸ�
					// ���� gpu�� vram�� �뷮�� ram���� ���� �۾Ƽ��׷�
	
}

