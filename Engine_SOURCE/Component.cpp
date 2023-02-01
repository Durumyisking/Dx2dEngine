#include "Component.h"
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

}