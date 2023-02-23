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
		SolidNone, // 컬링 안함
		WireframeNone, // 선으로만 그리기 Topology랑 같은데 그냥 gpu에서 처리해주는거
		End,
	};

	enum class eDepthStencilType
	{
		Less, // 일반적인 원근
		Greater, // 원근 거꾸로
		NoWrite, // 겹치면 아예 안그림
		None, // 깊이버퍼 사용 안함
		End,
	};

	enum class eBlendStateType
	{
		Default,
		AlphaBlend,
		OneOne, // 알파값 없이 물체에 색 섞음
		End,
	};

	enum class eRenderingMode
	{
		Opaque, // 불투명
		Cutout, // 일부만 투명
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

		D3D11_BUFFER_DESC Desc = {};
		Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;


		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;

	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Fade,
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

}