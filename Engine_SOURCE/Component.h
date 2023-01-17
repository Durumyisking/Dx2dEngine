#pragma once
#include "Entity.h"

namespace dru
{
	class CGameObj;
	class CComponent
	{
	public:
		enum class eType
		{
			None,
			Transform,
			Camera,

			// render
			Mesh, // 정점정보 저장되어있음
			SkyBox,
			Decal,

			Script,
			End,

		};
	public:
		CComponent();
		virtual ~CComponent();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

	private:
		const eType mType; // 타입이 바뀌면 안되기 때문
		CGameObj* mOwner;

	};

}

