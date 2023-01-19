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

	extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	// idx buffer
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;

		
	// Input Layout
	extern Microsoft::WRL::ComPtr<ID3D11InputLayout> triangleLayout; // 정점 버퍼에 정점정보 세팅해주는애


	void init();
	void release(); // 그리는 방식이 여러개일때 여러개를 할당하는게 아니라
					// 그리는 방식을 변경할때 할당된 곳에 그리는 방식의 객체들을 교체만 해준다 -> 오래걸림
					// 아직 gpu의 vram의 용량이 ram보다 한참 작아서그럼
	
}

