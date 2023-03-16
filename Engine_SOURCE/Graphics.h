#pragma once
#include <wrl.h>
#include "druMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2
#define CBSLOT_FADE 3
#define CBSLOT_COLOR 4
#define CBSLOT_ANIMATION 5
#define CBSLOT_LIGHTCOUNT 6


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

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Fade,
		Color,
		Animation,
		Light,
		End,
	};

	enum class eGPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,
		End,
	};

	enum class eSRVType
	{
		None,
		End,
	};

	struct DebugMesh
	{
		enums::eColliderType type;
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

}