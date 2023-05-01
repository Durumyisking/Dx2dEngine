#pragma once
#include "Entity.h"
#include "druMath.h"


namespace dru
{
	using namespace enums;

	class CGameObj;
	class CLiveGameObj;
	class CComponent : public CEntity
	{
	public:

	public:
		CComponent(eComponentType _Type);
		virtual ~CComponent();

		virtual void Initialize()	= 0;
		virtual void update()		= 0;
		virtual void fixedUpdate()	= 0;
		virtual void render()		= 0;

		eComponentType GetOrder() { return mType; }

		void SetOwner(CGameObj* _Owner) { mOwner = _Owner; }
		CGameObj* GetOwner() { return mOwner; }
		CLiveGameObj* GetOwner_LiveObject();

		template <typename T>
		T* GetOwnerType()
		{
			CGameObj* owner = GetOwner();
			return dynamic_cast<T*>(owner);

		}

		math::Vector3 GetOwnerPos() const; // component script에서 코드 사용 편하게 하기위함
		math::Vector3 GetOwnerWorldPos() const; 

	private:
		const eComponentType mType; // 타입이 바뀌면 안되기 때문
		CGameObj* mOwner;

	};

}

