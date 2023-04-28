#pragma once

namespace dru::enums
{

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		BackGround,
		Bullet,
		Monster,
		MonsterGun,
		Player,
		AfterImage,
		Platforms,
		Ray,
		Particle,
		FX,
		UI,
		PostProcess,
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
		AfterImageRenderer,
		Animator,
		Particle,
		Light, 
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
		Line,
		Box,
		Sphere,
		End,

	};

	enum class eCollisionState
	{
		CollisionNot = 0,
		CollisionEnter,
		CollisionStay,
		CollisionExit,
		CollisionOff,
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

	enum class eDir
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		END,
	};

}
