#pragma once
#include "Entity.h"
#include "Component.h"
#include "Script.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "SpriteRenderer.h"

namespace dru
{
	using namespace math;
	class CGameObj : public CEntity
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

		virtual void Initialize();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			eComponentType order = comp->GetOrder();

			if (order != eComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(comp);
				comp->SetOwner(this);
			}

			return comp;
		}

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

		void SetPos(Vector3 _Value);
		void SetScale(Vector3 _Value);
		void SetRotation(Vector3 _Value);

		Vector3 GetPos();
		Vector3 GetScale();
		Vector3 GetRotation();

		void SetMaterial(std::shared_ptr<CMaterial> _Material);
		void SetMesh(std::shared_ptr<CMesh> _Mesh);

	private:
		eState mState;
		std::vector<CComponent*> mComponents;
		std::vector<CComponent*> mScripts;



	};

}
