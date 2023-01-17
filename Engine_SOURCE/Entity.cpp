#include "Entity.h"


namespace dru
{
	CEntity::CEntity()
		: mID(reinterpret_cast<UINT32>(this))
	{
	}
	CEntity::CEntity(const CEntity& other)
		: mID(reinterpret_cast<UINT32>(this))
		, mName(other.mName)
	{
	}
	CEntity::~CEntity()
	{
	}
}