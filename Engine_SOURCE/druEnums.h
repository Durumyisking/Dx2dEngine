#pragma once

namespace dru::enums
{

	enum class eLayerType
	{
		None = 0,
		Camera,
		BackGround,
		Monster,
		Player,
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


}
