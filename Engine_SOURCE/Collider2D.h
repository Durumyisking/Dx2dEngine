#pragma once
#include "Component.h"
#include "Transform.h"

namespace dru
{
    class CCollider2D :
        public CComponent
    {
    public:
        CCollider2D();
        ~CCollider2D();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();

        void SetType(eColliderType _Type) { mType = _Type; }
        eColliderType GetType() const { return mType; }
        void SetCenter(Vector2 _Center) { mCenter = _Center; }
  //      eColliderType GetCenter() const { return mType; }
        void SetSize(Vector2 _Size) { mSize = _Size; }
//        eColliderType GetCenter() const { return mType; }


    private:
        eColliderType mType;
        CTransform* mTransform;

        Vector2 mSize;
        Vector2 mCenter;
        bool    mbTrigger;

    };
}
