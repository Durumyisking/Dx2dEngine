#include "Component.h"
#include "GameObj.h"

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

    math::Vector3 CComponent::GetOwnerPos() const
    {
        return mOwner->GetPos();
    }

} 