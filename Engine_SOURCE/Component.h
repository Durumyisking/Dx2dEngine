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
			Mesh, // �������� ����Ǿ�����
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
		const eType mType; // Ÿ���� �ٲ�� �ȵǱ� ����
		CGameObj* mOwner;

	};

}

