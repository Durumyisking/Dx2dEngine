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
		friend class CLiveGameObj;
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};
		enum class eObjectType
		{
			None,
			Live,
		};


		struct Blink
		{
			bool IsBlink;
			float BlinkTimer;
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
				mScripts.push_back(dynamic_cast<CScript*>(comp));
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

		template <typename T>
		T* GetComponents()
		{
			std::vector<T*> components = {};

			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);

				if (nullptr != component)
					components.push_back(component);
			}
			return components;
		}

		const std::vector<CScript*>& GetScripts() { return mScripts; }

		template <typename T>
		T* GetScript()
		{
			T* component;
			for (auto* script : mScripts)
			{
				component = dynamic_cast<T*>(script);

				if (nullptr != component)
					return component;
			}
			return nullptr;
		}



		Vector3 Forward() { return GetComponent<CTransform>()->Forward(); }
		Vector3 Right() { return GetComponent<CTransform>()->Right(); }
		Vector3 Up() { return GetComponent<CTransform>()->Up(); }




		void Flip();

		
		bool IsRenderingBlock() const { return mbBlockRendering; }
		void RenderingBlockOn() { mbBlockRendering = true; }
		void RenderingBlockOff() { mbBlockRendering = false; }

		bool MoveToTarget_Smooth_bool(CGameObj* _target, float _speed, bool _zOn, eDir _dir = eDir::END);
		Vector3 MoveToTarget_Smooth_vector3(CGameObj* _target, float _speed, bool _zOn, eDir _dir = eDir::END);

		CGameObj* GetParent() 
		{
			CTransform* tr = GetComponent<CTransform>()->GetParent();
			if (nullptr != tr)
			{
				return tr->GetOwner();
			}
			return nullptr; 
		}

		eObjectType GetObjectType() const { return mObjectType; }

	protected:
		std::vector<CComponent*> mComponents;


	private:
		eLayerType mType;
		eObjectType mObjectType;
		eState mState;
		std::vector<CScript*> mScripts;
		bool mbDestroy;

		bool mbIsLeft;
		bool mbOnFloor;
		bool mbBlockRendering;

	public:

		void SetPos(Vector3 _Value);
		void SetPosZ(float _Z) 
		{
			Vector3 pos = GetPos();
			pos.z = _Z;
			GetComponent<CTransform>()->SetPosition(pos);
		};
		void SetScale(Vector3 _Value);
		void SetRotation(Vector3 _Value);


		Vector3 GetPos();
		Vector3 GetWorldPos();
		Vector3 GetScale();
		Vector3 GetRotation();


		void SetMaterial(std::shared_ptr<CMaterial> _Material);
		void SetMesh(std::shared_ptr<CMesh> _Mesh);

		bool IsDead()
		{
			if (eState::Dead == mState)
				return true;
			return false;
		}

		void Active()
		{
			if (!this)
			{
				return;
			}
			mState = eState::Active;
		}
		void Pause()
		{
			if (!this)
			{
				return;
			}
			mState = eState::Paused;
		}
		void Die()
		{
			if (!this)
			{
				return;
			}

			mState = eState::Dead;
		}

		eState GetState() const { return mState; }

		bool IsDontDestroy() { return mbDestroy; }
		void DontDestroy() { mbDestroy = true; }

		eLayerType GetLayerType() const { return mType; }
		void SetLayerType(eLayerType _Type) { mType = _Type; }

		bool IsLeft() { return mbIsLeft; }
		void SetLeft() { mbIsLeft = true; }

		void SetRight() { mbIsLeft = false; }

		bool IsOnFloor() const { return mbOnFloor; }
		void SetFloorOn() { mbOnFloor = true; }
		void SetFloorOff() { mbOnFloor = false; }
	};

}
