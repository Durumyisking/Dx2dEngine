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
		int iData;
		float fData1;
		float fData2;
		float fData3;
		float fData4;
		float fData5;
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
		int		bFadeSwitch;
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

}

