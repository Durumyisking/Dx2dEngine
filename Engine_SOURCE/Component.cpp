#include "Component.h"
#include "GameObj.h"
#include "LiveGameObj.h"

namespace dru
{
    CComponent::CComponent(eComponentType _Type)
        : mType(_Type)
        , mOwner(nullptr)
    {
    }

    CComponent::~CComponent()
    {
    }

    CLiveGameObj* CComponent::GetOwner_LiveObject()
    {
        return dynamic_cast<CLiveGameObj*>(mOwner);
    }

    math::Vector3 CComponent::GetOwnerPos() const
    {
        return mOwner->GetPos();
    }

} 