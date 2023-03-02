#include "DebugObject.h"
#include "Component.h"

namespace dru
{
	CDebugObject::CDebugObject()
	{
	}

	CDebugObject::~CDebugObject()
	{
	}

	void CDebugObject::fixedUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedUpdate();
		}
	}

}