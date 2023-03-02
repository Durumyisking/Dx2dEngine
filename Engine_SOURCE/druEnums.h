#pragma once

namespace dru::enums
{

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		BackGround,
		Monster,
		Player,
		UI,
		End = 16,
	};


	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
		Collider,
		MeshRenderer,
		SpriteRenderer,
		UI,
		Script,
		End,

	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		//Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		
		Script,
		End,

	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Box,
		Sphere,
		End,

	};


}
