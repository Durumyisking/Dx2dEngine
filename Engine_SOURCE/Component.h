#pragma once
#include "Entity.h"
#include "druMath.h"

namespace dru
{
	using namespace enums;

	class CGameObj;
	class CComponent : public CEntity
	{
	public:

	public:
		CComponent(eComponentType _Type);
		virtual ~CComponent();

		virtual void Initialize() = 0;
		virtual void update() = 0;
		virtual void fixedUpdate() = 0;
		virtual void render() = 0;

		eComponentType GetOrder() { return mType; }

		void SetOwner(CGameObj* _Owner) { mOwner = _Owner; }
		CGameObj* GetOwner() { return mOwner; }


	private:
		const eComponentType mType; // 타입이 바뀌면 안되기 때문
		CGameObj* mOwner;

	};

}

