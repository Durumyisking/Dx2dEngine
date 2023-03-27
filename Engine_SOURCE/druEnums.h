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
		Platforms,
		Particle,
		FX,
		UI,
		End = 16,
	};


	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
		RigidBody,
		Collider,
		MeshRenderer,
		SpriteRenderer,
		Animator,
		Particle,
		UI,
		Light,
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

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,

	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot, 
		End,

	};


}
