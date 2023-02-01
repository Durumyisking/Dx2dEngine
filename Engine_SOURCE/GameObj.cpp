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
	}

	void CGameObj::Initialize()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->Initialize();
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
	}

	void CGameObj::fixedupdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedupdate();
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
	}

	void CGameObj::AddComponent(CComponent* _Component)
	{
		int order = _Component->GetOrder();
		mComponents[order] = _Component;
		mComponents[order]->SetOwner(this);

	}

}