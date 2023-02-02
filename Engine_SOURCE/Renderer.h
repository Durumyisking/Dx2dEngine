#pragma once
#include "CommonInclude.h"
#include "druMath.h"
#include "GraphicDevice.h"

#include "Mesh.h"
#include "Shader.h"

#include "ConstantBuffer.h"

using namespace dru::math;
using namespace dru::graphics;

namespace dru::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4	color;
		Vector2 uv;
	};


	// vertex data
	extern Vertex	arrVertex[4];
	
	
	extern CConstantBuffer* constantBuffers[static_cast<UINT>(eCBType::End)];


	extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
	



	void Initialize();
	void release(); // 그리는 방식이 여러개일때 여러개를 할당하는게 아니라
					// 그리는 방식을 변경할때 할당된 곳에 그리는 방식의 객체들을 교체만 해준다 -> 오래걸림
					// 아직 gpu의 vram의 용량이 ram보다 한참 작아서그럼
	
}

