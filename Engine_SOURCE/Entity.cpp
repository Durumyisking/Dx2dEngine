#include "Entity.h"


namespace dru
{

	CEntity::CEntity()
		: mID(reinterpret_cast<uintptr_t>(this))
	{
	}
	CEntity::CEntity(const CEntity& other)
		: mID(reinterpret_cast<uintptr_t>(this))
		, mName(other.mName)
	{
	}
	CEntity::~CEntity()
	{
	}
}