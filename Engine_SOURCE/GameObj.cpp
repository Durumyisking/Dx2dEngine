#include "GameObj.h"
namespace dru
{
	CGameObj::CGameObj()
		:mState(eState::Active)
	{
		mComponents.resize(static_cast<UINT>(eComponentType::End));

		mTransform = new CTransform();
		this->AddComponent(mTransform);
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

	void CGameObj::fixedupdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedupdate();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->fixedupdate();
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
			mScripts.push_back(_Component);
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


}