#pragma once
#include <wrl.h>
#include "druMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "../External/DirectXTK/lib/Debug/DirectXTK.lib")
#else
#pragma comment(lib, "../External/DirectXTK/lib/Release/DirectXTK.lib")
#endif

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2
#define CBSLOT_COLOR 3
#define CBSLOT_ANIMATION 4
#define CBSLOT_LIGHTCOUNT 5
#define CBSLOT_PARTICLESYSTEM 6
#define CBSLOT_NOISE			7
#define CBSLOT_POSTPROCESS		8
#define CBSLOT_LASERHIT			9

namespace dru::graphics
{
	enum class eValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		All,
		End,

	};

	enum class eBufferStage
	{
		VB,
		IB,
		CB,

		End,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};

	enum class eRasterizerType
	{
		SolidBack,
		SolidFront,
		SolidNone, // �ø� ����
		WireframeNone, // �����θ� �׸��� Topology�� ������ �׳� gpu���� ó�����ִ°�
		End,
	};

	enum class eDepthStencilType
	{
		Less, // �Ϲ����� ����
		Greater, // ���� �Ųٷ�
		NoWrite, // ��ġ�� �ƿ� �ȱ׸�
		None, // ���̹��� ��� ����
		End,
	};

	enum class eBlendStateType
	{
		Default,
		AlphaBlend,
		OneOne, // ���İ� ���� ��ü�� �� ����
		End,
	};

	enum class eRenderingMode
	{
		Opaque, // ������
		Cutout, // �Ϻθ� ����
		Transparent,
		PostProcess,
		End,
	};

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;


		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;

	};

	enum class eTextureSlot
	{
		T0,
		T1,
		T2,
		T3,
		T4,
		T5,
		T6,
		T7,

		CubeT8,
		CubeT9,

		Array2DT10,
		Array2DT11,

		End,
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Color,
		Animation,
		Light,
		ParticleSystem,
		Noise, 
		PostProcess,
		LaserHit,
		End,
	};


	enum class eGPUParam
	{
		Int_1,
		Int_2,
		Int_3,
		Int_4,
		Float_1,
		Float_2,
		Float_3,
		Float_4,
		Float_5,
		Float_6,
		Float_7,
		Float_8,
		Vector2_1,
		Vector2_2,
		Vector2_3,
		Vector2_4,
		Vector3_1,
		Vector3_2,
		Vector3_3,
		Vector3_4,
		Vector4_1,
		Vector4_2,
		Vector4_3,
		Vector4_4,
		Matrix_1,
		Matrix_2,
		Matrix_3,
		Matrix_4,
	};
	

	enum class eSRVType
	{
		SRV,
		UAV,
		End,
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		enums::eCollisionState state;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;
		float radius;
		float duration;
		float time;
	};

	struct LightAttribute
	{
		math::Vector4 diffuse;
		math::Vector4 specular;
		math::Vector4 ambient;

//		math::Vector4 emissive;

		math::Vector4 position;
		math::Vector4 direction;

		float radius;
		float angle;
		
		enums::eLightType type;

		int padding; // ������� �е�
	};

	struct Particle
	{
		math::Vector4 position;
		math::Vector4 direction;
		math::Vector4 startColor;
		math::Vector4 endColor;

		math::Vector3  startScale;
		math::Vector3  endScale;

		float lifeTime;
		float elapsedTime;
		float speed;
		math::Vector2 gravityAcc;
		float radian;
		UINT active;

	};
	struct ParticleShared
	{
		UINT activeCount;
	};
}