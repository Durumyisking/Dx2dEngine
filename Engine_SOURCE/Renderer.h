#pragma once
#include "CommonInclude.h"
#include "druMath.h"
#include "GraphicDevice.h"

#include "Mesh.h"
#include "Shader.h"

#include "ConstantBuffer.h"

#include "Camera.h"


using namespace dru::math;
using namespace dru::graphics;

namespace dru::renderer
{

	struct Vertex
	{
		Vector4 pos;
		Vector4	color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM) // ����ü ����°���
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)	
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(FadeCB, CBSLOT_FADE)
	{
		float	fValue;
		int		bFadeType;
		int		bTextureType;
	};


	// vertex data
	extern Vertex	arrVertex[4];
	extern CConstantBuffer* constantBuffers[];	
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> BlendState[];

	extern std::vector<CCamera*> Cameras[];

	void Initialize();
	void release(); // �׸��� ����� �������϶� �������� �Ҵ��ϴ°� �ƴ϶�
					// �׸��� ����� �����Ҷ� �Ҵ�� ���� �׸��� ����� ��ü���� ��ü�� ���ش� -> �����ɸ�
					// ���� gpu�� vram�� �뷮�� ram���� ���� �۾Ƽ��׷�
	
	void Render();


}

