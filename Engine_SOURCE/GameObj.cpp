#include "GameObj.h"
#include "TimeMgr.h"

namespace dru
{
	CGameObj::CGameObj()
		:mState(eState::Active)
		, mbIsLeft(true)
	{
		mComponents.resize(static_cast<UINT>(eComponentType::End));
		this->AddComponent<CTransform>(eComponentType::Transform);

	}

	CGameObj::~CGameObj()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			delete comp;
		}
	}

	void CGameObj::Initialize()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->Initialize();		
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
		}
	}

	void CGameObj::update()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;			
			comp->update();
		}
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->update();
		}
	}

	void CGameObj::fixedUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedUpdate();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->fixedUpdate();
		}
	}

	void CGameObj::render()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->render();
		}
		
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->render();
		}
	}

	void CGameObj::AddComponent(CComponent* _Component)
	{
		eComponentType order = _Component->GetOrder();


		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = _Component;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(dynamic_cast<CScript*>(_Component));
			_Component->SetOwner(this);
		}
	}

	void CGameObj::SetPos(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			GetComponent<CTransform>()->SetPosition(_Value);
		}
	}

	void CGameObj::SetScale(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			GetComponent<CTransform>()->SetScale(_Value);
		}
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->ChangeSize();
		}
		if (nullptr != GetComponent<CMeshRenderer>())
		{
			GetComponent<CMeshRenderer>()->ChangeSize();
		}
	}

	void CGameObj::SetRotation(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			GetComponent<CTransform>()->SetRotation(_Value);
		}
	}

	Vector3 CGameObj::GetPos()
	{
		return GetComponent<CTransform>()->GetPosition();
	}

	Vector3 CGameObj::GetScale()
	{
		return GetComponent<CTransform>()->GetScale();
	}

	Vector3 CGameObj::GetRotation()
	{
		return GetComponent<CTransform>()->GetRotation();
	}

	void CGameObj::SetMaterial(std::shared_ptr<CMaterial> _Material)
	{
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->SetMaterial(_Material);
		}
	}

	void CGameObj::SetMesh(std::shared_ptr<CMesh> _Mesh)
	{
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->SetMesh(_Mesh);
		}
	}

	void CGameObj::Flip()
	{
		CBaseRenderer* baseRenderer = GetComponent<CBaseRenderer>();
		if (baseRenderer)
		{
			std::shared_ptr<CMaterial> mtrl = baseRenderer->GetMaterial();
			if (mtrl)
			{

#define INVERSE -1
#define NORMAL 1


				int isInverse = mbIsLeft ? INVERSE : NORMAL;

				mtrl->SetData(eGPUParam::Int, &isInverse);
			}
		}

	}
	bool CGameObj::MoveToTarget_Smooth(CGameObj* _target, float _speed)
	{
		if (!_target)
			return false;

		Vector3 TargetPos = _target->GetPos();
		Vector3 ObjPos = this->GetPos();
		Vector3 Dir = (TargetPos - ObjPos);
		Dir.Normalize();
		float Distance = (TargetPos - ObjPos).Length();

		if (Distance >= 0.01f)
		{
			float Speed = Distance / _speed;
			float Step = Speed * CTimeMgr::DeltaTime();

			if (Step < Distance)
			{
				ObjPos += Dir * Step;
				this->SetPos(ObjPos);

				return false;
			}
			else
			{
				return true;
			}
		}
	}
}