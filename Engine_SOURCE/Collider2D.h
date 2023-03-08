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

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);


        // 물리 필요 없는애 (충돌로 움직임 없는 이벤트만 발동시킬때)
        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);

        void SetType(eColliderType _Type) { mType = _Type; }
        eColliderType GetType() const { return mType; }
        void SetCenter(Vector2 _Center) { mCenter = _Center; }
        Vector2 GetCenter() const { return mCenter; }
        void SetScale(Vector2 _Scale) { mScale = _Scale; }
        Vector2 GetScale() const { return mScale; }
        float GetRadius() const { if (eColliderType::Circle == mType) return mScale.x; }

        Vector3 GetColliderPos() const { return mPosition; }

        bool IsTrigger() const { return mbTrigger; }

        UINT GetColliderID() const { return mColliderID; }

    private:
        static UINT mColliderID;

        eColliderType mType;
        CTransform* mTransform;

        Vector2 mScale;
        Vector2 mCenter;

        Vector3 mPosition;

        bool    mbTrigger;

    };
}
