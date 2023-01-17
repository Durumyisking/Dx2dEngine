#pragma once
#include "Entity.h"
#include "Component.h"

namespace dru
{
	class CGameObj
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};

	public:
		CGameObj();
		virtual ~CGameObj();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		void AddComponent(CComponent* _Component);

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);

				if (nullptr != component)
					return component;
			}
			return nullptr;
		}

	private:
		std::vector<CComponent*> mComponents;

		eState mState;
	};


}
