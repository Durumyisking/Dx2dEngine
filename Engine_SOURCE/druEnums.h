#pragma once

namespace dru::enums
{
	enum class eCBType
	{
		Transform,
		End,

	};

	enum class eLayerType
	{
		None = 0,
		Background = 1,
		Player = 2,

		End,
	};


	enum class eComponentType
	{
		None,
		Transform,
		Camera,

		// render
		Mesh, // 정점정보 저장되어있음
		SkyBox,
		Decal,
		Collider,
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
