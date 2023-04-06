#pragma once
#include "CommonInclude.h"
#include "druMath.h"
#include "GraphicDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Light.h"
#include "StructedBuffer.h"

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
		int iData1;
		int iData2;
		int iData3;
		int iData4;

		float fData1;
		float fData2;
		float fData3;
		float fData4;

		Vector2 xy1;
		Vector2 xy2;
		Vector2 xy3;
		Vector2 xy4;

		Vector3 xyz1;
		float	xyzPadding1;
		Vector3 xyz2;
		float	xyzPadding2;
		Vector3 xyz3;
		float	xyzPadding3;
		Vector3 xyz4;
		float	xyzPadding4;

		Vector4 xyzw1;
		Vector4 xyzw2;
		Vector4 xyzw3;
		Vector4 xyzw4;

		Matrix matrix1;
		Matrix matrix2;
		Matrix matrix3;
		Matrix matrix4;
	};

	CBUFFER(GridCB, CBSLOT_GRID)	
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(ColorCB, CBSLOT_COLOR)
	{
		Vector4 RGBA;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 LT;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	CBUFFER(LightCB, CBSLOT_LIGHTCOUNT)
	{	
		UINT lightCount;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_LIGHTCOUNT)
	{
		Vector4 Color;
		UINT elementCount;
		float deltaTime;
		float elapsedTime;
	};
	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 noiseSize;
	};


	// vertex data
	extern Vertex	RectVertexes[4];

	extern CConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendState[];

	extern std::vector<CCamera*> Cameras[];

	extern CCamera* mainCamera;
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;

	extern CStructedBuffer* lightBuffer;



	void Initialize();
	void release(); // �׸��� ����� �������϶� �������� �Ҵ��ϴ°� �ƴ϶�
					// �׸��� ����� �����Ҷ� �Ҵ�� ���� �׸��� ����� ��ü���� ��ü�� ���ش� -> �����ɸ�
					// ���� gpu�� vram�� �뷮�� ram���� ���� �۾Ƽ��׷�
	
	void Render();

	void PushLightAttribute(LightAttribute _attribute);
	void BindLight();
	void BindNoiseTexture();
}

