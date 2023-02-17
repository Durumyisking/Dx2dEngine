#include "GameObj.h"
namespace dru
{
	CGameObj::CGameObj()
		:mState(eState::Active)
	{
		mComponents.resize(static_cast<UINT>(eComponentType::End));
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
		\
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

}