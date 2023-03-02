#pragma once
#include "Entity.h"
#include "Component.h"
#include "Script.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "MeshRenderer.h"

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
		virtual void fixedUpdate();
		virtual void render();

		template <typename T>
		T* AddComponent(eComponentType _eType)
		{
			
			T* comp = new T();

			if (_eType != eComponentType::Script)
			{
				mComponents[(UINT)_eType] = comp;
				mComponents[(UINT)_eType]->SetOwner(this);
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
		CScript* GetScript()
		{
			for (CComponent* script : mScripts)
			{
				CScript* returnScript = dynamic_cast<CScript*>(script);

				if (nullptr != script)
					return returnScript;
			}
			return nullptr;
		}

		void SetPos(Vector3 _Value);
		void SetScale(Vector3 _Value);
		void SetRotation(Vector3 _Value);


		Vector3 GetPos();
		Vector3 GetScale();
		Vector3 GetRotation();

		Vector3 Forward() { return GetComponent<CTransform>()->Forward(); }
		Vector3 Right() { return GetComponent<CTransform>()->Right(); }
		Vector3 Up() { return GetComponent<CTransform>()->Up(); }


		void SetMaterial(std::shared_ptr<CMaterial> _Material);
		void SetMesh(std::shared_ptr<CMesh> _Mesh);

		bool IsDead()
		{
			if (eState::Dead == mState)
				return true;
			return false;
		}

		void Active() { mState = eState::Active; }
		void Pause() { mState = eState::Paused; }
		void Die() { mState = eState::Dead; }

		eState GetState() const { return mState; }

		bool IsDontDestroy(){ return mbDestroy;	}
		void DontDestroy() { mbDestroy = true; }

		eLayerType GetLayerType() const { return mType; }
		void SetLayerType(eLayerType _Type) { mType = _Type; }


	protected:
		std::vector<CComponent*> mComponents;


	private:
		eLayerType mType;
		eState mState;
		std::vector<CComponent*> mScripts;
		bool mbDestroy;


	};

}
