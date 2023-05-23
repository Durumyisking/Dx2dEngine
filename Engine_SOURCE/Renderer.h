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

#define RED		Vector4{1.f, 0.f, 0.f, 1.f}
#define GREEN	Vector4{0.f, 1.f, 0.f, 1.f}
#define BLUE	Vector4{0.f, 0.f, 1.f, 1.f}
#define MAGENTA Vector4{1.f, 0.f, 1.f, 1.f}
#define PEARL	Vector4{0.f, 1.f, 1.f, 1.f}
#define ORANGE	Vector4{0.9f, 0.72f, 0.31f, 1.f}
#define YELLOW	Vector4{0.9569f, 0.6672f, 0.4588f, 1.f}
#define ORANGE_YELLOW	Vector4{0.9569f, 0.6672f, 0.4588f, 1.f}

#define LIGHT_RED		Vector4{1.f, 0.f, 0.f, 0.5f}
#define LIGHT_GREEN		Vector4{0.f, 1.f, 0.f, 0.5f}
#define LIGHT_BLUE		Vector4{0.f, 0.f, 1.f, 0.5f}
#define LIGHT_MAGENTA	Vector4{1.f, 0.f, 1.f, 0.5f}
#define LIGHT_PEARL		Vector4{0.f, 1.f, 1.f, 0.5f}
#define LIGHT_ORANGE	Vector4{0.9f, 0.72f, 0.31f, 0.5f}
#define LIGHT_YELLOW	Vector4{0.9569f, 0.6672f, 0.4588f, 0.5f}
#define LIGHT_ORANGE_YELLOW	Vector4{0.9569f, 0.6672f, 0.4588f, 1.f}


namespace dru::renderer
{

	struct Vertex
	{
		Vector4 pos;
		Vector4	color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM) // 구조체 만드는거임
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
		float fData5;
		float fData6;
		float fData7;
		float fData8;

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
		Vector4 worldPosition;
		Vector4 startSize;
		Vector4 startColor;
		Vector4 endColor;

		UINT maxParticles;
		UINT simulationSpace;
		float radius;
		float deltaTime;

		float startSpeed;
		float endSpeed;
		float maxLifeTime;
		float minLifeTime;

		float startAngle;
		float endAngle;
		float elapsedTime;
		float gravity;

		float force;
		float radian;
		Vector2 padding;
	};
	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 noiseSize;
		float noiseTime;
	};
	CBUFFER(PostProcessCB, CBSLOT_POSTPROCESS)
	{
		Vector2 Resolution;

		float ElapsedTime;

		float wave_amount;
		float wave_speed;
		float wave_distortion;
	};
	CBUFFER(LaserHitCB, CBSLOT_LASERHIT)
	{
		float ElapsedTimeX;
		float ElapsedTimeY;
		float PrevElapsedTimeY;
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
	void release(); // 그리는 방식이 여러개일때 여러개를 할당하는게 아니라
					// 그리는 방식을 변경할때 할당된 곳에 그리는 방식의 객체들을 교체만 해준다 -> 오래걸림
					// 아직 gpu의 vram의 용량이 ram보다 한참 작아서그럼
	
	void Render();

	void PushLightAttribute(LightAttribute _attribute);
	void BindLight();
	void BindNoiseTexture();
	void CopyRenderTarget();
}

